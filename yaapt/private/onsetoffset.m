function [out] = onsetoffset(Data,Fs)
bp_low = 20;
bp_high = 4410;

frq_frame_length = 10;
frq_frame_overlap = 5;
frq_background_ref = 100;
fft_length = 8192;
min_notelength = 125;%1/16 note, 120bpm,125ms
onset_threshold=100;
offset_threshold=10;

frq_frame_jump = frq_frame_length - frq_frame_overlap;
frq_n_frame_length = fix(frq_frame_length*Fs/1000);
frq_n_frame_overlap = fix(frq_frame_overlap*Fs/1000);
frq_n_frame_jump = frq_n_frame_length-frq_n_frame_overlap;
frq_numframes = fix((length(Data)-frq_n_frame_overlap)/(frq_n_frame_jump));
frq_background_frame_idx  = fix(frq_background_ref/frq_frame_jump);

out = zeros(time_numframes,1);


res_window = kaiser(frq_n_frame_length);
[s,~,~] = spectrogram(Data,res_window,frq_n_frame_overlap,fft_length,Fs,'yaxis');
N_F0_min = round(bp_low/(Fs/fft_length));
N_F0_max = round(bp_high/(Fs/fft_length));
s = s(N_F0_min:min(N_F0_max,size(s,1)),:);
frq_Energy_HFC = [1:size(s,1)]*abs(s).^2;
frq_background_Energy = mean(frq_Energy_HFC(1:frq_background_frame_idx));



min_notelength_idx = min_notelength/frq_frame_jump;

frq_ref_Energy = frq_Energy_HFC/frq_background_Energy;
onset_interval = frq_ref_Energy>onset_threshold;
offset_interval = frq_ref_Energy<offset_threshold;
while(any(onset_interval))
    onset_idx_init=find(onset_interval,1);
    offset_idx=find(offset_interval);
    offset_idx_satisfied = offset_idx((offset_idx-onset_idx_init)>min_notelength_idx);
    offset_idx_init = offset_idx_satisfied(1);
    out(onset_idx_init:offset_idx_init)=true;
    onset_interval(onset_idx_init:offset_idx_init)=false;   
end
end
