clear;
graphics_toolkit("gnuplot");

YMAX = 0.016713;
VELOCITY_LAYERS = 20;
MEAN_DIAMETER = 0.001;

normalized_layer_height = (YMAX/VELOCITY_LAYERS)/MEAN_DIAMETER;

plotted_data = zeros(VELOCITY_LAYERS,2);

velocity_profile_data = csvread("../raw_data/velocity_profile.csv");

for i = 1:VELOCITY_LAYERS
	plotted_data(i,1) = (i-0.5)*normalized_layer_height; % first column stores center of layers
	plotted_data(i,2) = mean(velocity_profile_data(:,(i+1))); % second column stores mean velocity, normalized by mean atom diameter
endfor

figure;
hold on;
%xlim([min(plotted_data(:,2)) max(plotted_data(:,2))]); % xlim
%xlim("manual"); % fix xlim
ylim([min(plotted_data(:,1)) max(plotted_data(:,1))]); % ylim
ylim("manual"); % fix ylim
plot(plotted_data(:,2),plotted_data(:,1));
grid on;
title('Velocity Profile');
xlabel('Velocity (m/s)');
ylabel('Height/Mean Diameter (unitless)');
print("../velocity_profile.png");

