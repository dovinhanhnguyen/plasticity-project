#include "data_handling.h"

// constructor
Data_handling::Data_handling() {
	Number_Of_Broken_Contacts = 0; // initialise to zero
	Number_Of_Born_Contacts = 0; // initialise to zero
	Number_Of_Broken_Contacts2 = 0; // initialise to zero
	Number_Of_Born_Contacts2 = 0; // initialise to zero
	Number_Of_Events = 0; // initialise to zero
	
	Box_Bounds = new double[7]; // [flag to x,y,z], [xlo], [xhi], [ylo], [yhi], [zlo], [zhi]
	Box_Bounds[0] = 0; // initialise [flag to x,y,z] to zero
	cout << "Constructor called" << "\n";
}

// destructor
Data_handling::~Data_handling() {
	delete[] Box_Bounds;
	delete[] Atoms_Info;
	delete[] Initial_Contact_Matrix;
	delete[] Previous_Contact_Matrix;
	delete[] Contact_Matrix;
	delete[] Color_Matrix; //TO-DO
	cout << "Destructor called" << "\n";
}

// read timestep
void Data_handling::read_timestep(string file_line) {
	sscanf(file_line.c_str(),"%ld", &Timestep);
	cout << "read_timestep gives " << Timestep << "\n";
}

// read number of atoms and allocate memory for our matrices
void Data_handling::read_number_of_atoms(string file_line, long initial_timestep) {
	if (Timestep == initial_timestep) { // if initial timestep, allocate memory for our matrices
		sscanf(file_line.c_str(),"%ld", &Number_Of_Atoms); // read at first timestep to get the number of atoms once
		
		cout << "Allocating memory..." << "\n";
		
		Atoms_Info = new double[Number_Of_Atoms*INFO_PER_ATOM]; // [0]=id1, [1]=radius1, [2]=x1, [3]=y1, [4]=z1, [5]=id2, etc
		
		Initial_Contact_Matrix = new int[Number_Of_Atoms*(Number_Of_Atoms-1)/2]; // [0]=atom0_atom1, [1]=atom0_atom2, etc
		
		Previous_Contact_Matrix = new int[Number_Of_Atoms*(Number_Of_Atoms-1)/2]; //TO-DO: [0]=atom0_atom1, [1]=atom0_atom2, etc
		
		Contact_Matrix = new int[Number_Of_Atoms*(Number_Of_Atoms-1)/2]; // [0]=atom0_atom1, [1]=atom0_atom2, etc
		
		Color_Matrix = new int[Number_Of_Atoms*(Number_Of_Atoms-1)/2]; //TO-DO: [0]=color of atom0_atom1, [1]=color of atom0_atom2, etc
		
		cout << "Done allocating memory..." << "\n";
	}
	//cout << "read_number_of_atoms gives " << Number_Of_Atoms << "\n";
}

// read box dimensions
void Data_handling::read_box_bounds(string file_line) {
	if (fabs(Box_Bounds[0]) < SMALL_NUM) { // (if Box_bound == 0) with floating point comparision
		sscanf(file_line.c_str(), "%lf %lf", &Box_Bounds[1], &Box_Bounds[2]);
		Box_Bounds[0]++;
		//cout << "Box_Bounds[0]=" << Box_Bounds[0] << " Box_Bounds[1]=" << Box_Bounds[1] << " Box_Bounds[2]=" << Box_Bounds[2] << "\n";
	}
	else if (fabs(Box_Bounds[0]-1) < SMALL_NUM) { // (if Box_bound == 1) with floating point comparision
		sscanf(file_line.c_str(), "%lf %lf", &Box_Bounds[3], &Box_Bounds[4]);
		Box_Bounds[0]++;
		//cout << "Box_Bounds[0]=" << Box_Bounds[0] << " Box_Bounds[3]=" << Box_Bounds[3] << " Box_Bounds[4]=" << Box_Bounds[4] << "\n";
	}
	else if (fabs(Box_Bounds[0]-2) < SMALL_NUM) { // (if Box_bound == 2) with floating point comparision
		sscanf(file_line.c_str(), "%lf %lf", &Box_Bounds[5], &Box_Bounds[6]);
		Box_Bounds[0] = 0; // reset to 0
		//cout << "Box_Bounds[0]=" << Box_Bounds[0] << " Box_Bounds[5]=" << Box_Bounds[5] << " Box_Bounds[6]=" << Box_Bounds[6] << "\n";
	}
}

