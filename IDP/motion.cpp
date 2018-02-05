#include "initialise.h"

int junction_counter = 0;
int i = 1;
int junction_array[10] = {0,0,1,0,0,1,1,0,0,4};
int array_size = sizeof(junction_array)/sizeof(junction_array[0]);


void timed_forward_motion(int timing) {
    //timing in ms
    rlink.command (MOTOR_1_GO, 128+98);
    rlink.command (MOTOR_2_GO, 102);
    delay (timing);
}

void turn_90_left() {
    rlink.command (MOTOR_1_GO, 53); 
    rlink.command (MOTOR_2_GO, 53); 
    delay(1500);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void turn_90_right() {
    rlink.command (MOTOR_1_GO, 180); 
    rlink.command (MOTOR_2_GO, 180); 
    delay(1500);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void turn_135_left() {
    rlink.command (MOTOR_1_GO, 53); 
    rlink.command (MOTOR_2_GO, 53); 
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
    rlink.command (MOTOR_1_GO, 180); 
    rlink.command (MOTOR_2_GO, 180); 
    delay(1000);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}


void recovery() {
    cout<<i<<endl;
    delay(150);
	int val = rlink.request (READ_PORT_5);
	int line_sensors = val & 15; //extract 4 most LSB values 

    if (line_sensors == 6 || line_sensors == 2 || line_sensors == 4){}
	else {
    rlink.command (BOTH_MOTORS_GO_SAME, ((i+1)%2)*(100)+(i%2)*(228));
	
	stopwatch watch;
	watch.start();

    while (watch.read()<200*i) {
		int val = rlink.request (READ_PORT_5);
        int line_sensors = val & 15; //extract 4 most LSB values
       
		if (line_sensors == 2 || line_sensors == 4 || line_sensors == 6) break;		
	}
	
	int total_time = watch.stop();
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
            cout<<"BREAKING WITH:"<<line_sensors<<endl;
            break;
        }
		  
        switch (line_sensors) {
            case 6 : //0110
                //cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+98);
                rlink.command (MOTOR_2_GO, 102);
                i=1;
                break;
            case 2 : //0010
                //cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 128+98+10);
                rlink.command (MOTOR_2_GO, 102-10);
                break;
            case 4 : //0100
                //cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 128+98-10);
                rlink.command (MOTOR_2_GO, 102+10);
                break;
            case 0 : //0000
                //cout<<"0000 DANGER: Off path"<<endl;
				recovery();
                break; 

        }
        
    }
}

void junction_tester() {
    if (junction_array[junction_counter]==0) {
        timed_forward_motion(500);
    }
    if (junction_array[junction_counter]==1) {
        turn_90_right();
    }
    if (junction_array[junction_counter]==2) {
        turn_135_left();
    }
    if (junction_array[junction_counter]==3) {
        turn_135_right();
    }
    if (junction_array[junction_counter]==4) {
        timed_forward_motion(1000);
    }
    if (junction_array[junction_counter]==5) {
        //dropping junction 1;
    }
    if (junction_array[junction_counter]==6) {
        //dropping junction 2;
    }
    junction_counter++;
}

int main() {
    
    initialise_robot();
    
    for (int j=0; j<array_size; j++) {
    line_follower();
    junction_tester();
    cout<<j<<endl;
}
		return 0;
}
