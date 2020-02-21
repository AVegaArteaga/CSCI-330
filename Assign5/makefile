#
# PROGRAM:    assign5
# PROGRAMMER: Abel Vega Arteaga
# LOGON ID:   z1883490
# DATE DUE:   10/06/2019
#

# Complier variables
CCFLAGS = -Wall -Werror -std=c++11
	
# Rule to link object code files to create executable file
assign5: assign5.o
	g++ $(CCFLAGS) -o assign5 assign5.o

# Rule to compile source code file to object code
assign5.o: assign5.cc
	g++ $(CCFLAGS) -c assign5.cc

# Pseudo-target to remove object coe and executable files
clean:
	-rm *.o assign5
