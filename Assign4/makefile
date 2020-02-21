#
# PROGRAM:  assignment 4
# AUTHOR:   Abel Vega Arteaga
# Z-ID:     z1883490
# DATE DUE: 10/09/2019
#

# Compiler variables
CCFLAGS = -Wall -std=c++11

dog: main.o functions.o
	g++ $(CCFLAGS) -o dog main.o functions.o

main.o: main.cc functions.h
	g++ $(CCFLAGS) -c main.cc
	
functions.o: functions.cc functions.h
	g++ $(CCFLAGS) -c functions.cc
	

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o dog
