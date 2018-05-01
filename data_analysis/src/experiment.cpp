// NOTE: set up parameters using this file!

#include "experiment.h"

// constructor
Experiment::Experiment() {
	mTIMESTEP_LENGTH = 0.000001; // sec/timestep
	mSTARTING_TIMESTEP = 500000; // timestep when shearing begins
	mNEVERY = 10000; // LIGGGHTS dumps file every NEVERY timesteps
	mSHEAR_VELOCITY = 0.0005; // shearing velocity
	mYMAX = 0.016713; // position of shearing wall from mesh.vtk
	mPATH_TO_EXPERIMENT = "../../post/"; // relative path to main experiment data
	mPATH_TO_FORWARD = "../../post_forward/"; // relative path to forward experiment data
	mPATH_TO_BACKWARD = "../../post_backward/"; // relative path to backward experiment data
	
	std::cout << "Experiment class constructor called" << "\n";
}

// destructor
Experiment::~Experiment() {
	std::cout << "Experiment class destructor called" << "\n";
}

// print basic parameters of experiment
void Experiment::print_experiment_parameters (void) {
	std::cout << "TIMESTEP_LENGTH " << mTIMESTEP_LENGTH << "\n";
	std::cout << "STARTING_TIMESTEP " << mSTARTING_TIMESTEP << "\n";
	std::cout << "NEVERY " << mNEVERY << "\n";
	std::cout << "SHEAR_VELOCITY " << mSHEAR_VELOCITY << "\n";
	std::cout << "YMAX " << mYMAX << "\n";
	std::cout << mPATH_TO_EXPERIMENT << "\n";
	std::cout << mPATH_TO_FORWARD << "\n";
	std::cout << mPATH_TO_BACKWARD << "\n";
}
