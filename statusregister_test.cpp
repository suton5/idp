#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <robot_instr.h>
#include <robot_link.h>
#include <cmath>
#include "initialise.h"

#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;

int main() {

initialise_robot();
  
rlink.command (MOTOR_2_GO, 127);
//rlink.command (STOP_IF_HIGH, 0x05);
//rlink.command (STOP_SELECT, 5);

//int stat = rlink.request (STATUS);

//binary(stat);
int tmp;
cin >> tmp;
return 0;
}
