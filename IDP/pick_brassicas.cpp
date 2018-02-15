#include "initialise.h"
#include "motion.h"

int distance_sensor_threshold = 200;
int ldr_reading_threshold = 100;

void pickup_selector(int choice) {
	if (choice == 0) { //cabbage
		rlink.command(WRITE_PORT_0, 0);
		delay(2000);
		rlink.command (MOTOR_4_GO, 255);
		delay(4000);
		rlink.command (MOTOR_4_GO, 0);
		delay(2000);
		rlink.command (MOTOR_4_GO, 100);
		delay(2100);
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
		delay(2100);
		rlink.command(WRITE_PORT_0, 96);
		delay(2000);
	}
}

void brassica_detector() {
	while (true) {
	rlink.command (WRITE_PORT_0, 247);
	int ldr_reading=rlink.request (ADC4);
	//cout<<ldr_reading<<endl;
	int distance_reading = rlink.request (READ_PORT_0);
	//cout<<distance_reading<<endl;
	if (distance_reading<distance_sensor_threshold){
		delay(200);
		rlink.command (BOTH_MOTORS_GO_SAME,0);
		if (ldr_reading<ldr_reading_threshold) { //cabbage
			line_follower_straight(750-200);
			rlink.command (BOTH_MOTORS_GO_SAME,0);
			
			pickup_selector(0);
		}
		
		if (ldr_reading>ldr_reading_threshold) { //cauliflower
			line_follower_straight(750-200);
			rlink.command (BOTH_MOTORS_GO_SAME,0);
			
			pickup_selector(1);
		} 
	}
	
	int val = rlink.request (READ_PORT_5);
	int line_sensors = val bitand 15; //extract 4 most LSB values
	int line_sensors_A = line_sensors bitand 1;
	int line_sensors_B = (line_sensors bitand 2) >> 1;
	int line_sensors_C = (line_sensors bitand 4) >> 2;
	int line_sensors_D = (line_sensors bitand 8) >> 3;
	 
	        if ((line_sensors_A bitor line_sensors_D) bitand (line_sensors_B bitor line_sensors_C)){
            cout<<"BREAKING WITH:"<<convertDecimalToBinary(line_sensors)<<endl;
            break;
        } 
	
	
	switch (line_sensors) {
		case 6 : //0110
			//cout<<"0110 Stay straight"<<endl;
			rlink.command (MOTOR_1_GO, 128+motor_1_initial+speed_factor);
			rlink.command (MOTOR_2_GO, motor_2_initial+speed_factor);
			i=1;
			break;
		case 2 : //0010
			//cout<<"0010 Slight right"<<endl;
			rlink.command (MOTOR_1_GO, 128+motor_1_initial+5+speed_factor);
			rlink.command (MOTOR_2_GO, motor_2_initial-5+speed_factor);
			break;
		case 4 : //0100
			//cout<<"0100 Slight left"<<endl;
			rlink.command (MOTOR_1_GO, 128+motor_1_initial-5+speed_factor);
			rlink.command (MOTOR_2_GO, motor_2_initial+5+speed_factor);
			break;
		case 0 : //0000
			//cout<<"0000 DANGER: Off path"<<endl;
			recovery();
			break; 

    }
	}
}
