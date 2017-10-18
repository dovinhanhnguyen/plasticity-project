clear;
graphics_toolkit("gnuplot");

INITIAL_TIMESTEP = 300500000;
SHEAR_TIMESTEPS = 1000000;
NEVERY = 10000;

h = 0;

figure;
for i = INITIAL_TIMESTEP:NEVERY:(INITIAL_TIMESTEP+SHEAR_TIMESTEPS)
	contact_positions_data = csvread(num2str(i));
	hold on;
	xlim([0.0 0.02]); % xlim, from LIGGGHTS script
	xlim("manual"); % fix xlim
	ylim([0.0 0.02]); % ylim, from LIGGGHTS script
	ylim("manual"); % fix ylim
	scatter(contact_positions_data(2:end,1),contact_positions_data(2:end,2),[],contact_positions_data(2:end,7:9),"filled"); % row 1 contains shearing distance so start from row 2;
	pause(0.1);
endfor