// read id, radius, x, y, z, vx, vy, vz, fx, fy, fz
void Data_handling::read_atoms_info(string file_line) {
	long id_tmp, type_tmp;
	double radius_tmp, x_tmp, y_tmp, z_tmp, vx_tmp, vy_tmp, vz_tmp, fx_tmp, fy_tmp, fz_tmp;
	
	sscanf(file_line.c_str(), "%ld %ld %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &id_tmp,&type_tmp,&radius_tmp,&x_tmp,&y_tmp,&z_tmp,&vx_tmp,&vy_tmp,&vz_tmp,&fx_tmp,&fy_tmp,&fz_tmp);
	
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM] = id_tmp; // index starts at 0; Atoms_Info[0] stores id=1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+1] = radius_tmp; // next element, Atoms_Info[1] stores radius1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+2] = x_tmp; // next element, Atoms_Info[2] stores x1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+3] = y_tmp; // next element, Atoms_Info[3] stores y1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+4] = z_tmp; // next element, Atoms_Info[4] stores z1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+5] = vx_tmp; // next element, Atoms_Info[5] stores vx1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+6] = vy_tmp; // next element, Atoms_Info[6] stores vy1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+7] = vz_tmp; // next element, Atoms_Info[7] stores vz1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+8] = fx_tmp; // next element, Atoms_Info[8] stores fx1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+9] = fy_tmp; // next element, Atoms_Info[9] stores fy1
	Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+10] = fz_tmp; // next element, Atoms_Info[10] stores fz1
	
	/*** Uncomment this to check read_atoms_info()
	for (int i = 0; i < INFO_PER_ATOM; i++) cout << Atoms_Info[(id_tmp-1)*INFO_PER_ATOM+i] << " ";
	cout << "\n";
	***/
}

