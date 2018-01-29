#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include <cmath>
//#include "initialise.h"
#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;
int junction_counter = 0;
int junction_array[6]  = {0,1,1,0,1};

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

void timed_forward_motion(int timing) {
    //timing in ms
    rlink.command (MOTOR_1_GO, 128+38);
    rlink.command (MOTOR_2_GO, 42);
    delay (timing);
}

void turn_90_right() {
    rlink.command (MOTOR_1_GO, 255);
    rlink.command (MOTOR_2_GO, 0);
    delay(2300);
}

//unsigned mask;
//mask = (1 << 4) -1;
//int line_sensors, line_sensors_binary;
//cin>>line_sensors_binary;
//line_sensors = BinaryToDecimal(line_sensors_binary);
void junction_tester() {
    int current_junction = junction_counter;
    if (current_junction==0) {
        timed_forward_motion(1000);
    }
    if (current_junction==1) {
        turn_90_right();
    }
    junction_counter++;
}

/*
void line_follower() {
    while (true) {
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
                rlink.command (MOTOR_1_GO, 10);
                rlink.command (MOTOR_2_GO, 72+55);
                break;
            case 0 : //0000
                cout<<"DANGER: Off path"<<endl;
                rlink.command (MOTOR_1_GO, 20);
                rlink.command (MOTOR_2_GO, 128+20);
                break;
        }
        
    }
}
*/
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
	


    for (int i=0; i<5; i++) {

    //CAN WHILE CONDITION BE PUT IN LINE_FOLLOWER ITSELF?
    while (true) {
		
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 0x0f;
		
		if (line_sensors==15 || line_sensors==14 || line_sensors==7){//(line_sensors!=2 && line_sensors!=1 && line_sensors!=6 && line_sensors!=4 && line_sensors!=8 & line_sensors!=0) {
			break;
		}

		
		
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
                rlink.command (MOTOR_1_GO, 10);
                rlink.command (MOTOR_2_GO, 72+55);
                break;
            case 0 : //0000
                cout<<"DANGER: Off path"<<endl;
                rlink.command (MOTOR_1_GO, 20);
                rlink.command (MOTOR_2_GO, 128+20);
                break;
                
            default :
                cout<<"Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+68);
                rlink.command (MOTOR_2_GO, 72);
                break;
        }
        
    }
    //cout<<"BROKEN"<<endl;
    //DO WE WANT IT TO STOP??
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
    
    junction_tester();
    cout<<i<<endl;
    
    }
		return 0;
}
