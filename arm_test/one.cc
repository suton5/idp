// one.cc
#include <robot_instr.h>
#include <robot_link.h>
#include "header.h"

int request() {
return rlink.request (TEST_INSTRUCTION); // send test instruction
}
