function [Pitch, Merit] = tm_trk(Data, Fs, SPitch, pStd, pAvg, Prm)
%TM_TRK  Temporal pitch tracking for YAAPT pitch tracking 
%
%   [Pitch, Merit] = tm_trk(Data, Fs, SPitch, pStd, pAvg, Prm)
%   computes estimates of pitch  using nonlinearly processed
%   speech (typically square or absolute value) and frequency domain processing
%   Search for frequencies which have energy at multiplies of that frequency
%
%INPUTS:
%   Data:   Nonlinearly processed signal
%   Fs:    The sampling frequency.
%   SPitch:The spectral F0 track, with the unvoiced
%   pStd:  The STD of voiced spectral F0 track .
%   pAvg:  The mean of voiced spectral F0 track .
%   Prm:   Array of parameters used to control performance
%
%OUTPUTS:
%   Pitch: Computed pitch candidates array
%   Merit: The merit of array of pitch candidates

%   Creation :   Jun 20, 2006, July 27, 2007
%   Programers:  Hongbing Hu

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     This file is a part of the YAAPT program, designed for a fundamental 
%   frequency tracking algorithm that is extermely robust for both high quality 
%   and telephone speech.  
%     The YAAPT program was created by the Speech Communication Laboratory of
%   the state university of New York at Binghamton. The program is available 
%   at http://www.ws.binghamton.edu/zahorian as free software. Further 
%   information about the program could be found at "A spectral/temporal 
%   method for robust fundamental frequency tracking," J.Acosut.Soc.Am. 123(6), 
%   June 2008.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%-- PARAMETERS ----------------------------------------------------------------
nframesize = fix(Prm.frame_length*Fs/1000);    
nframejump = fix(Prm.frame_space*Fs/1000); 
noverlap   = nframesize-nframejump;         % overlap width in sample 
numframes  = fix((length(Data)-noverlap)/nframejump);

merit_boost = Prm.merit_boost;
% The maximum number of pitch candidates
maxcands   = Prm.nccf_maxcands; 
%freq_thresh = pAvg;  % seems too large
freq_thresh = 5 * pStd;
SRange = zeros(2,length(SPitch));
% Determine the search range according spectral pitch track
temp_max = zeros(1,length(SPitch));
temp_min = zeros(1,length(SPitch));
for i = 1:length(SPitch)
    temp_max(i) = SPitch(i)-2*pStd;
    temp_min(i) = SPitch(i)+2*pStd;
end
SRange(1,:)  = max(temp_max, Prm.f0_min);
SRange(2,:)  = min(temp_min, Prm.f0_max);    
  
%-- INITIALIZATION -----------------------------------------------------------
Pitch = zeros(maxcands, numframes);
Merit = zeros(maxcands, numframes);

%-- MAIN ROUTINE --------------------------------------------------------------
for n = 1:numframes

    firstp = 1+((n-1)*(nframejump));
    Signal = Data(firstp:firstp+nframesize-1);
    
    % Compute pitch candidates,  and correspnding "merit" values,
    % up to maxcands per frame Merit values are normalized (0 to
    % 1),  and depend mainly on size of correlation peaks
    Lag_min0 = fix(Fs/SRange(2,n)) - 3;
    Lag_max0 = fix(Fs/SRange(1,n)) + 3;
    % Compute correaltion
    Phi =  crs_corr(Signal', Lag_min0, Lag_max0);
    
    % The Max_cand pitch candidates are collected into Pitch and
    % Merit arraies 
    [Pitch(:,n),Merit(:,n)] = cmp_rate(Phi,Fs,maxcands,Lag_min0,Lag_max0,Prm);
end 

%   The following lines increase merit for peaks which are very
%   close to in frequency to those peaks which are close to
%   smoothed F0 track from spectrogram,   and decrease merit for peaks
%   which are not close to the smoothed F0 track obtained from
%   spectrogram
for i = 1:maxcands
    Idx_unvoiced = SPitch == 0;
    diff   =  abs( (Pitch(i,:) - SPitch(1,:)));
%     diff(Idx_unvoiced) = freq_thresh + 1;
    match1 = zeros(1,length(diff));
    for j = 1:length(diff)
        if(Idx_unvoiced(j)==1)
            diff(j) = freq_thresh + 1;
        end
         match1(j) = diff(j) < freq_thresh;
    end
%     match1 =  (diff < freq_thresh);
    match = zeros(1,length(diff));
    for k = 1:length(diff)
         match(k) = ((1 - (diff(k)/freq_thresh)) * match1(k));
    end
%     match  =  ((1 - (diff./freq_thresh)) .* match1);
    Merit(i,:) = ((1+merit_boost)*Merit(i,:)).*match;
end

