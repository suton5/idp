#include "initialise.h"
#include "motion.h"

int ldr_reading_threshold = 145;
int j=0;
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

void pickup_selector(int choice) {
	if (choice == 0) { //cauliflower
		int number1 = rlink.request(READ_PORT_5);
		number1 &= ~(1UL << 5);
		rlink.command (WRITE_PORT_5, number1);
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
        number1 = rlink.request(READ_PORT_5);
		number1 |= 1UL << 5;
		rlink.command (WRITE_PORT_5, number1);
	}
	
	if (choice == 1) { //cabbage
		int number2 = rlink.request(READ_PORT_5);
		number2 &= ~(1UL << 6);
		rlink.command (WRITE_PORT_5, number2);
        rlink.command(WRITE_PORT_0, BinaryToDecimal(10111111));//01100000
        delay(2000);
        rlink.command (MOTOR_4_GO, 255);
        delay(5200);
        rlink.command (MOTOR_4_GO, 0);
        delay(2000);
        rlink.command (MOTOR_4_GO, 100);
        delay(4200);
        rlink.command (MOTOR_4_GO, 0);
        rlink.command(WRITE_PORT_0, BinaryToDecimal(11111111));
        delay(2000);
        number2 = rlink.request(READ_PORT_5);
		number2 |= 1UL << 6;
		rlink.command (WRITE_PORT_5, number2);
        
    }
}

void brassica_detector() {
	
	line_follower_straight(3000);
	
	while (true) {
        
        //Initialiase all bits at 1
        rlink.command (WRITE_PORT_0, BinaryToDecimal(11111111));
        //int ldr_reading=rlink.request (ADC4);
        //cout<<ldr_reading<<endl;
        
        // Extract distance sensor bit
        // Low if large brassica detected
        int distance_reading = rlink.request (READ_PORT_0);
        int distance_reading1 = distance_reading bitand 128;
        int distance_reading2 = distance_reading1 >> 7;
        //cout<<distance_reading<<endl;
        
        // If large brassice detected
        if (distance_reading2==0){
            
            // Set bit 7 indicator without affecting other bits
            int number = rlink.request(READ_PORT_5);
			number &= ~(1UL << 7);
			rlink.command (WRITE_PORT_5, number);
			
			// Turn LED on
            rlink.command (WRITE_PORT_0, BinaryToDecimal(11110111));
			//cout<<ldr_reading<<endl;
			if (j==0) ;
            if (j==3 ) { //cabbage
                
                // Cover distance between LDR and arm
                line_follower_straight(500);
                rlink.command (BOTH_MOTORS_GO_SAME,0);
                
                pickup_selector(1);
                
                // Turn off bit 7 indicator after pick-up
                int number = rlink.request(READ_PORT_5);
				number |= 1UL << 7;
				rlink.command (WRITE_PORT_5, number);
            }
            
            if (j==1 or j==2) { //cauliflower
                line_follower_straight(500);
                rlink.command (BOTH_MOTORS_GO_SAME,0);
                
                pickup_selector(0);
                
                // Turn off bit 7 indicator after pick-up
                int number = rlink.request(READ_PORT_5);
				number |= 1UL << 7;
				rlink.command (WRITE_PORT_5, number);
            }
            j++;
        }
        
        // Integrated line-following
        int val = rlink.request (READ_PORT_5);
        int line_sensors = val bitand 15; //extract 4 most LSB values
        int line_sensors_A = line_sensors bitand 1;
        int line_sensors_B = (line_sensors bitand 2) >> 1;
        int line_sensors_C = (line_sensors bitand 4) >> 2;
        int line_sensors_D = (line_sensors bitand 8) >> 3;
        
        // If any junctions detected, go back to motion
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
}
