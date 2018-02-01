#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>
#include <cmath>
#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;

int convertDecimalToBinary(int n) {
    long long binaryNumber = 0;
    int remainder, i = 1, step = 1;
    while (n!=0) {
        remainder = n%2;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}

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
	
	unsigned val;
	while (true) {
	//rlink.command (WRITE_PORT_5, v);
	val = rlink.request (READ_PORT_0);
	//unsigned r = createMask(0, 3);
	cout << val<<endl;

	//val &= ~0xf;
	//val |= v & 0xf;
	//rlink.command (WRITE_PORT_5, val);
	}
	
	return 0;

}
