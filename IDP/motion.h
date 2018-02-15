extern int junction_counter;
extern int i;
extern int junction_array[11];
extern int array_size;
extern int speed_factor;
extern int motor_1_initial;
extern int motor_2_initial;

int convertDecimalToBinary(int n);
void timed_forward_motion(int timing);
void turn_90_left();
void turn_90_right();
void turn_135_left();
void turn_135_right();
void turn_180_right();
void recovery();
void line_follower();
void line_follower_straight(int timing);
void junction_tester();

