#include "initialise.h"

int i = 1;


void timed_forward_motion(int timing) {
    //timing in ms
    rlink.command (MOTOR_1_GO, 128+68);
    rlink.command (MOTOR_2_GO, 72);
    delay (timing);
}


void recovery() {
    cout<<i<<endl;
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
	i++;
	}
}

void line_follower_reverse() {
	    while (true) {
		
		int val = rlink.request (READ_PORT_5);
		int line_sensors = val bitand 15; //extract 4 most LSB values
		  
        switch (line_sensors) {
            case 6 : //0110
                //cout<<"0110 Stay straight"<<endl;
                rlink.command (MOTOR_1_GO, 68);
                rlink.command (MOTOR_2_GO, 128+72);
                i=1;
                break;
            case 2 : //0010
                //cout<<"0010 Slight right"<<endl;
                rlink.command (MOTOR_1_GO, 68+10);
                rlink.command (MOTOR_2_GO, 128+72-10);
                break;
            case 4 : //0100
                //cout<<"0100 Slight left"<<endl;
                rlink.command (MOTOR_1_GO, 68-10);
                rlink.command (MOTOR_2_GO, 128+72+10);
                break;
            case 0 : //0000
                //cout<<"0000 DANGER: Off path"<<endl;
				recovery();
                break; 

        }
        
    }
}

int main() {
    
    initialise_robot();
    line_follower_reverse();

	return 0;
}
