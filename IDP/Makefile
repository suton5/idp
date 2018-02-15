# Automatically generated Makefile
a.out :  pick_brassicas.o motion.o initialise.o dropping.o
	 g++ -L/export/teach/1BRobot -o a.out  pick_brassicas.o  motion.o  initialise.o  dropping.o  -lrobot

pick_brassicas.o: pick_brassicas.cpp initialise.h motion.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c pick_brassicas.cpp
motion.o: motion.cpp initialise.h motion.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c motion.cpp
initialise.o: initialise.cpp initialise.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c initialise.cpp
dropping.o: dropping.cpp initialise.h motion.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c dropping.cpp
