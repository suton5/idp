

//add a sensor to detect the black perimeter
/*
if (obstacle_sensor == 1)
    {
        stop_function == 1;
        
        for (int t = 0; t < 300; t = t + 10) //depends on the speed of the robot
            {
                reverse_function == 1;//create a reverse function beforehand and call this functio
            }
        
        forward_function == 1; //call the forward motion function again and resume
    }
*/
//ultimate correction in case the line following statements all fail due to high speed down
//the slope and the robot cannot react fast enough
if (line_sensor == 0000) //0000 being all 4 sensors return 0 indicating it is stranded
    {
        stop_function == 1;      //create a stop function beforehand and call this function
        
        while(true)
            {
                reverse_function == 1;
                
                //while reversing, if one of/both the left sensors sense white line
                //then turn left
                if (line_sensor == 1000 or line_sensor == 1100 or line_sensor == 0100)
                    {
                        turn_left_function == 1;
                        
                        if (line_sensor == 0110)
                            {
                                forward_function == 1;
                            }
                    }
                
                //while reversing, if one of/both the right sensors sense white line
                //then turn right
                if (line_sensor == 0001 or line_sensor == 0011 or line_sensor == 0010)
                    {
                        turn_right_function == 1;
                        
                        if (line_sensor == 0110)
                            {
                                forward_function == 1;
                            }
                    }
                
                //albeit all 6 conditions, i did not account for the possibility that
                //the robot goes offway at the junction, in which case
                //the sensor might return sth like 1001 when reversing
                //which i think can be ignored when it further reverses
                    
                
