
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>
#include <cmath>
#include <robot_delay.h>


int junction_counter = 0;
int i = 1;
int junction_array[6] =/*{0,0,1,0,0,1,5,0,0,6,0,4};{0,0,0,1,0};{5,0,0,6,0,4};*/{0,0,0,0,0,0};
int array_size = sizeof(junction_array)/sizeof(junction_array[0]);
int speed_factor = 15;
int motor_1_initial = 50;
int motor_2_initial = 50;
int distance_sensor_threshold = 200;
int ldr_reading_threshold = 165;
#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;

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
	//rlink.command (WRITE_PORT_0, BinaryToDecimal(11111111));
	//int ldr_reading=rlink.request (ADC4);
	//cout<<ldr_reading<<endl;
	//int tmp;
	//cin>>tmp;
	//rlink.command(WRITE_PORT_5, BinaryToDecimal(tmp));
	rlink.command (WRITE_PORT_0, 255);
	int reading = rlink.request (READ_PORT_0);
	int reading1 = reading bitand 128;
	int reading2 = reading1 >> 7;
	cout << reading2<<endl;
}
}
