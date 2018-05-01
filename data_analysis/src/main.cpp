#include "main.h"

int main() {
	//~ Experiment exp;
	//~ exp.print_experiment_parameters();
	
	bool flag = false;
	while (flag == false) {
		screen_manual();
		
		std::string input;
		getline(std::cin, input);
		
		if (input == "0") {
			screen_0_exit();
			flag = true;
		}
		else if (input == "1") {
			screen_1_atoms_radius();
			
			Atom_radius atom_radius_analysis;
			atom_radius_analysis.analyse();
			atom_radius_analysis.output();
		}
		else if (input == "2") {
			screen_2_average_coordination_number();
			
			// function to analyse <z>
		}
		else {
			screen_invalid();
		}
	}
}
