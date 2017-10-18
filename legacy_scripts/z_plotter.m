clear;
graphics_toolkit("gnuplot");

SHEAR_TIMESTEPS = 1000000;
NEVERY = 10000;

average_coordination_number_data = csvread("average_coordination_number_data.csv");
number_of_lines = SHEAR_TIMESTEPS/NEVERY+1;
jumping_gap = (SHEAR_TIMESTEPS/NEVERY)/10;

figure; % new plotting window

for i = 1:jumping_gap:number_of_lines
	clf; % clear all graphic objects in the plotting window
	hold on; % all subsequent plotting commands will be held
	xlim([4.2 4.6]); % xlim
	xlim("manual"); % fix xlim
	ylim([0 0.2]); % ylim
	ylim("manual"); % fix ylim
	hist(average_coordination_number_data(1:i,2),100,1); % histogram
	text(mean(xlim()), mean(ylim()), num2str(average_coordination_number_data(i,1))); % display shearing distance at centre of plot
	pause(0.1); % pause for 0.1 sec
endfor