// if first timestep, modify both initial and current contact matrices; if not then modify only current matrix
void Data_handling::modify_contact_matrix(long initial_timestep) {
	
	/*** Uncomment this to check read_atoms_info()
	cout << "List of atoms info...\n";
	for (long i = 0; i < Number_Of_Atoms*INFO_PER_ATOM; i++) cout << Atoms_Info[i] << "\n";
	***/
	
	long k = 0;
	
	// if initial timestep, populate Initial_Contact_Matrix, Previous_Contact_Matrix, Contact_Matrix (they should all be the same)
	if (Timestep == initial_timestep) {
		k = 0;
		for (long i = 0; i < (Number_Of_Atoms-1); i++) {
			for (long j = i+1; j < Number_Of_Atoms; j++) {
				Initial_Contact_Matrix[k] = is_contact(Atoms_Info[i*INFO_PER_ATOM+1], Atoms_Info[i*INFO_PER_ATOM+2], Atoms_Info[i*INFO_PER_ATOM+3], Atoms_Info[i*INFO_PER_ATOM+4],
											Atoms_Info[j*INFO_PER_ATOM+1], Atoms_Info[j*INFO_PER_ATOM+2], Atoms_Info[j*INFO_PER_ATOM+3], Atoms_Info[j*INFO_PER_ATOM+4]);
											
				Previous_Contact_Matrix[k] = is_contact(Atoms_Info[i*INFO_PER_ATOM+1], Atoms_Info[i*INFO_PER_ATOM+2], Atoms_Info[i*INFO_PER_ATOM+3], Atoms_Info[i*INFO_PER_ATOM+4],
											Atoms_Info[j*INFO_PER_ATOM+1], Atoms_Info[j*INFO_PER_ATOM+2], Atoms_Info[j*INFO_PER_ATOM+3], Atoms_Info[j*INFO_PER_ATOM+4]);
				
				Contact_Matrix[k] = is_contact(Atoms_Info[i*INFO_PER_ATOM+1], Atoms_Info[i*INFO_PER_ATOM+2], Atoms_Info[i*INFO_PER_ATOM+3], Atoms_Info[i*INFO_PER_ATOM+4],
											Atoms_Info[j*INFO_PER_ATOM+1], Atoms_Info[j*INFO_PER_ATOM+2], Atoms_Info[j*INFO_PER_ATOM+3], Atoms_Info[j*INFO_PER_ATOM+4]);
				
				Color_Matrix[k] = 0;
				
				/*** Uncomment this to see more verbose result
				cout << Atoms_Info[i*INFO_PER_ATOM] << " and " << Atoms_Info[j*INFO_PER_ATOM] << " "; // id1 and id2
				cout << i*INFO_PER_ATOM << i*INFO_PER_ATOM+1 << i*INFO_PER_ATOM+2 << i*INFO_PER_ATOM+3 << i*INFO_PER_ATOM+4 << " touch "; // indices
				cout << j*INFO_PER_ATOM << j*INFO_PER_ATOM+1 << j*INFO_PER_ATOM+2 << j*INFO_PER_ATOM+3 << j*INFO_PER_ATOM+4 << " ? " <<  Initial_Contact_Matrix[k] << "\n"; // indices, touch
				
				cout<<Atoms_Info[i*INFO_PER_ATOM+1]<<" "<<Atoms_Info[i*INFO_PER_ATOM+2]<<" "<<Atoms_Info[i*INFO_PER_ATOM+3]<<" "<<Atoms_Info[i*INFO_PER_ATOM+4] << " ";
				cout<<Atoms_Info[j*INFO_PER_ATOM+1]<<" "<<Atoms_Info[j*INFO_PER_ATOM+2]<<" "<<Atoms_Info[j*INFO_PER_ATOM+3]<<" "<<Atoms_Info[j*INFO_PER_ATOM+4]<<"\n";
				***/
				
				k++;
			}
		}
		
		// count number of initial contacts
		Initial_Number_Of_Contacts = 0; // initialise to zero
		for (k = 0; k < (Number_Of_Atoms*(Number_Of_Atoms-1)/2); k++) Initial_Number_Of_Contacts = Initial_Number_Of_Contacts + Initial_Contact_Matrix[k];
	}
	
	// modify Previous_Contact_Matrix, Contact_Matrix and Color_Matrix
	k = 0;
	for (long i = 0; i < (Number_Of_Atoms-1); i++) {
		for (long j = i+1; j < Number_Of_Atoms; j++) {
			// update Previous_Contact_Matrix by copying Contact_Matrix
			Previous_Contact_Matrix[k] = Contact_Matrix[k];
			
			// update Contact_Matrix
			Contact_Matrix[k] = is_contact(Atoms_Info[i*INFO_PER_ATOM+1], Atoms_Info[i*INFO_PER_ATOM+2], Atoms_Info[i*INFO_PER_ATOM+3], Atoms_Info[i*INFO_PER_ATOM+4],
								Atoms_Info[j*INFO_PER_ATOM+1], Atoms_Info[j*INFO_PER_ATOM+2], Atoms_Info[j*INFO_PER_ATOM+3], Atoms_Info[j*INFO_PER_ATOM+4]);
			
			// update Color_Matrix
			if (Previous_Contact_Matrix[k] == Contact_Matrix[k]) Color_Matrix[k] = 0; // contact point stays the same
			else if (Previous_Contact_Matrix[k] > Contact_Matrix[k]) Color_Matrix[k] = 1; // contact point is broken
			else Color_Matrix[k] = 2; // contact point is born
			
			/*** Uncomment this to check Color_Matrix
			if (Color_Matrix[k] != 0) cout << Previous_Contact_Matrix[k] << Contact_Matrix[k] << Color_Matrix[k] << "\n";
			***/
			
			/*** Uncomment this to see more verbose result							
			cout << Atoms_Info[i*INFO_PER_ATOM] << " and " << Atoms_Info[j*INFO_PER_ATOM] << " "; // id1 and id2
			cout << i*INFO_PER_ATOM << i*INFO_PER_ATOM+1 << i*INFO_PER_ATOM+2 << i*INFO_PER_ATOM+3 << i*INFO_PER_ATOM+4 << " touch "; // indices
			cout << j*INFO_PER_ATOM << j*INFO_PER_ATOM+1 << j*INFO_PER_ATOM+2 << j*INFO_PER_ATOM+3 << j*INFO_PER_ATOM+4 << " ? " <<  Contact_Matrix[k] << "\n"; // indices, touch
				
			cout<<Atoms_Info[i*INFO_PER_ATOM+1]<<" "<<Atoms_Info[i*INFO_PER_ATOM+2]<<" "<<Atoms_Info[i*INFO_PER_ATOM+3]<<" "<<Atoms_Info[i*INFO_PER_ATOM+4] << " ";
			cout<<Atoms_Info[j*INFO_PER_ATOM+1]<<" "<<Atoms_Info[j*INFO_PER_ATOM+2]<<" "<<Atoms_Info[j*INFO_PER_ATOM+3]<<" "<<Atoms_Info[j*INFO_PER_ATOM+4]<<"\n";
			***/
			
			k++;
		}
	}
	
	// count number of current contacts
	Current_Number_Of_Contacts = 0; // reset to zero
	for (k = 0; k < (Number_Of_Atoms*(Number_Of_Atoms-1)/2); k++) Current_Number_Of_Contacts = Current_Number_Of_Contacts + Contact_Matrix[k];

	//cout << "Current_Number_Of_Contacts is " << Current_Number_Of_Contacts << "\n";
}

