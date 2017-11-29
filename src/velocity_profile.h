#ifndef __VELOCITY_PROFILE_INCLUDED__
#define __VELOCITY_PROFILE_INCLUDED__

#include <iostream>
#include <fstream>
#include <sstream>
#include "data_handling.h"
using namespace std;

#define TIMESTEP_LENGTH 0.000001 // seconds per timestep
#define STARTING_TIMESTEP 500000 // timestep when shearing begins
#define	INITIAL_TIMESTEP 400500000 // first timestep to look at
#define SHEAR_TIMESTEPS 200000 // number of timesteps of shearing
#define NEVERY 10000 // LIGGGHTS dump file every NEVERY timesteps
#define SHEAR_VELOCITY 0.0005 // shearing velocity

#define YMAX 0.016713 // position of shearing wall from mesh.vtk
#define VELOCITY_LAYERS 20 // number of layers to build up velocity profile

enum parser_status {IDLE, TIMESTEP, NUMBER_OF_ATOMS, BOX_BOUNDS, ATOMS_INFO};

Data_handling dataHandler;

string Filename(long filenumber); // return filename in string format

#endif
