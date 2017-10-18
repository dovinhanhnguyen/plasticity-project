clear;
graphics_toolkit("gnuplot");

radius_data = csvread("../raw_data/radius_data.csv");
figure;
hold on;
grid on;
hist(radius_data,100,1); % plot histogram with 100 bins
title('Distribution of particle radius');
xlabel('Radius (m)');
ylabel('Number (particles)');
print("../distribution_of_particle_radius.png");

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
