#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>
#include <cmath>
#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;

unsigned createMask(unsigned a, unsigned b)
{
   unsigned r = 0;
   for (unsigned i=a; i<=b; i++)
       r |= 1 << i;

   return r;
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
unsigned v = 1+4;
unsigned val, val_last4;

//rlink.command (WRITE_PORT_5, v);
val = rlink.request (READ_PORT_5);
unsigned r = createMask(4, 7);
val_last4 = (r & val)/pow(2, 4);
cout << val_last4 <<endl;

val &= ~0xf;
val |= v & 0xf;
rlink.command (WRITE_PORT_5, val);

return 0;

}