// compare two matrices; if timestep=1, surely two matrices are equal
void Data_handling::compare_contact_matrix() {
	Number_Of_Broken_Contacts = 0; // set to zero for counting
	Number_Of_Born_Contacts = 0; // set to zero for counting
	
	for (long k = 0; k < (Number_Of_Atoms*(Number_Of_Atoms-1)/2); k++) {
		if (Contact_Matrix[k] < Initial_Contact_Matrix[k]) Number_Of_Broken_Contacts++;
		if (Contact_Matrix[k] > Initial_Contact_Matrix[k]) Number_Of_Born_Contacts++;
	}
	
	Number_Of_Broken_Contacts2 = 0; // set to zero for counting
	Number_Of_Born_Contacts2 = 0; // set to zero for counting
	
	for (long k = 0; k < (Number_Of_Atoms*(Number_Of_Atoms-1)/2); k++) {
		if (Contact_Matrix[k] < Previous_Contact_Matrix[k]) {
			Number_Of_Broken_Contacts2++;
			Number_Of_Events++;
		}
		if (Contact_Matrix[k] > Previous_Contact_Matrix[k]) {
			Number_Of_Born_Contacts2++;
			Number_Of_Events++;
		}
	}
	
	//cout << "Number_Of_Broken_Contacts is " << Number_Of_Broken_Contacts << "\n";
	//cout << "Number_Of_Born_Contacts is " << Number_Of_Born_Contacts << "\n";
	//cout << "Number_Of_Broken_Contacts2 is " << Number_Of_Broken_Contacts2 << "\n";
	//cout << "Number_Of_Born_Contacts2 is " << Number_Of_Born_Contacts2 << "\n";
	//cout << "Number_Of_Events is " << Number_Of_Events << "\n";
}

// utility function to check if two atoms touch
bool Data_handling::is_contact(double atom1_radius, double atom1_x, double atom1_y, double atom1_z,
							   double atom2_radius, double atom2_x, double atom2_y, double atom2_z) {
	
	if (sqrt(pow(atom1_x-atom2_x,2)+pow(atom1_y-atom2_y,2)+pow(atom1_z-atom2_z,2)) <= (atom1_radius+atom2_radius)) return true;
	else {
		if (((atom1_x-atom1_radius) <= Box_Bounds[1]) || ((atom2_x+atom2_radius) >= Box_Bounds[2])) { // if a part of atom1 is out of the lower bound OR a part of atom2 is out of the upper bound, then shift atom1 to the upper bound
			if (sqrt(pow(atom1_x+(Box_Bounds[2]-Box_Bounds[1])-atom2_x,2)+pow(atom1_y-atom2_y,2)+pow(atom1_z-atom2_z,2)) <= (atom1_radius+atom2_radius)) return true;
		}
		if (((atom1_x+atom1_radius) >= Box_Bounds[2]) || ((atom2_x-atom2_radius) <= Box_Bounds[1])) { // if a part of atom1 is out of the upper bound OR a part of atom2 is out of the lower bound, then shift atom1 to the lower bound
			if (sqrt(pow(atom1_x-(Box_Bounds[2]-Box_Bounds[1])-atom2_x,2)+pow(atom1_y-atom2_y,2)+pow(atom1_z-atom2_z,2)) <= (atom1_radius+atom2_radius)) return true;
		}
		return false;
	}
}

