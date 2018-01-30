# Automatically generated Makefile
test :  test.o initialise.o
	 g++ -L/export/teach/1BRobot -o test  test.o  initialise.o  -lrobot

test.o: test.cpp initialise.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c test.cpp
initialise.o: initialise.cc initialise.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c initialise.cc
