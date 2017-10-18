#ifndef __DATA_HANDLING_INCLUDED__
#define __DATA_HANDLING_INCLUDED__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

#define SMALL_NUM 0.0000001 // for floating point comparision
#define INFO_PER_ATOM 11 // id, radius, x, y, z, vx, vy, vz, fx, fy, fz

class Data_handling {
		long Timestep;
		long Number_Of_Atoms;
		long Initial_Number_Of_Contacts; // initial number of contacts
		long Current_Number_Of_Contacts; // current number of contacts
		long Number_Of_Broken_Contacts; // number of broken contacts
		long Number_Of_Born_Contacts; // number of born contacts
		
		double *Atoms_Info; // [0]=id1, [1]=radius1, [2]=x1, [3]=y1, [4]=z1, [5]=id2, etc
		int *Initial_Contact_Matrix; // [0]=atom0_atom1, [1]=atom0_atom2, etc
		int *Previous_Contact_Matrix; //TO-DO: Initial_Contact_Matrix but at the previous timestep
		int *Contact_Matrix; // [0]=atom0_atom1, [1]=atom0_atom2, etc
		int *Color_Matrix; //TO-DO: to color contact points (idle, born, broken)
	public:
		double *Box_Bounds; // [flag to x,y,z], [xlo], [xhi], [ylo], [yhi], [zlo], [zhi]
		
		Data_handling(); // constructor
		~Data_handling(); // destructor
		
		void read_timestep(string file_line); // read timestep
		void read_number_of_atoms(string file_line, long initial_timestep); // read number of atoms
		void read_box_bounds(string file_line); // read box dimensions, xlo, xhi, ylo, yhi, zlo, zhi
		void read_atoms_info(string file_line); // read id, radius, x, y, z
		void modify_contact_matrix(long initial_timestep); // if first timestep, modify both initial and current contact matrices; if not then modify only current matrix
		void compare_contact_matrix(); // compare two matrices; if timestep=1, surely two matrices are equal
		
		void output_contact_data(string output_filename, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity); // output number of broken/born contacts
		void output_average_coordination_number (string output_filename, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity); // output average number of contacts per atom
		void output_contact_points(bool is_output_contact_point, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity); // output files containing position of contact points
		void output_radius_data(string output_filename); // output atoms radii
		
		void output_velocity_profile(string output_filename, double ymin, double ymax, long velocity_layers, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity); //TO-DO: output velocity profile
		
		bool is_contact(double atom1_radius, double atom1_x, double atom1_y, double atom1_z,
						double atom2_radius, double atom2_x, double atom2_y, double atom2_z); // utility function to check if two atoms touch
		double contact_coordinates(double &x_coord, double &y_coord, double &z_coord,
									double atom1_radius, double atom1_x, double atom1_y, double atom1_z,
									double atom2_radius, double atom2_x, double atom2_y, double atom2_z); // utility function to calculate contact position
};

string Output_filename(long filenumber); // return filename in string format

#endif
