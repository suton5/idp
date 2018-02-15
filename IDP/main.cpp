#include "initialise.h"
#include "motion.h"
#include "pick_brassicas.h"
#include "drop_brassicas.h"

int main() {
    
    initialise_robot();
    
    for (int j=0; j<array_size; j++) {
    line_follower();
    junction_tester();
    cout<<j<<endl;
	}
	
	return 0;
}
