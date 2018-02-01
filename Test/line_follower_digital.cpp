#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>

using namespace std;

#define ROBOT_NUM 15 // The id number (see below)
robot_link rlink;

int MOTOR_MAX = 127;
int MOTOR_MIN = 255;
//sensor1-4 refer to readings from each line-following sensor
//sensor_threshold is minimum reading from line-following sensor

/*
void timed_forward_motion(int timing) {
    //timing in ms
    time_t end = time(NULL) + timing/1000;
    while (time(NULL) <= end) {
        rlink.command (BOTH_MOTORS_GO_SAME, 30);
    }
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
}
 */

void timed_forward_motion(int speed, int timing) {
    //timing in ms
    rlink.command (MOTOR_1_GO, 128-2+speed);
    rlink.command (MOTOR_2_GO, speed+2);
    delay (timing);
}

void turn_90_left() {
    time_t end = time(NULL) + 3;
    while (time(NULL) <= end) {
        //rlink.command (MOTOR_1_GO, 128+50);
        //rlink.command (MOTOR_2_GO, 50);
        cout << "Hi!";
    }
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
}

void turn_135_left() {
    time_t end = time(NULL) + 4.5;
    while (time(NULL) <= end) {
        rlink.command (MOTOR_1_GO, 128+50);
        rlink.command (MOTOR_2_GO, 50);
    }
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
}

void turn_90_right() {
    time_t end = time(NULL) + 3;
    while (time(NULL) <= end) {
        rlink.command (MOTOR_1_GO, 50);
        rlink.command (MOTOR_2_GO, 128+50);
    }
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
}

void turn_135_right() {
    time_t end = time(NULL) + 4.5;
    while (time(NULL) <= end) {
        rlink.command (MOTOR_1_GO, 50);
        rlink.command (MOTOR_2_GO, 128+50);
    }
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
}

void straight_motion_along_line() {
	while (true) {
		int line_sensors, line_sensors_binary;
		cin>>line_sensors_binary;
		line_sensors = BinaryToDecimal(line_sensors_binary);
		
		switch (line_sensors) {
			case 0 : //0000
				cout<<"Stranded"<<endl;
				rlink.command (MOTOR_1_GO, 68);
				rlink.command (MOTOR_2_GO, 128+72);
				break;
			case 1 : //0001
				cout<<"Hard right"<<endl;
				rlink.command (MOTOR_1_GO, 128+68+59);
				rlink.command (MOTOR_2_GO, 72-59);
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
			case 5 : //0101
				cout<<"Reverse"<<endl;
				rlink.command (MOTOR_1_GO, 68);
				rlink.command (MOTOR_2_GO, 128+72);
				break;
			case 6 : //0110
				cout<<"Stay straight"<<endl;
				rlink.command (MOTOR_1_GO, 128+68);
				rlink.command (MOTOR_2_GO, 72);
				break;

	
			case 8 : //1000
				cout<<"Hard left"<<endl;
				rlink.command (MOTOR_1_GO, 128+68-59);
				rlink.command (MOTOR_2_GO, 72+59);
				break;
			/*case 15 : //1111
				cout<<"Left at juntion"<<endl;
				rlink.command (MOTOR_1_GO, 127);
				rlink.command (MOTOR_2_GO, 127);
				break;*/


		}
}
}
void pick_brassicas() {
    // pick pick pick
}

void drop_brassicas() {
    // drop drop drop
}

int main() {
    //sequentially work through circuit
    
    //turn left and get out of box
    turn_90_right();
    timed_forward_motion(2000);
    
    //get to node 1
    while (sensor1 <= sensor_threshold && sensor4 <= sensor_threshold) {
        straight_motion_along_line();
    }
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
    
    //implement picking algorithm
    pick_brassicas();
    
    //turn right and move a bit to ensure second white line does not interrupt
    turn_90_right();
    timed_forward_motion(2000);
    
    //get to node 3, turn right and get to node 4
    while (sensor1 <= sensor_threshold && sensor4 <= sensor_threshold) {
        straight_motion_along_line();
    }
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
    turn_90_right();
    while (sensor1 <= sensor_threshold && sensor4 <= sensor_threshold) {
        straight_motion_along_line();
    }
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
    
    //climb up hill and implement picking algorithm
    turn_135_left();
    pick_brassicas();
    
    //turn around and get down hill towards node 6
    turn_135_right();
    timed_forward_motion(2000);
    
    //implement dropping algorithm
    drop_brassicas();
}
