#include "initialise.h"
#include "motion.h"

int junction_counter = 0;
int i = 1;
int junction_array[12] ={0,0,1,0,0,1,5,0,0,6,0,4};//{0,0,1,1,1,4};//;//{5,0,6,4};
int array_size = sizeof(junction_array)/sizeof(junction_array[0]);
int speed_factor = 0;


void timed_forward_motion(int timing) {
    //timing in ms
    rlink.command (MOTOR_1_GO, 128+68+speed_factor);
    rlink.command (MOTOR_2_GO, 72+speed_factor);
    delay (timing);
}

void turn_90_left() {
    rlink.command (MOTOR_1_GO, 40); 
    rlink.command (MOTOR_2_GO, 40); 
    delay(800);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
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

void dropping_1(){
	//delay(120);
    rlink.command (MOTOR_1_GO, 150+speed_factor); 
    rlink.command (MOTOR_2_GO, 150+speed_factor); 
    delay(1000);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val bitand 15; //extract 4 most LSB values
		//int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		//int line_sensors_D = (line_sensors bitand 8) >> 3;
        if ((line_sensors_B bitand line_sensors_C)){
			rlink.command (MOTOR_1_GO, 68+speed_factor); 
			rlink.command (MOTOR_2_GO, 128+72+speed_factor);
			delay(1100);
			rlink.command (MOTOR_1_GO, 0); 
			rlink.command (MOTOR_2_GO, 0);
			delay(5000);
            break;
        }
	}
}

void dropping_2() {
    //timing in ms
	rlink.command (MOTOR_1_GO, 68+speed_factor); 
	rlink.command (MOTOR_2_GO, 128+72+speed_factor);
	delay(1100);
    rlink.command (MOTOR_1_GO, 0);
    rlink.command (MOTOR_2_GO, 0);
    delay (5000);
}

void recovery() {
    delay(150);
	int val = rlink.request (READ_PORT_5);
	int line_sensors = val & 15; //extract 4 most LSB values 

    if (line_sensors == 6 || line_sensors == 2 || line_sensors == 4){}
	else {
    rlink.command (BOTH_MOTORS_GO_SAME, ((i+1)%2)*(80)+(i%2)*(208));
	
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
            cout<<"BREAKING WITH:"<<line_sensors<<endl;
            break;
        }
		  
        switch (line_sensors) {
            case 6 : //0110
                //cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+68+speed_factor);
                rlink.command (MOTOR_2_GO, 72+speed_factor);
                i=1;
                break;
            case 2 : //0010
                //cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 128+68+10+speed_factor);
                rlink.command (MOTOR_2_GO, 72-10+speed_factor);
                break;
            case 4 : //0100
                //cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 128+68-10+speed_factor);
                rlink.command (MOTOR_2_GO, 72+10+speed_factor);
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
        timed_forward_motion(1000);
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
        timed_forward_motion(100);
        rlink.command (BOTH_MOTORS_GO_SAME, 0);
    }
    if (junction_array[junction_counter]==5) {
        dropping_1();
    }
    if (junction_array[junction_counter]==6) {
        dropping_2();
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
