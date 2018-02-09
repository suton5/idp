# Automatically generated Makefile
motion :  motion.o initialise.o
	 g++ -L/export/teach/1BRobot -o motion  motion.o  initialise.o  -lrobot

motion.o: motion.cpp initialise.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c motion.cpp
initialise.o: initialise.cpp
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c initialise.cpp
