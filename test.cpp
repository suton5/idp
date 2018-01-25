#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <cmath>
#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;


int BinaryToDecimal(int n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
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
	
	int line_sensors, line_sensors_binary;
	cin>>line_sensors_binary;
	line_sensors = BinaryToDecimal(line_sensors_binary);
	
	switch (line_sensors) {
		case 6 :
			cout<<"Success"<<endl;
			break;
		default :
			cout<<"Failure"<<endl;
	}
		
	return 0;
}
