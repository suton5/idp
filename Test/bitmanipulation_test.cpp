#include <iostream>
using namespace std;

int main(){
	for (int i; i<1000; i++){
    int val;             // a value
	cin >> val;
		int line_sensors = val bitand 15; //extract 4 most LSB values
		int line_sensors_A = line_sensors bitand 1;
		int line_sensors_B = (line_sensors bitand 2) >> 1;
		int line_sensors_C = (line_sensors bitand 4) >> 2;
		int line_sensors_D = (line_sensors bitand 8) >> 3;
    
    // ... code to setup the link etc not shown
    
    //param = bit0 bitor bit5; // ’0010 0001’ set to 21 hex (33 dec)
    cout << "Total: "<<line_sensors <<endl;
        cout << "A: "<<line_sensors_A <<endl;
    cout << "B: "<<line_sensors_B <<endl;
    cout << "C: "<<line_sensors_C <<endl;
    cout << "D: "<<line_sensors_D <<endl;
        cout << "0110?: "<<(line_sensors_B bitand line_sensors_C) <<endl;
         cout << "0010?: "<<(!line_sensors_B bitand line_sensors_C) <<endl;
          cout << "0100?: "<<(line_sensors_B bitand !line_sensors_C) <<endl;
           cout << "0000?: "<<(!line_sensors_B bitand !line_sensors_C) <<endl;

}
    return 0;

}
