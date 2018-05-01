#ifndef __ATOM_RADIUS_INCLUDED__
#define __ATOM_RADIUS_INCLUDED__

#include <vector>

#include "experiment.h"

class Atom_radius: public Experiment {
	
protected:
	std::vector<double> mRadius_data;
	
public:
	void analyse (void);
	void output (void);
};

#endif
