#ifndef __EXPERIMENT_INCLUDED__
#define __EXPERIMENT_INCLUDED__
// Parameters used in the experiment
// To set parameters, go to experiment.cpp

#include <iostream>

// base class containing basic parameters of the experiment
class Experiment {

protected:
	double TIMESTEP_LENGTH;
	long STARTING_TIMESTEP;
	long NEVERY;
	double SHEAR_VELOCITY;
	double YMAX;

public:
	Experiment();
	~Experiment();
	
	void print_experiment_parameters (void);
};

#endif
