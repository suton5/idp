#include <iostream>
using namespace std;

int main() {
	int number = 255;
	number &= ~(1UL << 6);
	cout<<number<<endl;
}
