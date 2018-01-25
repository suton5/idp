#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
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
	
	while (true) {
		unsigned val, val_last4;
		unsigned mask;
		mask = (1 << 4) -1;
		val = rlink.request (READ_PORT_5);
		int line_sensors = val & mask;
		//int line_sensors, line_sensors_binary;
		//cin>>line_sensors_binary;
		//line_sensors = BinaryToDecimal(line_sensors_binary);
		
		switch (line_sensors) {
			case 6 : //0110
				cout<<"Stay straight"<<endl;
				rlink.command (MOTOR_1_GO, 128+68);
				rlink.command (MOTOR_2_GO, 72);
				break;
			case 1 : //0001
				cout<<"Hard right"<<endl;
				rlink.command (MOTOR_1_GO, 128+68+59);
				rlink.command (MOTOR_2_GO, 128+10);
				break;
			case 2 : //0010
				cout<<"Slight right"<<endl;
				rlink.command (MOTOR_1_GO, 128+68+30);
				rlink.command (MOTOR_2_GO, 72-30);
				break;
			case 4 : //0100
				cout<<"Slight left"<<endl;
				rlink.command (MOTOR_1_GO, 128+68-30);
				rlink.command (MOTOR_2_GO, 72+30);
				break;	
			case 8 : //1000
				cout<<"Hard left"<<endl;
				rlink.command (MOTOR_1_GO, 128-10);
				rlink.command (MOTOR_2_GO, 72+55);
				break;
			case 15 : //1111
				cout<<"Left at juntion"<<endl;
				rlink.command (MOTOR_1_GO, 127);
				rlink.command (MOTOR_2_GO, 127);
				break;
			default :
				cout<<"Stay straight"<<endl;
				rlink.command (MOTOR_1_GO, 128+68);
				rlink.command (MOTOR_2_GO, 72);
		}
		
	}
			
		return 0;
}
