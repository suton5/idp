#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include <cmath>
#define ROBOT_NUM  15
robot_link  rlink;




int main() {
	
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
	while (true) {
	
	int val=rlink.request(ADC4);
	cout<<val<<endl;
	
	}
	//dropping_1();
	}
