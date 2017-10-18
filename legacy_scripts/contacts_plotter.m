clear;
graphics_toolkit("gnuplot");

INITIAL_TIMESTEP = 300500000;
SHEAR_TIMESTEPS = 1000000;
NEVERY = 10000;

figure;
for i = INITIAL_TIMESTEP:NEVERY:(INITIAL_TIMESTEP+SHEAR_TIMESTEPS)
	contact_positions_data = csvread(num2str(i));
	clf;
	hold on;
	xlim([0.0 0.02]); % xlim, from LIGGGHTS script
	xlim("manual"); % fix xlim
	ylim([0.0 0.02]); % ylim, from LIGGGHTS script
	ylim("manual"); % fix ylim
	scatter(contact_positions_data(2:end,1),contact_positions_data(2:end,2),[],contact_positions_data(2:end,4:6),"filled"); % row 1 contains shearing distance so start from row 2; style=cross
	text(mean(xlim()), max(ylim()), num2str(contact_positions_data(1,1))); % display shearing distance at top of scatter plot
	pause(0.5);
endfor
