#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <cmath>
#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;

void binary(int num)

{

    int rem;

 

    if (num <= 1)

    {

        cout << num;

        return;

    }

    rem = num % 2;

    binary(num / 2);

    cout << rem;

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
rlink.command (MOTOR_2_GO, 127);
//rlink.command (STOP_IF_HIGH, 0x05);
rlink.command (STOP_SELECT, 5);

int stat = rlink.request (STATUS);

binary(stat);
int tmp;
cin >> tmp;
return 0;
}
