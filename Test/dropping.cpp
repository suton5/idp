#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include <cmath>
#include "initialise.h"
int speed_factor = 15;
int motor_1_initial = 50;
int motor_2_initial = 50;
int i = 1;

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

void turn_90_left() {
    rlink.command (MOTOR_1_GO, 40); 
    rlink.command (MOTOR_2_GO, 40); 
    delay(800);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void turn_90_right() {
	//delay(20);
    rlink.command (MOTOR_1_GO, 150+speed_factor); 
    rlink.command (MOTOR_2_GO, 150+speed_factor); 
    delay(1500);
    while (true) {
		int val = rlink.request (READ_PORT_5);

		int line_sensors = val bitand 15; //extract 4 most LSB values
		//int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		//int line_sensors_D = (line_sensors bitand 8) >> 3;
        if ((line_sensors_B bitand line_sensors_C)){
            break;
        }
	}
}

void recovery() {
    delay(150);
	int val = rlink.request (READ_PORT_5);
	int line_sensors = val & 15; //extract 4 most LSB values 

    if (line_sensors == 6 || line_sensors == 2 || line_sensors == 4){}
	else {
    rlink.command (BOTH_MOTORS_GO_SAME, ((i+1)%2)*(motor_1_initial+speed_factor)+(i%2)*(128+motor_1_initial+speed_factor));
	
	stopwatch watch;
	watch.start();

    while (watch.read()<100*i) {
		int val = rlink.request (READ_PORT_5);
        int line_sensors = val & 15; //extract 4 most LSB values
       
		if (line_sensors == 2 || line_sensors == 4 || line_sensors == 6) break;		
	}
	
	int total_time = watch.stop();
	//cout<<"Failure number: "<<i<<" Time taken: "<<total_time<<endl;

	i++;
	}
}

void line_follower() {
	    while (true) {
		
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val bitand 15; //extract 4 most LSB values
		int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		int line_sensors_D = (line_sensors bitand 8) >> 3;

        if ((line_sensors_A bitor line_sensors_D) bitand (line_sensors_B bitor line_sensors_C)){
            //cout<<"BREAKING WITH:"<<convertDecimalToBinary(line_sensors)<<endl;
            break;
        }
		  
        switch (line_sensors) {
            case 6 : //0110
                //cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial+speed_factor);
                i=1;
                break;
            case 2 : //0010
                //cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial+5+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial-5+speed_factor);
                break;
            case 4 : //0100
                //cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial-5+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial+5+speed_factor);
                break;
            case 0 : //0000
                //cout<<"0000 DANGER: Off path"<<endl;
				recovery();
                break; 

        }
        
    }
}

void line_follower_straight(int timing) {
		    stopwatch watch1;
			watch1.start();
	//cout<<"Watch created"<<endl;
    while (watch1.read()<timing) {
		//cout<<"Straight"<<endl;	
			
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val bitand 15; //extract 4 most LSB values
		int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		int line_sensors_D = (line_sensors bitand 8) >> 3;
		
		if (line_sensors_B bitand line_sensors_C) {
			                //cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial+speed_factor);
                i=1;
                break;
			}
			
		if (!line_sensors_B bitand line_sensors_C) {
			                //cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial+10+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial-10+speed_factor);
                break;
			}
			if (line_sensors_B bitand !line_sensors_C) {
				                //cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial-10+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial+10+speed_factor);
                break;
			}
			if (!line_sensors_B bitand !line_sensors_C) {
				                //cout<<"0000 DANGER: Off path"<<endl;
				recovery();
                break; 
			}
    }
}

void dropping_1(){
	delay(120);
    rlink.command (MOTOR_1_GO, 150+speed_factor); 
    rlink.command (MOTOR_2_GO, 150+speed_factor); 
    delay(1500);
    //cout<<"Right turn completed"<<endl;
    while (true) {
		int val = rlink.request (READ_PORT_5);

		int line_sensors = val bitand 15; //extract 4 most LSB values
		//int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		//int line_sensors_D = (line_sensors bitand 8) >> 3;
        if ((line_sensors_B bitand line_sensors_C)){
            break;
        }
    }
    //cout<<"Line found"<<endl;
    /*
	line_follower_straight(500);
	rlink.command (MOTOR_1_GO, motor_1_initial+speed_factor-10); 
	rlink.command (MOTOR_2_GO, 128+motor_2_initial+speed_factor-10);
	delay(1700);
	*/
	rlink.command (MOTOR_1_GO, 0); 
	rlink.command (MOTOR_2_GO, motor_2_initial+speed_factor);
	delay(4000);
	rlink.command (MOTOR_2_GO, 0);
	delay(5000); //ADD ACTUAL DROPPING MECHANISM
}

void returning(){
	rlink.command (MOTOR_1_GO, 0); 
	rlink.command (MOTOR_2_GO, 128+motor_2_initial+speed_factor);
	delay(1500);

    //cout<<"Right turn completed"<<endl;
    while (true) {
		int val = rlink.request (READ_PORT_5);

		int line_sensors = val bitand 15; //extract 4 most LSB values
		//int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		//int line_sensors_D = (line_sensors bitand 8) >> 3;
        if ((line_sensors_B bitand line_sensors_C)){
            break;
        }
    }
    //cout<<"Line found"<<endl;
    /*
	line_follower_straight(500);
	rlink.command (MOTOR_1_GO, motor_1_initial+speed_factor-10); 
	rlink.command (MOTOR_2_GO, 128+motor_2_initial+speed_factor-10);
	delay(1700);
	*/
	rlink.command (MOTOR_1_GO, 0); 
	rlink.command (MOTOR_2_GO, 0);
}

void dropping_2() {
	delay(120);
	rlink.command (MOTOR_1_GO, 0); 
	rlink.command (MOTOR_2_GO, motor_2_initial+speed_factor);
	delay(4000);
	rlink.command (MOTOR_2_GO, 0);
	delay(5000); //ADD ACTUAL DROPPING MECHANISM
}
    
int main() {
    
    initialise_robot();
    line_follower();
	dropping_1();
	returning();
	cout<<"Returned"<<endl;
	line_follower_straight(3000);
	cout<<"Left junction behind"<<endl;
	line_follower();
	cout<<"Second junction found"<<endl;
	line_follower_straight(500);
	cout<<"Bypassed junction"<<endl;
	line_follower();
	cout<<"Actual junction found"<<endl;
	dropping_2();
	returning();
	line_follower_straight(10000);

	return 0;
}
