clear;
graphics_toolkit("gnuplot");

YMAX = 0.016713;
VELOCITY_LAYERS = 20;
NUMBER_OF_CUTOFF_LAYERS = 2;
MEAN_DIAMETER = 0.001;
normalized_layer_height = (YMAX/VELOCITY_LAYERS)/MEAN_DIAMETER;

SHEAR_TIMESTEPS = 600000000;
NEVERY = 10000;
plotting_nevery = 10000000;

plotted_data = zeros(VELOCITY_LAYERS-2*NUMBER_OF_CUTOFF_LAYERS,2);

velocity_profile_data = csvread("../raw_data/velocity_profile.csv");

set(0, 'defaultfigurevisible', 'off');
figure;
for j = 1:(plotting_nevery/NEVERY):(SHEAR_TIMESTEPS/NEVERY+1)
	for i = 1:(VELOCITY_LAYERS-2*NUMBER_OF_CUTOFF_LAYERS)
		plotted_data(i,1) = (i+NUMBER_OF_CUTOFF_LAYERS-0.5)*normalized_layer_height; % first column stores center of layers
		plotted_data(i,2) = mean(velocity_profile_data(1:j,(i+1))); % second column stores mean velocity, normalized by mean atom diameter
	endfor
	
	clf;
	hold on;
	xlim([-0.0001 0.0005]); % estimated xlim
	xlim("manual"); % fix xlim
	ylim([min(plotted_data(:,1)) max(plotted_data(:,1))]); % ylim
	ylim("manual"); % fix ylim
	plot(plotted_data(:,2),plotted_data(:,1));
	grid on;
	title('Velocity Profile');
	xlabel('Velocity (m/s)');
	ylabel('Height/Mean Diameter (unitless)');
	filename=sprintf('raw_velocity_pictures/%05d.png', j);
	print(filename);
endfor

