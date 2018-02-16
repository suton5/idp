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

//low bit 3, turn on LED
//high bit 5, change box
//high bit 6, claw in
int choice;

int DecimalToBinary(int n) {
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

void selector(int choice, int tmp1, int tmp2) {
	if (choice == 0) { //cauliflower
		rlink.command(WRITE_PORT_0, BinaryToDecimal(10011111));
		delay(2000);
		rlink.command (MOTOR_4_GO, 255);
		delay(5200); //3500
		rlink.command (MOTOR_4_GO, 0);
		delay(2000);
		rlink.command (MOTOR_4_GO, 100);
		delay(4200); //2000
		rlink.command (MOTOR_4_GO, 0);
		rlink.command(WRITE_PORT_0, BinaryToDecimal(11011111));
		delay(2000);
	}
	
	if (choice == 1) { //cabbage
		rlink.command(WRITE_PORT_0, BinaryToDecimal(10111111));//01100000
		delay(2000);
		rlink.command (MOTOR_4_GO, 255);
		delay(5200);
		rlink.command (MOTOR_4_GO, 0);
		delay(2000);
		rlink.command (MOTOR_4_GO, 100);
		delay(4200);
		rlink.command (MOTOR_4_GO, 0);
		rlink.command(WRITE_PORT_0, BinaryToDecimal(11111111));
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


/*
while (true) {
int tmp;
int motor;
int delay_m;
cout << "Binary?" << endl;
cin >> tmp;
cout << "Motor?" << endl;
cin >> motor;
cout << "Delay?" << endl;
cin >> delay_m;
rlink.command(WRITE_PORT_0, BinaryToDecimal(tmp));
rlink.command (MOTOR_4_GO, motor);
delay(delay_m);
}*/


while (true){
	int tmp1;
	cin>>tmp1;
	int tmp2;
	cin>>tmp2;
selector(0, tmp1, tmp2);

}

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


