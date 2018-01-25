#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include <stopwatch.h>
#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;
stopwatch watch;

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
//1st test
/*
watch.start();
for (int i=0; i<10; i++) {
rlink.command (MOTOR_3_GO, 30);
delay (3000);
rlink.command (MOTOR_3_GO, 127);
delay (3000);
}
int etime = watch.stop();
cout << etime << endl;
*/

//2nd test

watch.start();
for (int i=0; i<=255; i++) {
	int val1 = rlink.request (READ_PORT_5);
	rlink.command (WRITE_PORT_5, i);
	//cout<<val1<<endl;
}
int etime = watch.stop();
cout << etime << endl;

return 0;
}
