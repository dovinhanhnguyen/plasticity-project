#include "script.h"

int main() {
	ifstream fileIn;
	string line;
	parser_status current_parser_status = IDLE;

	for (long i = INITIAL_TIMESTEP; i <= INITIAL_TIMESTEP+SHEAR_TIMESTEPS; i += NEVERY) { // parsing SHEAR_NUMBER/NEVERY of files, starting with INITIAL_TIMESTEP file
		fileIn.open(Filename(i).c_str(), ios::binary);

		if (fileIn.good()) {
			while (getline(fileIn,line)) {
				if (line.find("ITEM: TIMESTEP") != string::npos) current_parser_status = TIMESTEP; // next line contains value of timestep
				else if (line.find("ITEM: NUMBER OF ATOMS") != string::npos) current_parser_status = NUMBER_OF_ATOMS; // next line contains total number of atoms
				else if (line.find("ITEM: BOX BOUNDS") != string::npos) current_parser_status = BOX_BOUNDS; // next 3 lines contain box dimension
				else if (line.find("ITEM: ATOMS") != string::npos) current_parser_status = ATOMS_INFO; // next number-of-atoms lines contain atoms info
				else {
					switch (current_parser_status) {
						case IDLE:
							break;
						case TIMESTEP:
							dataHandler.read_timestep(line);
							break;
						case NUMBER_OF_ATOMS:
							dataHandler.read_number_of_atoms(line, INITIAL_TIMESTEP);
							break;
						case BOX_BOUNDS:
							dataHandler.read_box_bounds(line);
							break;
						case ATOMS_INFO:
							dataHandler.read_atoms_info(line);
							break;
					}
				}
			}
			dataHandler.modify_contact_matrix(INITIAL_TIMESTEP);
			dataHandler.compare_contact_matrix();
			dataHandler.output_contact_data("../output/raw_data/contact_data.csv", STARTING_TIMESTEP, INITIAL_TIMESTEP, TIMESTEP_LENGTH, SHEAR_VELOCITY);
			dataHandler.output_average_coordination_number("../output/raw_data/average_coordination_number_data.csv", STARTING_TIMESTEP, INITIAL_TIMESTEP, TIMESTEP_LENGTH, SHEAR_VELOCITY);
			dataHandler.output_contact_points(IS_OUTPUT_CONTACT_POINTS, STARTING_TIMESTEP, INITIAL_TIMESTEP, TIMESTEP_LENGTH, SHEAR_VELOCITY);
		}
		else {
			cout << "fileIn " << i << " is not good" << "\n";
		}

		fileIn.close();
	}
	dataHandler.output_radius_data("../output/raw_data/radius_data.csv");
}

// return filename in string format
string Filename(long filenumber) {
	stringstream ss;
	ss.str(""); // clear stream
	ss << filenumber; // put number into stream
	return "../post/full_info"+ss.str()+".Shear";
}
