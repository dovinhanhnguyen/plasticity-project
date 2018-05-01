#ifndef __DISPLAY_INCLUDED__
#define __DISPLAY_INCLUDED__
// Main screen of program

#include <iostream>

void screen_manual (void);
void screen_0_exit (void);
void screen_1_atoms_radius (void);
void screen_2_average_coordination_number (void);
void screen_invalid (void);

// command manual
void screen_manual (void) {
	std::cout << "\n";
	std::cout << "0 - Exit" << "\n";
	std::cout << "1 - Atoms Radius, r" << "\n";
	std::cout << "2 - Average Coordination Number, <Z>" << "\n";
	std::cout << "\n";
	std::cout << "Enter choice: ";
}

// input 0
void screen_0_exit (void) {
	std::cout << "\n" << "Exit" << "\n";
}

// input 1
void screen_1_atoms_radius (void) {
	std::cout << "\n" << "Atoms Radius, r" << "\n";
}

// input 2
void screen_2_average_coordination_number (void) {
	std::cout << "\n" << "Average Coordination Number, <Z>" << "\n";
}

// invalid input
void screen_invalid (void) {
	std::cout << "\n" << "Invalid" << "\n";
}

#endif
