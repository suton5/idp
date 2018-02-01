#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
using namespace std;

#define ROBOT_NUM 15 // The id number (see below)
robot_link rlink;

int sensor1, sensor2, sensor3, sensor4;
int sensor_threshold = 5;
int MOTOR_MAX = 127;
int MOTOR_MIN = 255;
//sensor1-4 refer to readings from each line-following sensor
//sensor_threshold is minimum reading from line-following sensor

void timed_forward_motion(int timing) {
    //timing in ms
    time_t end = time(NULL) + timing/1000;
    while (time(NULL) <= end) {
        rlink.command (BOTH_MOTORS_GO_SAME, 30);
    }
    rlink.command (BOTH_MOTORS_GO_SAME, 0);
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
    //implement PID control for line-following
    int error;
    int turn;
    int integral = 0;
    int previous_error = 0;
    int derivative = 0;
    float Kp = 0.1;
    float Ki = 0.2;
    float Kd = 1.0;
    int motor_1 = 70;
    int motor_2 = 70;
    rlink.command (BOTH_MOTORS_GO_SAME, 70);
    while (true) {
        error = sensor2 - sensor3; //if positive (assuming white gives higher reading), too much to the right and vice versa
        integral = integral + error;
        derivative = error - previous_error;
        turn = Kp*error + Ki*integral + Kd*derivative;
        motor_1 -= turn;
        motor_2 += turn;

		if (motor_1 > MOTOR_MAX) motor_1 = MOTOR_MAX;
        if (motor_1 < 0) motor_1 = 0;
		if (motor_2 > MOTOR_MAX) motor_2 = MOTOR_MAX;
        if (motor_2 < 0) motor_2 = 0;
        
        rlink.command (MOTOR_1_GO, motor_1);
        rlink.command (MOTOR_2_GO, motor_2);
		previous_error = error;
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
