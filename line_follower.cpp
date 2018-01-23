#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int sensor1, sensor2, sensor3, sensor4, mA_power, mB_power;
int sensor_threshold = 5;
//sensor1-4 refer to readings from each line-following sensor
//mA_power, mB_power refer to signal output to left and right drive motor, respectively
//sensor_threshold is minimum reading from line-following sensor

void timed_forward_motion(int timing) {
    //timing in ms
    time_t end = time(NULL) + timing/1000;
    while (time(NULL) <= end) {
        mA_power = 30;
        mB_power = 30;
    }
    mA_power = 0;
    mB_power = 0;
}

void turn_90_left() {
    time_t end = time(NULL) + 3;
    while (time(NULL) <= end) {
        //mA_power = -50;
        //mB_power = 50;
        cout << "Hi!";
    }
    mA_power = 0;
    mB_power = 0;
}

void turn_135_left() {
    time_t end = time(NULL) + 4.5;
    while (time(NULL) <= end) {
        mA_power = -50;
        mB_power = 50;
    }
    mA_power = 0;
    mB_power = 0;
}

void turn_90_right() {
    time_t end = time(NULL) + 3;
    while (time(NULL) <= end) {
        mA_power = 50;
        mB_power = -50;
    }
    mA_power = 0;
    mB_power = 0;
}

void turn_135_right() {
    time_t end = time(NULL) + 4.5;
    while (time(NULL) <= end) {
        mA_power = 50;
        mB_power = -50;
    }
    mA_power = 0;
    mB_power = 0;
}

void straight_motion_along_line() {
    int error;
    int turn;
    int integral = 0;
    int previous_error = 0;
    int derivative = 0;
    float Kp = 0.1;
    float Ki = 0.2;
    float Kd = 1.0;
    mA_power = 70;
    mB_power = 70;
    while (true) {
        error = sensor2 - sensor3; //if positive, too much to the right and vice versa
        integral = integral + error;
        derivative = error - previous_error;
        turn = Kp*error + Ki*integral + Kd*derivative;
        mA_power = mA_power - turn;
        mB_power = mB_power + turn;
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
    mA_power = 0;
    mB_power = 0;
    
    //implement picking algorithm
    pick_brassicas();
    
    //turn right and move a bit to ensure second white line does not interrupt
    turn_90_right();
    timed_forward_motion(2000);
    
    //get to node 3, turn right and get to node 4
    while (sensor1 <= sensor_threshold && sensor4 <= sensor_threshold) {
        straight_motion_along_line();
    }
    mA_power = 0;
    mB_power = 0;
    turn_90_right();
    while (sensor1 <= sensor_threshold && sensor4 <= sensor_threshold) {
        straight_motion_along_line();
    }
    mA_power = 0;
    mB_power = 0;
    
    //climb up hill and implement picking algorithm
    turn_135_left();
    pick_brassicas();
    
    //turn around and get down hill towards node 6
    turn_135_right();
    timed_forward_motion(2000);
    
    //implement dropping algorithm
    drop_brassicas();
}
