clear;
graphics_toolkit("gnuplot");

%%% plot radius distribution %%%
radius_data = csvread("../raw_data/radius_data.csv");
figure;
hold on;
grid on;
hist(radius_data,100,1); % plot histogram with 100 bins
title('Distribution of particle radius');
xlabel('Radius (m)');
ylabel('Number (particles)');
print("../distribution_of_particle_radius.png");

%%% plot average coordination number %%%
average_coordination_number_data = csvread("../raw_data/average_coordination_number_data.csv");
figure;
hold on;
grid on;
xlim([min(average_coordination_number_data(:,1)) max(average_coordination_number_data(:,1))]); % xlim
xlim("manual"); % fix xlim
plot(average_coordination_number_data(:,1),average_coordination_number_data(:,2));
title('Average Coordination Number against Shear Distance');
xlabel('Shear Distance (m)');
ylabel('Average Coordination Number');
print("../average_coordination_number.png");

%%% plot cumulative born/broken contacts %%%
contact_data = csvread("../raw_data/contact_data.csv");
figure;
hold on;
grid on;
xlim([min(contact_data(:,1)) max(contact_data(:,1))]); % xlim
xlim("manual"); % fix xlim
plot(contact_data(:,1),contact_data(:,2),'r',contact_data(:,1),contact_data(:,3),'b'); % plot all rows of column 1 against all rows of column 2 in red, against all rows of column 3 in blue
title('Broken Contacts and Born Contacts against Shear Distance');
xlabel('Shear Distance (m)');
ylabel('Number');
legend("Broken", "Born");
print("../number_of_broken_born_contacts.png");

%%% plot born/broken contacts between successive timesteps  %%%
contact_data2 = csvread("../raw_data/contact_data2.csv");
figure;
hold on;
grid on;
xlim([min(contact_data2(:,1)) max(contact_data2(:,1))]); % xlim
xlim("manual"); % fix xlim
plot(contact_data2(:,1),contact_data2(:,2),'r',contact_data2(:,1),contact_data2(:,3),'b'); % plot all rows of column 1 against all rows of column 2 in red, against all rows of column 3 in blue
title('Broken Contacts and Born Contacts between successive timesteps against Shear Distance');
xlabel('Shear Distance (m)');
ylabel('Number');
legend("Broken", "Born");
print("../number_of_broken_born_contacts2.png");

%%% plot cumulative number of events %%%
number_of_events_data = csvread("../raw_data/number_of_events_data.csv");
figure;
hold on;
grid on;
xlim([min(number_of_events_data(:,1)) max(number_of_events_data(:,1))]); % xlim
xlim("manual"); % fix xlim
plot(number_of_events_data(:,1),number_of_events_data(:,2));
title('Cumulative Number of Events against Shear Distance');
xlabel('Shear Distance (m)');
ylabel('Cumulative Number of Events');
print("../cumulative_number_of_events.png");

%%% plot velocity profile %%%
YMAX = 0.016713;
VELOCITY_LAYERS = 20;
NUMBER_OF_CUTOFF_LAYERS = 0;
MEAN_DIAMETER = 0.001;

normalized_layer_height = (YMAX/VELOCITY_LAYERS)/MEAN_DIAMETER;

plotted_data = zeros(VELOCITY_LAYERS-2*NUMBER_OF_CUTOFF_LAYERS,2);

velocity_profile_data = csvread("../raw_data/velocity_profile.csv");

for i = 1:(VELOCITY_LAYERS-2*NUMBER_OF_CUTOFF_LAYERS)
	plotted_data(i,1) = (i+NUMBER_OF_CUTOFF_LAYERS-0.5)*normalized_layer_height; % first column stores center of layers
	plotted_data(i,2) = mean(velocity_profile_data(:,(i+NUMBER_OF_CUTOFF_LAYERS+1))); % second column stores mean velocity, normalized by mean atom diameter
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
