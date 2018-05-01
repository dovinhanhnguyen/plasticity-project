#ifndef __EXPERIMENT_INCLUDED__
#define __EXPERIMENT_INCLUDED__
// Parameters used in the experiment
// To set parameters, go to experiment.cpp

#include <iostream>
#include <string>

// base class containing basic parameters of the experiment
class Experiment {

protected:
	double mTIMESTEP_LENGTH;
	long mSTARTING_TIMESTEP;
	long mNEVERY;
	double mSHEAR_VELOCITY;
	double mYMAX;
	std::string mPATH_TO_EXPERIMENT;
	std::string mPATH_TO_FORWARD;
	std::string mPATH_TO_BACKWARD;

public:
	Experiment();
	~Experiment();
	
	void print_experiment_parameters (void);
};

#endif
