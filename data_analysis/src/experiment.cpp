// NOTE: set up parameters using this file!

#include "experiment.h"

// constructor
Experiment::Experiment() {
	TIMESTEP_LENGTH = 0.000001; // sec/timestep
	STARTING_TIMESTEP = 500000; // timestep when shearing begins
	NEVERY = 10000; // LIGGGHTS dumps file every NEVERY timesteps
	SHEAR_VELOCITY = 0.0005; // shearing velocity
	YMAX = 0.016713; // position of shearing wall from mesh.vtk
	
	std::cout << "Experiment class constructor called" << "\n";
}

// destructor
Experiment::~Experiment() {
	std::cout << "Experiment class destructor called" << "\n";
}

// print basic parameters of experiment
void Experiment::print_experiment_parameters (void) {
	std::cout << "TIMESTEP_LENGTH " << TIMESTEP_LENGTH << "\n";
	std::cout << "STARTING_TIMESTEP " << STARTING_TIMESTEP << "\n";
	std::cout << "NEVERY " << NEVERY << "\n";
	std::cout << "SHEAR_VELOCITY " << SHEAR_VELOCITY << "\n";
	std::cout << "YMAX " << YMAX << "\n";
}