// utility function to calculate contact position
double Data_handling::contact_coordinates(double &x_coord, double &y_coord, double &z_coord,
											double atom1_radius, double atom1_x, double atom1_y, double atom1_z,
											double atom2_radius, double atom2_x, double atom2_y, double atom2_z)  {
	
	x_coord = (atom2_radius/(atom1_radius+atom2_radius))*atom1_x+(atom1_radius/(atom1_radius+atom2_radius))*atom2_x;
	y_coord = (atom2_radius/(atom1_radius+atom2_radius))*atom1_y+(atom1_radius/(atom1_radius+atom2_radius))*atom2_y;
	z_coord = (atom2_radius/(atom1_radius+atom2_radius))*atom1_z+(atom1_radius/(atom1_radius+atom2_radius))*atom2_z;
}

// output number of broken/born contacts
void Data_handling::output_contact_data(string output_filename, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity) {
	ofstream fileOut;
	
	if (Timestep == initial_timestep) fileOut.open(output_filename.c_str()); // if open first time, truncate file
	else fileOut.open(output_filename.c_str(), ios::app); // else append to file
	
	if (fileOut.good()) fileOut << ((Timestep-starting_timestep)*timestep_length*shear_velocity) << "," << Number_Of_Broken_Contacts << "," << Number_Of_Born_Contacts << "\n";
	else cout << "Contact data output file is not good" << "\n";
	
	fileOut.close();
}

// output number of broken/born contacts by comparing previous and current
void Data_handling::output_contact_data2(string output_filename, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity) {
	ofstream fileOut;
	
	if (Timestep == initial_timestep) fileOut.open(output_filename.c_str()); // if open first time, truncate file
	else fileOut.open(output_filename.c_str(), ios::app); // else append to file
	
	if (fileOut.good()) fileOut << ((Timestep-starting_timestep)*timestep_length*shear_velocity) << "," << Number_Of_Broken_Contacts2 << "," << Number_Of_Born_Contacts2 << "\n";
	else cout << "Contact data 2 output file is not good" << "\n";
	
	fileOut.close();
}

// output average number of contacts per atom (2.0*Number_Of_Contacts because we need double counting here)
void Data_handling::output_average_coordination_number (string output_filename, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity) {
	ofstream fileOut;
	
	if (Timestep == initial_timestep) fileOut.open(output_filename.c_str()); // if open first time, truncate file
	else fileOut.open(output_filename.c_str(), ios::app); // else append to file
	
	if (fileOut.good()) fileOut << ((Timestep-starting_timestep)*timestep_length*shear_velocity) << "," << (2.0*Current_Number_Of_Contacts/Number_Of_Atoms) << "\n";
	else cout << "Average coordination number data output file is not good" << "\n";
	
	fileOut.close();
}

// output files containing position of contact points
void Data_handling::output_contact_points(bool is_output_contact_point, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity) {
	if (is_output_contact_point) {
		ofstream fileOut;
		fileOut.open(Output_filename(Timestep).c_str()); // open and truncate
		
		if (fileOut.good()) {
			fileOut << ((Timestep-starting_timestep)*timestep_length*shear_velocity) << "\n"; // first line write shearing distance
			
			double contact_x_coord = 0.0, contact_y_coord = 0.0, contact_z_coord = 0.0; // variables to store contact point's coordinates
			
			long k = 0;
			for (long i = 0; i < (Number_Of_Atoms-1); i++) {
				for (long j = i+1; j < Number_Of_Atoms; j++) {
					if (Contact_Matrix[k] == true || Previous_Contact_Matrix[k] == true) { // if two atoms are in contact, either now or one timestep before
						
						/*** Uncomment this to print out atoms info
						cout << Atoms_Info[i*INFO_PER_ATOM+1]<<","<<Atoms_Info[i*INFO_PER_ATOM+2]<<","<<Atoms_Info[i*INFO_PER_ATOM+3]<<","<<Atoms_Info[i*INFO_PER_ATOM+4];
						cout << Atoms_Info[j*INFO_PER_ATOM+1]<<","<<Atoms_Info[j*INFO_PER_ATOM+2]<<","<<Atoms_Info[j*INFO_PER_ATOM+3]<<","<<Atoms_Info[j*INFO_PER_ATOM+4]<<"\n";
						***/
						
						// calculate their contact point's coordinates
						contact_coordinates(contact_x_coord, contact_y_coord, contact_z_coord,
											Atoms_Info[i*INFO_PER_ATOM+1], Atoms_Info[i*INFO_PER_ATOM+2], Atoms_Info[i*INFO_PER_ATOM+3], Atoms_Info[i*INFO_PER_ATOM+4],
											Atoms_Info[j*INFO_PER_ATOM+1], Atoms_Info[j*INFO_PER_ATOM+2], Atoms_Info[j*INFO_PER_ATOM+3], Atoms_Info[j*INFO_PER_ATOM+4]);
						
						// output contact point's coordinates and its RGB color
						if (Color_Matrix[k] == 0) fileOut << contact_x_coord << "," << contact_y_coord << "," << contact_z_coord << "," << "0,1,0,1,1,1" << "\n"; // same = green
						else if (Color_Matrix[k] == 1) fileOut << contact_x_coord << "," << contact_y_coord << "," << contact_z_coord << "," << "1,0,0,1,0,0" << "\n"; // broken = red
						else if (Color_Matrix[k] == 2) fileOut << contact_x_coord << "," << contact_y_coord << "," << contact_z_coord << "," << "0,0,1,1,1,1" << "\n"; // born = blue
						else fileOut << contact_x_coord << "," << contact_y_coord << "," << contact_z_coord << "," << "0,0,0" << "\n"; // black to check for error
					}
					k++;
				}
			}
		}
		else cout << "Contact positions output file is not good" << "\n";
		
		fileOut.close();
	}
}

