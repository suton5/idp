# Automatically generated Makefile
main :  pick_brassicas.o motion.o main.o initialise.o drop_brassicas.o
	 g++ -L/export/teach/1BRobot -o main  pick_brassicas.o  motion.o  main.o  initialise.o  drop_brassicas.o  -lrobot

pick_brassicas.o: pick_brassicas.cpp initialise.h motion.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c pick_brassicas.cpp
motion.o: motion.cpp initialise.h motion.h pick_brassicas.h drop_brassicas.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c motion.cpp
main.o: main.cpp initialise.h motion.h pick_brassicas.h drop_brassicas.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c main.cpp
initialise.o: initialise.cpp initialise.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c initialise.cpp
drop_brassicas.o: drop_brassicas.cpp initialise.h motion.h
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c drop_brassicas.cpp
