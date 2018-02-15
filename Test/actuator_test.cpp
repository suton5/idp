#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include <cmath>
#define ROBOT_NUM  15
robot_link  rlink;

//high bit 5, contract box
//high bit 6, contract claw
int choice;

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

void selector(int choice) {
	if (choice == 0) { //cabbage
		rlink.command(WRITE_PORT_0, 0);
		delay(2000);
		rlink.command (MOTOR_4_GO, 255);
		delay(4000);
		rlink.command (MOTOR_4_GO, 0);
		delay(2000);
		rlink.command (MOTOR_4_GO, 100);
		delay(2300);
		rlink.command(WRITE_PORT_0, 64);
		delay(2000);
	}
	
	if (choice == 1) { //cauliflower
		rlink.command(WRITE_PORT_0, 32);
		delay(2000);
		rlink.command (MOTOR_4_GO, 255);
		delay(4000);
		rlink.command (MOTOR_4_GO, 0);
		delay(2000);
		rlink.command (MOTOR_4_GO, 100);
		delay(2300);
		rlink.command(WRITE_PORT_0, 96);
		delay(2000);
	}
}
int initialise_robot() {

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
	
return 0;
}

int main(){
initialise_robot();
selector(1);
//rlink.command(WRITE_PORT_0, 0);
/*
for (int i=0; i<9; i++){
rlink.command(WRITE_PORT_0, 0);
delay(2000);
rlink.command (MOTOR_4_GO, 255);
delay(4000);
rlink.command (MOTOR_4_GO, 0);
delay(2000);
rlink.command (MOTOR_4_GO, 100);
delay(4100);
rlink.command(WRITE_PORT_0, 255);
delay(2000);*/
}


