#include "main.h"

int main() {
	Experiment exp;
	exp.print_experiment_parameters();
	
	bool flag = false;
	while (flag == false) {
		print_manual();
		
		std::string input;
		getline(std::cin, input);
		
		if (input == "0") {
			std::cout << "\n" << "Exit" << "\n";
			flag = true;
		}
		else if (input == "1") {
			std::cout << "\n" << "Atoms Radius, r" << "\n";
			
			// function to analyse r
		}
		else if (input == "2") {
			std::cout << "\n" << "Average Coordination Number, <Z>" << "\n";
			
			// function to analyse <z>
		}
		else {
			std::cout << "\n" << "Invalid" << "\n";
		}
	}
}
