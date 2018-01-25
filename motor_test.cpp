#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <cmath>
#define ROBOT_NUM  15                         // The id number (see below)
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
//int val;
//val = rlink.request (READ_PORT_5);
//cout << val <<endl;

//unsigned speed;

//rlink.command (MOTOR_3_GO, 255);
//while (true) {
//rlink.command (MOTOR_1_GO, 255-100);
rlink.command (MOTOR_2_GO, 127);
//rlink.command (MOTOR_3_GO, 127);
//rlink.command (MOTOR_4_GO, 127);

//}
int tmp;
cin >> tmp;

//speed=rlink.request(MOTOR_2);
//cout << "Hi"<<speed<<endl;
return 0;
}

