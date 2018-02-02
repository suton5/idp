#include "initialise.h"

int junction_counter = 0;
int junction_array[8]  = {1,0,1,1,0,0,0,4};//{0,1,4};
int array_size = sizeof(junction_array)/sizeof(junction_array[0]);


void timed_forward_motion(int timing) {
    //timing in ms
    rlink.command (MOTOR_1_GO, 128+98);
    rlink.command (MOTOR_2_GO, 102);
    delay (timing);
}

void turn_90_left() {
    rlink.command (MOTOR_1_GO, 128+98);
    rlink.command (MOTOR_2_GO, 102);
    delay(600);
    rlink.command (MOTOR_1_GO, 92); 
    rlink.command (MOTOR_2_GO, 92); 
    delay(500);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void turn_90_right() {
    rlink.command (MOTOR_1_GO, 128+98);
    rlink.command (MOTOR_2_GO, 102);
    delay(600);
    rlink.command (MOTOR_1_GO, 220); 
    rlink.command (MOTOR_2_GO, 220); 
    delay(500);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}

void turn_135_left() {
    rlink.command (MOTOR_1_GO, 128+98);
    rlink.command (MOTOR_2_GO, 102);
    delay(750);
    rlink.command (MOTOR_1_GO, 92); 
    rlink.command (MOTOR_2_GO, 92); 
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
    rlink.command (MOTOR_1_GO, 128+98);
    rlink.command (MOTOR_2_GO, 102);
    delay(750);
    rlink.command (MOTOR_1_GO, 220); 
    rlink.command (MOTOR_2_GO, 220); 
    delay(1000);
    while (true) {
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values 

        if (line_sensors == 6){
            break;
        }
	}
}	

int j = 1;
void recovery() {
	//static int i=1;
	/*
	if (i>50) {
		rlink.command (MOTOR_1_GO, 20);
        rlink.command (MOTOR_2_GO, 128+20);
    }
    */

		        while(true){
            stopwatch watch;
            watch.start();
            
            rlink.command (BOTH_MOTORS_GO_SAME, ((j+1)%2)*(100)+(j%2)*(228));


            int val = rlink.request (READ_PORT_5);
            int line_sensors = val & 15; //extract 4 most LSB values
            
            if ((line_sensors =! 0) || (watch.read() == 10*j)){
				j++;
                break;
            }
        }}
        
       /*
		rlink.command (BOTH_MOTORS_GO_SAME, ((i+1)%2)*(100)+(i%2)*(228));
		delay(10*i);
		rlink.command (BOTH_MOTORS_GO_SAME, 0);	
		delay(10);
		i++;
		*/
	


void line_follower() {
	    while (true) {
		
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val & 15; //extract 4 most LSB values

        if ((line_sensors bitand 9) == 9){
            cout<<"BREAKING WITH:"<<line_sensors<<endl;
            break;
        }
		
        switch (line_sensors) {
            case 6 : //0110
                cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 128+98);
                rlink.command (MOTOR_2_GO, 102);
                break;
            case 1 : //0001
                cout<<"0001 Hard right"<<endl;
                rlink.command (MOTOR_1_GO, 128+98+29);
                rlink.command (MOTOR_2_GO, 128+50);
                break;
            case 2 : //0010
                cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 128+98+10);
                rlink.command (MOTOR_2_GO, 102-10);
                break;
            case 4 : //0100
                cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 128+98-10);
                rlink.command (MOTOR_2_GO, 102+10);
                break;
            case 8 : //1000
                cout<<"1000 Hard left"<<endl;
                rlink.command (MOTOR_1_GO, 50);
                rlink.command (MOTOR_2_GO, 102+25);
                break;
                
            case 0 : //0000
                cout<<"0000 DANGER: Off path"<<endl;
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
    
    for (int i=0; i<array_size; i++) {
    line_follower();
    junction_tester();
    }
    
		return 0;
}
