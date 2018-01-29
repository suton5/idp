#include <iostream>
using namespace std;

int main(){
    int param;             // a value
    const int bit0 = 1; // ’0000 0001’ individual bits
    const int bit5 = 32; // ’0010 0000’ expressed in hexadecimal
    
    // ... code to setup the link etc not shown
    
    param = bit0 bitor bit5; // ’0010 0001’ set to 21 hex (33 dec)
    cout << param <<endl;
}
