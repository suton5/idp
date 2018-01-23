
#include <stdio.h>

//the distance between 2 sensor arms is fixed physically, i.e. a constant
//variable i indicates i-th brassica sensed
//when i-th is sensed, store in array, then pick i-th brassica
//that means the fixed distance between arms < distance between subsequent brassica
//distance sensor to sense height
//infrared for the color

int i = 0;
int distance_sensor;
#include "line_follower.cpp"

void pick_brassicas()
    {
        //go straight until there is obstable
        while (distance_sensor==0){
            straight_motion_along line();
        }
        
        if (distance_sensor == 1)
            {
                mA_power = 0;
                mB_power = 0;
                
                    while(IR_sensor == 0)
                        {
                            forward_function == 1; //create an untimed function
                            
                        }
                
                    if (IR_sensor == 1)
                        {
                            timed_forward_motion(100); //set to match distance between sensor arm and picking arm
                            mA_power = 0;
                            mB_power = 0;
                            

                        }
            }
        
        
        
        
