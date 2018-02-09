#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include <cmath>
#include "initialise.h"

int junction_counter = 0;
int junction_array[4]  = {0,0,0,1};//{1,0,1,1,0,0,4};
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
    rlink.command (MOTOR_1_GO, 128+98);
    rlink.command (MOTOR_2_GO, 102);
    delay (timing);
}

void turn_90_right() {
    rlink.command (MOTOR_1_GO, 180); 
    rlink.command (MOTOR_2_GO, 180); 
    delay(1500);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void turn_135_left() {
    rlink.command (MOTOR_1_GO, 53); 
    rlink.command (MOTOR_2_GO, 53); 
    delay(1000);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void recovery() {
	static int i=1;
	//rlink.command (MOTOR_1_GO, ((i+1)%2)*(10*i)+(i%2)*(128+10*i));
	//rlink.command (MOTOR_2_GO, ((i+1)%2)*(10*i)+(i%2)*(128+10*i));
	delay(150);
	int val = rlink.request (READ_PORT_5);
	int line_sensors = val & 15; //extract 4 most LSB values 

    if (line_sensors == 6 || line_sensors == 2 || line_sensors == 4){
	}
	else {
	rlink.command (BOTH_MOTORS_GO_SAME, ((i+1)%2)*(100)+(i%2)*(228));
	delay(100+10*i);
	i++;
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
        turn_135_left();
    }
    if (junction_array[junction_counter]==4) {
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

        if ((line_sensors bitand 9) == 1 || (line_sensors bitand 9) == 8 || (line_sensors bitand 9) == 9){
            cout<<"BREAKING WITH:"<<line_sensors<<endl;
            break;
        }
         
		
        switch (line_sensors) {
            case 6 : //0110
                cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+98);
                rlink.command (MOTOR_2_GO, 102);
                break;
            case 2 : //0010
                cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 128+98+10);
                rlink.command (MOTOR_2_GO, 102-10);
                break;
            case 4 : //0100
                cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 128+98-10);
                rlink.command (MOTOR_2_GO, 102+10);
                break;
            case 0 : //0000
                cout<<"0000 DANGER: Off path"<<endl;
				recovery();
                break;

        }
        
    }
    
    junction_tester();
    cout<<i<<endl;
    
    }
		return 0;
}
