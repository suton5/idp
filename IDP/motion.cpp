#include "initialise.h"
#include "motion.h"
#include "pick_brassicas.h"
#include "drop_brassicas.h"

int junction_counter = 0;
int i = 1;
int junction_array[10] ={0,0,7,5,2,0,0,1,8,9};/*{0,0,1,0,0,1,5,0,0,6,0,4};{0,0,0,1,0};{5,0,0,6,0,4};{7,2,0,0,1,5,0,0,6,0,4};*/
int array_size = sizeof(junction_array)/sizeof(junction_array[0]);
int speed_factor = 15;
int motor_1_initial = 50;
int motor_2_initial = 50;

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

void timed_forward_motion(int timing) {
    //timing in ms
    rlink.command (MOTOR_1_GO, 128+motor_1_initial+speed_factor);
    rlink.command (MOTOR_2_GO, motor_2_initial+speed_factor);
    delay (timing);
}

void turn_90_left() {
	//delay(20);
    rlink.command (MOTOR_1_GO, 23+speed_factor); 
    rlink.command (MOTOR_2_GO, 23+speed_factor); 
    delay(1500);
    while (true) {
		int val = rlink.request (READ_PORT_5);

		int line_sensors = val bitand 15; //extract 4 most LSB values
		//int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		//int line_sensors_D = (line_sensors bitand 8) >> 3;
        if ((line_sensors_B bitand line_sensors_C)){
            break;
        }
	}
}

void turn_90_right() {
	//delay(20);
    rlink.command (MOTOR_1_GO, 150+speed_factor); 
    rlink.command (MOTOR_2_GO, 150+speed_factor); 
    delay(1500);
    while (true) {
		int val = rlink.request (READ_PORT_5);

		int line_sensors = val bitand 15; //extract 4 most LSB values
		//int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		//int line_sensors_D = (line_sensors bitand 8) >> 3;
        if ((line_sensors_B bitand line_sensors_C)){
            break;
        }
	}
}

void turn_135_left() {
    rlink.command (MOTOR_1_GO, 40); 
    rlink.command (MOTOR_2_GO, 40); 
    delay(1000);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void turn_135_right() {
    rlink.command (MOTOR_1_GO, 167); 
    rlink.command (MOTOR_2_GO, 167); 
    delay(1000);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void turn_180_left() {
	//delay(20);
    rlink.command (MOTOR_1_GO, 23+speed_factor); 
    rlink.command (MOTOR_2_GO, 23+speed_factor); 
    delay(8000);
    while (true) {
		int val = rlink.request (READ_PORT_5);

		int line_sensors = val bitand 15; //extract 4 most LSB values
		//int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		//int line_sensors_D = (line_sensors bitand 8) >> 3;
        if ((line_sensors_B bitand line_sensors_C)){
            break;
        }
	}
}

void turn_180_right() {
	//delay(20);
    rlink.command (MOTOR_1_GO, 150+speed_factor); 
    rlink.command (MOTOR_2_GO, 150+speed_factor); 
    delay(8000);
    while (true) {
		int val = rlink.request (READ_PORT_5);

		int line_sensors = val bitand 15; //extract 4 most LSB values
		//int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		//int line_sensors_D = (line_sensors bitand 8) >> 3;
        if ((line_sensors_B bitand line_sensors_C)){
            break;
        }
	}
}

void recovery() {
    delay(150);
	int val = rlink.request (READ_PORT_5);
	int line_sensors = val & 15; //extract 4 most LSB values 

    if (line_sensors == 6 || line_sensors == 2 || line_sensors == 4){}
	else {
    rlink.command (BOTH_MOTORS_GO_SAME, ((i+1)%2)*(motor_1_initial+speed_factor)+(i%2)*(128+motor_1_initial+speed_factor));
	
	stopwatch watch;
	watch.start();

    while (watch.read()<100*i) {
		int val = rlink.request (READ_PORT_5);
        int line_sensors = val & 15; //extract 4 most LSB values
       
		if (line_sensors == 2 || line_sensors == 4 || line_sensors == 6) break;		
	}
	
	int total_time = watch.stop();
	cout<<"Failure number: "<<i<<" Time taken: "<<total_time<<endl;

	i++;
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

void line_follower_straight(int timing) {
	stopwatch watch1;
	watch1.start();
    while (watch1.read()<timing) {			
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val bitand 15; //extract 4 most LSB values
		int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		int line_sensors_D = (line_sensors bitand 8) >> 3;
		
		if (line_sensors_B bitand line_sensors_C) {
			    //cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial+speed_factor);
                i=1;
                break;
			}
			
		if (!line_sensors_B bitand line_sensors_C) {
			    //cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial+10+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial-10+speed_factor);
                break;
			}
			if (line_sensors_B bitand !line_sensors_C) {
				//cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 128+motor_1_initial-10+speed_factor);
                rlink.command (MOTOR_2_GO, motor_2_initial+10+speed_factor);
                break;
			}
			if (!line_sensors_B bitand !line_sensors_C) {
				//cout<<"0000 DANGER: Off path"<<endl;
				recovery();
                break; 
			}
    }
}

void junction_tester() {
    if (junction_array[junction_counter]==0) {
        timed_forward_motion(1000);
    }
    if (junction_array[junction_counter]==1) {
        turn_90_right();
    }
    if (junction_array[junction_counter]==2) {
        turn_90_left();
    }
    if (junction_array[junction_counter]==3) {
        turn_135_right();
    }
    if (junction_array[junction_counter]==4) {
		turn_135_left();
    }
    if (junction_array[junction_counter]==5) {
        turn_180_right();
    }
    if (junction_array[junction_counter]==6) {
		turn_180_left();
	}
    if (junction_array[junction_counter]==7) {
        brassica_detector();
    }
    if (junction_array[junction_counter]==8) {
        dropper();
    }
    if (junction_array[junction_counter]==9) {
        timed_forward_motion(800);
        rlink.command (BOTH_MOTORS_GO_SAME, 0);
    }
    
    junction_counter++;
}