// output number of events
void Data_handling::output_number_of_events(string output_filename, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity) {
	ofstream fileOut;
	
	if (Timestep == initial_timestep) fileOut.open(output_filename.c_str()); // if open first time, truncate file
	else fileOut.open(output_filename.c_str(), ios::app); // else append to file
	
	if (fileOut.good()) fileOut << ((Timestep-starting_timestep)*timestep_length*shear_velocity) << "," << Number_Of_Events << "\n";
	else cout << "Number of events data output file is not good" << "\n";
	
	fileOut.close();
}

// output atoms radii
void Data_handling::output_radius_data(string output_filename) {
	ofstream fileOut;
	fileOut.open(output_filename.c_str()); // open and truncate file
	
	if (fileOut.good()) {
		for (long i = 0; i < Number_Of_Atoms; i++) fileOut << Atoms_Info[i*INFO_PER_ATOM+1] << "\n"; // get radius data from Atoms_Info[]
	}
	else {
		cout << "Radius data output file is not good" << "\n";
	}
	
	fileOut.close();
}

// output velocity profile
void Data_handling::output_velocity_profile(string output_filename, double ymin, double ymax, long velocity_layers, long starting_timestep, long initial_timestep, double timestep_length, double shear_velocity) {
	ofstream fileOut;
	
	if (Timestep == initial_timestep) fileOut.open(output_filename.c_str()); // if open first time, truncate file
	else fileOut.open(output_filename.c_str(), ios::app); // else append to file
	
	if (fileOut.good()) {
		fileOut << ((Timestep-starting_timestep)*timestep_length*shear_velocity); // first column write shearing distance
		
		// write mean velocity of layers
		double velocity_sum_in_each_layer[velocity_layers] = {0}; // declare and initialise to zero
		long number_of_atoms_in_each_layer[velocity_layers] = {0}; // declare and initialise to zero
		
		double layer_height = (ymax-ymin)/velocity_layers;
		long layer_index = 0; // initialise to zero
		
		for (long i = 0; i < Number_Of_Atoms; i++) {
			layer_index = (long)((Atoms_Info[i*INFO_PER_ATOM+3])/(layer_height));
			
			velocity_sum_in_each_layer[layer_index] += Atoms_Info[i*INFO_PER_ATOM+5];
			number_of_atoms_in_each_layer[layer_index]++;
		}
		
		for (long j = 0; j < velocity_layers; j++) {
			fileOut << "," << ((velocity_sum_in_each_layer[j])/(number_of_atoms_in_each_layer[j]));
		}
		
		fileOut << "\n"; // new line
		
		/*** Uncomment this to check number of atoms in each layer and sum of them
		long sum_of_atoms = 0;
		for (long i = 0; i < velocity_layers; i++) {
			cout << "Layer " << i << " " << number_of_atoms_in_each_layer[i] << "\n";
			sum_of_atoms += number_of_atoms_in_each_layer[i];
		}
		cout << "Sum " << sum_of_atoms << "\n";
		***/
	}
	else cout << "Velocity profile output file is not good" << "\n";
	
	fileOut.close();
}

// return filename in string format
string Output_filename(long filenumber) {
	stringstream ss;
	ss.str(""); // clear stream
	ss << filenumber; // put number into stream
	return "../output/raw_data/contact_positions/"+ss.str();
}
