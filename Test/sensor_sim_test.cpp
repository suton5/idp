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
int ldr_reading_threshold = 120;
#define ROBOT_NUM  15                         // The id number (see below)
robot_link  rlink;


void timed_forward_motion(int timing) {
    //timing in ms
    rlink.command (MOTOR_1_GO, 128+98);
    rlink.command (MOTOR_2_GO, 102);
    delay (timing);
}

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

void recovery() {
    delay(150);
	int val = rlink.request (READ_PORT_5);
	int line_sensors = val & 15; //extract 4 most LSB values 

    if (line_sensors == 6 || line_sensors == 2 || line_sensors == 4){}
	else {
    rlink.command (BOTH_MOTORS_GO_SAME, ((i+1)%2)*(motor_2_initial+speed_factor)+(i%2)*(128+motor_1_initial+speed_factor));
	
	stopwatch watch;
	watch.start();

    while (watch.read()<100*i) {
		int val = rlink.request (READ_PORT_5);
        int line_sensors = val & 15; //extract 4 most LSB values
       
		if (line_sensors == 2 || line_sensors == 4 || line_sensors == 6) break;		
	}
	
	int total_time = watch.stop();
	//cout<<"Failure number: "<<i<<" Time taken: "<<total_time<<endl;

	i++;
	}
}

void line_follower_straight(int timing) {
		    stopwatch watch1;
			watch1.start();
	//cout<<"Watch created"<<endl;
    while (watch1.read()<timing) {
		//cout<<"Straight"<<endl;	
			//cout<<watch1.read()<<endl;
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val bitand 15; //extract 4 most LSB values
		int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		int line_sensors_D = (line_sensors bitand 8) >> 3;
		//cout<<line_sensors<<endl;
		
		if (line_sensors_B bitand line_sensors_C) {
			                //cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial+speed_factor);
                i=1;
			}
			
		if (!line_sensors_B bitand line_sensors_C) {
			                //cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial+10+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial-10+speed_factor);
              
			}
			if (line_sensors_B bitand !line_sensors_C) {
				                //cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial-10+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial+10+speed_factor);
              
			}
			if (!line_sensors_B bitand !line_sensors_C) {
				                //cout<<"0000 DANGER: Off path"<<endl;
				recovery();

			}
    }
}

void line_follower() {
	    while (true) {
		
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

void pickup_selector(int choice) {
	if (choice == 0) { //cauliflower
		cout<<"Cauliflower"<<endl;
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
				cout<<"Cabbage"<<endl;

		rlink.command(WRITE_PORT_0, BinaryToDecimal(10111111));//01100000
		int val1 = rlink.request(READ_PORT_0);
		delay(2000);
		rlink.command (MOTOR_4_GO, 255);
		delay(5200);
		rlink.command (MOTOR_4_GO, 0);
		delay(2000);
		rlink.command (MOTOR_4_GO, 100);
		delay(4200);
		rlink.command (MOTOR_4_GO, 0);
		rlink.command(WRITE_PORT_0, BinaryToDecimal(11111111));//00010000
		delay(2000);
		

	}
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
	
	//line_follower_straight(9999999999);

	while (true) {
	rlink.command (WRITE_PORT_0, BinaryToDecimal(11111111));

	//cout<<ldr_reading<<endl;
	
	int reading = rlink.request (READ_PORT_0);
	int reading1 = reading bitand 128;
	int reading2 = reading1 >> 7;
	//cout<<reading2<<endl;
	
	if (reading2==0){
		rlink.command (WRITE_PORT_0, BinaryToDecimal(11110111));
		//rlink.command (BOTH_MOTORS_GO_SAME,0);
			int ldr_reading=rlink.request (ADC4);
		cout << ldr_reading << endl;
		
		
		if (ldr_reading<ldr_reading_threshold) { //cabbage
			cout<<"CABBAGE"<<endl;
			timed_forward_motion(500);
			rlink.command (BOTH_MOTORS_GO_SAME,0);
			delay(2000);
			//pickup_selector(1);
		}
		
		else { //cauliflower
			cout <<"CAULIFLOWER"<<endl;
			timed_forward_motion(500);
			rlink.command (BOTH_MOTORS_GO_SAME,0);
			delay(2000);
			//pickup_selector(0); 
		}
		delay(5000);
	}
	
	
	int val = rlink.request (READ_PORT_5);
	int line_sensors = val bitand 15; //extract 4 most LSB values
	int line_sensors_A = line_sensors bitand 1;
	int line_sensors_B = (line_sensors bitand 2) >> 1;
	int line_sensors_C = (line_sensors bitand 4) >> 2;
	int line_sensors_D = (line_sensors bitand 8) >> 3;
	 
	        if ((line_sensors_A bitor line_sensors_D) bitand (line_sensors_B bitor line_sensors_C)){
            //cout<<"BREAKING WITH:"<<convertDecimalToBinary(line_sensors)<<endl;
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
	

	return 0;

}
