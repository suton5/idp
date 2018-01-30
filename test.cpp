#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include <cmath>
#include "initialise.h"
#define ROBOT_NUM  15
robot_link  rlink;
int junction_counter = 0;
int junction_array[7]  = {1,0,1,1,0,0,2};
int array_size = sizeof(junction_array)/sizeof(junction_array[0]);

int BinaryToDecimal(int n) {
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0) {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

void timed_forward_motion(int timing) {
    //timing in ms
    rlink.command (MOTOR_1_GO, 128+68);
    rlink.command (MOTOR_2_GO, 72);
    delay (timing);
}

void turn_90_right() {
    rlink.command (MOTOR_1_GO, 128+68);
    rlink.command (MOTOR_2_GO, 72);
    delay(750);
    rlink.command (MOTOR_1_GO, 220); 
    rlink.command (MOTOR_2_GO, 220); 
    delay(750);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void junction_tester() {
    if (junction_array[junction_counter]==0) {
        timed_forward_motion(500);
    }
    if (junction_array[junction_counter]==1) {
        turn_90_right();
    }
    if (junction_array[junction_counter]==2) {
        timed_forward_motion(4500);
    }
    cout<<junction_counter<<endl;
    junction_counter++;
}


int main() {
    
    initialise_robot();
    
    for (int i=0; i<array_size; i++) {
    while (true) {
		
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors bitand 9 == 9){
            cout<<"BREAKING WITH:"<<line_sensors<<endl;
            break;
        }
         
		
        switch (line_sensors) {
            case 6 : //0110
                cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+68);
                rlink.command (MOTOR_2_GO, 72);
                break;
            case 1 : //0001
                cout<<"0001 Hard right"<<endl;
                rlink.command (MOTOR_1_GO, 128+68+59);
                rlink.command (MOTOR_2_GO, 128+10);
                break;
            case 2 : //0010
                cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 128+68+30);
                rlink.command (MOTOR_2_GO, 72-30);
                break;
            case 4 : //0100
                cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 128+68-30);
                rlink.command (MOTOR_2_GO, 72+30);
                break;
            case 8 : //1000
                cout<<"1000 Hard left"<<endl;
                rlink.command (MOTOR_1_GO, 10);
                rlink.command (MOTOR_2_GO, 72+55);
                break;
                
            case 0 : //0000
                cout<<"0000 DANGER: Off path"<<endl;
                rlink.command (MOTOR_1_GO, 20);
                rlink.command (MOTOR_2_GO, 128+20);
                break; 

        }
        
    }
    
    junction_tester();
    cout<<i<<endl;
    
    }
		return 0;
}
