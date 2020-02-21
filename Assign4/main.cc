#include <iostream>
#include <cstdio>       
#include <cstdlib>
#include <string.h>
#include "functions.h"
#include <getopt.h>

using namespace std;

/***********************************************************************
 * CSCI 330, Assignment 4, Fall Semester
 * Abel Vega Arteaga
 * z1883490
 * Section 1 
 * October 14, 2019
 * 
 * Purpose: The purpose of this assignment is to provide practice using 
 * the system calls we discussed for working with files on a UNIX system.
 * You will br writing a basic implementation of the CAT command using C++
***********************************************************************/
#include <iostream>       
#include <cstdio>       
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
using namespace std; 
// Global Varialbes
int buffer_length = 1024;
int  shift_amount = 0;
ssize_t amountRead = 0;

// These Global Variable will change into True if -s and -n was
//  was specifid into the command line.
bool maxSize = false;
int maxBuffer;

// These Global Variables for bool (true/false), meaning if the optarg 
// detects one of the -commands, the it will go into the case statements
// it will turn that particular case into "true"

bool cFlag  = false;
bool brFlag = false;
bool hexFlag  = false;
bool bnFlag = false;

/**
 * Function: dataToChange
 * Purpose:  Choose which functions to run
 * Parameters (3):
 *    1) an integer amount of bytes that have been read so far
 *    2) a c-string containing bytes read
 *    3) a c-string to store hex digits in
 * Returns: Nothing
 */
// void Funtion and returns nothing
void dataToChange(int amountRead, char *buffer, char *hexBuffer, char *bitsBuffer)
{
	if(cFlag == true) // for caesar shift
	{	// sends shift_amount/buffer/amountRead
		caesar_shift(shift_amount, buffer, amountRead); 
	}
	if(brFlag == true) // binary shift 
	{	// sends shift_amount/buffer/amountRead
		bin_shift(shift_amount, buffer, amountRead);
	}
	if(hexFlag == true) // hexedecimal
	{	// sends  buffer/hexBuffer/amountRead
		change_to_hex(buffer, hexBuffer, amountRead);
	}	
	if(bnFlag == true) // change to binary
	{	// sends buffer/bitsBuffer/amountRead
		convert_to_bin(buffer, bitsBuffer, amountRead);
	}
}

/**
 * Main function
 */
int main(int argc, char *argv[])
{
	// get options	
	// -b		binary output
	// -c x 	caesar shift
	// -n x		number of bytes to read from each file
	// -r x		rotation
	// -s x		change size of buffer for calls
	// -x		hex output
	
	//intitalizing opt to equal 0 
	int option = 0;
	int maxLength = -1; // used to change the length of the write function.
	while((option = getopt(argc, argv, "bc:n:r:s:x")) != -1) // end when -1 returned 
	{                                 //^^ used take accpeted variables.
		switch(option)
		{
			case 's': // to change the size of the buffer used for calls
				maxBuffer = atoi(optarg);
				//cout << "buffer_length" << buffer_length << endl; //testing
				//maxBuffer = true;		
				break;
			case 'n': // change the number of bytes read from each file
				maxLength = atoi(optarg);
				break;
			case 'c': //ceaser shift
				cFlag = true;
				shift_amount = atoi(optarg);
				break;
			case 'r': // binary rotation
				brFlag = true;
				shift_amount = atoi(optarg);
				break;
			case 'x': // hexadecimal notation
				hexFlag = true;
				break;
			case 'b': // binary notation
				bnFlag = true;
				break;
			default: 
				break; 
		}
	}
	// end get options
	// Check for mutually exclusive shift operations: binary (-r) and caesar (-c) shifts
	if(cFlag && brFlag) // r and c
	{
		perror("You can not have -c and -r, you're breaking the rules!!!");
		exit(1);
	}
	// Check for mutually exclusive output types: binary (-b) and hexadecimal (-x) notation
	if(bnFlag && hexFlag) //
	{
		perror("You can not have -b and -x, you're breaking the rules!!!");
		exit(1);
	}
	
	// size of the array of buffer
	char buffer[maxBuffer];         // making room for string for option -s
	char hexBuffer[buffer_length * 2]; // string with room for 2 hex digits for each character of the buffer.
	char bitsBuffer[buffer_length * 8]; // string with room for 2 hex digits for each character of the buffer.
/**                        ----------------                          **/
	// for remaining arguments that are not options, treat them as filenames
	int fd;
	for (int index = optind; index < argc; index++) //optind is the index in argv where the options ends and other aguements begin. 
    {
		//cout << "Hello from line 138. This is index=" << index << endl;
		if( strcmp(argv[index], "-") == 0) // comparing the argv and dash to see if the two arguments are the same or not
		{                              
			// Read from standard input
			fd = STDIN_FILENO; // stdin is stream 0
			perror("This is a '-' file");
		}   
		else
		{
			// open from argv[index] 
			fd = open(argv[index], O_RDONLY);
		}
		//cout << "Hello from line 151" << endl;    
		// checking if file could be opened
		if(fd == -1) // if fails to open, prints error
		{
			perror(argv[index]);
			continue; // quit the for-loop iteration early, skipping this file and moving on to the next one
		}
		else // file is OK
		{
			bool shouldKeepReading = true;
			//cout << "Hello from line 161" << endl;
			while (shouldKeepReading && (amountRead = read(fd, buffer, buffer_length)) != 0) // read bytes, buffer_length at a time, until read() finishes
			{
				if (amountRead == -1) //checks if amountRead returns -1. if there is more data at the end of buffer_length, then it will keep looping until it hits 0
				{
					cerr << " could not read file: " << (argv[index]) << endl; 
					perror(argv[index]);
					exit(1);
				}
				if(maxLength > -1 && maxLength < amountRead)// if max length > -1
				{
						amountRead = maxLength;    // change the size of the amount read to what the user enter
						shouldKeepReading = false; //
						buffer[maxLength] = '\0';  //
						
				}
				
				dataToChange(amountRead, buffer, hexBuffer, bitsBuffer); // call the changeToCall function to set new data
				
		//		if(maxBuffer)
		//			{
		//			// change the size of hexBuffer	
		//				hexBuffer[buffer_length];
		//			}
				// make changes to data
				if(hexFlag) // if hexFlag, print hex buffer instead of buffer
				{
					
				write(STDOUT_FILENO, hexBuffer, amountRead * 2); // I doubled the amountRead because hex will spitout twice as long since we will get two characters
					cout << endl; // print a new line so that the prompt isn't at the end of some data
				}
				else if (bnFlag) // if binNotation, print hex buffer instead of buffer
				{
					write(STDOUT_FILENO, bitsBuffer, amountRead * 8);
					cout << endl; // print a new line so that the prompt isn't at the end of some data

				}
				else
				{ 
					write(STDOUT_FILENO, buffer, amountRead);
					cout << endl; // prints out the argv[i] what buffer has. i.e. if it just a text file(s)
				}
				
			} // ends of while-read() loop.
			close(fd); // closes the file
		}
		
	} //endl for loop;
	return 0;
	/*
	 * 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
my name is john.
My name is Mary.
x + y = 12
x = 6
x + y = 8
x = 2
Nuh cheif
Yee
john123
Mary456
Georege999
YES69
2 4 5 8 9 63337
9 8 7 5 5 5 344 22 1
eleven11
five5
seven7
three3
two2
9       8       7       5       5       5       344     22      1
7
25 10 7 3 0 -3 -5 -11 -50
25 10 7 3 1 0 -3 -5 -11 -50
	 * 
	 * 
	 * 
	 */
}
