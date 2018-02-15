#include "initialise.h"
#include "motion.h"

void dropping_1() {
  delay(120);
  rlink.command(MOTOR_1_GO, 150 + speed_factor);
  rlink.command(MOTOR_2_GO, 150 + speed_factor);
  delay(1500);
  //cout<<"Right turn completed"<<endl;
  while (true) {
    int val = rlink.request(READ_PORT_5);

    int line_sensors = val bitand 15; //extract 4 most LSB values
    //int line_sensors_A = line_sensors bitand 1;
    int line_sensors_B = (line_sensors bitand 2) >> 1;
    int line_sensors_C = (line_sensors bitand 4) >> 2;
    //int line_sensors_D = (line_sensors bitand 8) >> 3;
    if ((line_sensors_B bitand line_sensors_C)) {
      break;
    }
  }
  //cout<<"Line found"<<endl;
  /*
	line_follower_straight(500);
	rlink.command (MOTOR_1_GO, motor_1_initial+speed_factor-10); 
	rlink.command (MOTOR_2_GO, 128+motor_2_initial+speed_factor-10);
	delay(1700);
	*/
  rlink.command(MOTOR_1_GO, 0);
  rlink.command(MOTOR_2_GO, motor_2_initial + speed_factor);
  delay(4000);
  rlink.command(MOTOR_2_GO, 0);
  delay(5000); //ADD ACTUAL DROPPING MECHANISM
}

void dropping_2() {
  delay(120);
  rlink.command(MOTOR_1_GO, 0);
  rlink.command(MOTOR_2_GO, motor_2_initial + speed_factor);
  delay(4000);
  rlink.command(MOTOR_2_GO, 0);
  delay(5000); //ADD ACTUAL DROPPING MECHANISM
}

void returning() {
  rlink.command(MOTOR_1_GO, 0);
  rlink.command(MOTOR_2_GO, 128 + motor_2_initial + speed_factor);
  delay(1500);

  //cout<<"Right turn completed"<<endl;
  while (true) {
    int val = rlink.request(READ_PORT_5);

    int line_sensors = val bitand 15; //extract 4 most LSB values
    //int line_sensors_A = line_sensors bitand 1;
    int line_sensors_B = (line_sensors bitand 2) >> 1;
    int line_sensors_C = (line_sensors bitand 4) >> 2;
    //int line_sensors_D = (line_sensors bitand 8) >> 3;
    if ((line_sensors_B bitand line_sensors_C)) {
      break;
    }
  }
  //cout<<"Line found"<<endl;
  /*
	line_follower_straight(500);
	rlink.command (MOTOR_1_GO, motor_1_initial+speed_factor-10); 
	rlink.command (MOTOR_2_GO, 128+motor_2_initial+speed_factor-10);
	delay(1700);
	*/
  rlink.command(MOTOR_1_GO, 0);
  rlink.command(MOTOR_2_GO, 0);
}
  
void dropper() {
	dropping_1();
	returning();
	cout<<"Returned"<<endl;
	line_follower_straight(3000);
	cout<<"Left junction behind"<<endl;
	line_follower();
	cout<<"Second junction found"<<endl;
	line_follower_straight(500);
	cout<<"Bypassed junction"<<endl;
	line_follower();
	cout<<"Actual junction found"<<endl;
	dropping_2();
	returning();
	line_follower_straight(10000);
}
