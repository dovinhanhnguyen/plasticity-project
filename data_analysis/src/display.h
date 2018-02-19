#ifndef __DISPLAY_INCLUDED__
#define __DISPLAY_INCLUDED__
// Main screen of program

#include <iostream>

void print_manual (void);

// print command manual
void print_manual (void) {
	std::cout << "\n";
	std::cout << "0 - Exit" << "\n";
	std::cout << "1 - Atoms Radius, r" << "\n";
	std::cout << "2 - Average Coordination Number, <Z>" << "\n";
	std::cout << "\n";
	std::cout << "Enter choice: ";
}

#endif
