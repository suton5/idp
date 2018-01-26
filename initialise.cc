#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#define ROBOT_NUM  15
#include "initialise.h"

int initialise_robot() {

	#ifdef __arm__
	if (!rlink.initialise ()) {
		cout << "Cannot initialise link" << endl;
		rlink.print_errs("    ");
		return -1;
		}               // setup for local hardware
		
	#else
	if (!rlink.initialise (ROBOT_NUM)) { 
		cout << "Cannot initialise link" << endl;
		rlink.print_errs("    ");
		return -1;
	} // setup the link
	#endif
	
return 0;
}
