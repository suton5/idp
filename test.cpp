#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include <cmath>
#include "initialise.h"
#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;
int junction_array[3]  = {0,0,1};
int i = 0;

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

	initialise_robot();

	
	while (true) {
		unsigned val;
		//unsigned mask;
		//mask = (1 << 4) -1;
		val = rlink.request (READ_PORT_5);
		unsigned line_sensors = val & 0x0f;
		//int line_sensors, line_sensors_binary;
		//cin>>line_sensors_binary;
		//line_sensors = BinaryToDecimal(line_sensors_binary);
		cout << line_sensors<<endl;
		
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
			default :
				cout<<"Stay straight"<<endl;
				rlink.command (MOTOR_1_GO, 128+68);
				rlink.command (MOTOR_2_GO, 72);
		}
		
	}
			
		return 0;
}
