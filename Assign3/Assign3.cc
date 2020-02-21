#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>


struct stat sb;
using namespace std;

using std::endl;
using std::cout;
const int Count = 1024; // the numbr of bytes that the program would be read
string CheckDash = "-"; ///// For question f. to check if the file is a single dash.
char buffer[Count]; // size of the array of buffer
ssize_t howmany = 0; // how many bytes that have been read


int main(int argc, char *argv[]) // argc counts how many were passed with the program						    // argv[] is the vector of argument
{
	for(int i = 1; i < argc; i++)
	{   //starts at one since ./a.out starts at 0 and we dont want to include that, so we start at one which will be the file(s).	{ 		    						// argc will be the max of how many agruments had passed
		////////////////////////////////////
		int fd = open(argv[i], O_RDONLY);
		cout << fd << endl;
		if(argv[i] == CheckDash)
		{
			fd = 1;
			cout << "This file is a dash" << endl;  // I am not sure how to do the f question.
		}
		///Error                        	      // open file(s) and prints an error if unable to do so
		if(fd == -1)            	             // if fails to open, prints error
		{
			perror(argv[i]);		   // Prints an error if
			continue;	                  // continue since we want to know if the other files are also having this error
		}
		if(fd != -1)	                        // if he file is not -1, the this would say what file was open
		{
			cout << "Usage of file : " << argv[i] << endl;
		}
		while ((howmany = read(fd, buffer, Count)) != 0)          //reads the file discriptor, buffer, and count(1024)
		{
			/*
			if (howmany == -1)                                             //checks if homany returns -1. if there is more data at the end of 1024, then it will keep looping until it hits 0
				{
					cerr << " return -1 : " << (argv[i]) << endl;
					perror(argv[i]);
					exit(1);
				}
			*/
			write(i, buffer, howmany); // prints out the argv[i]
		}
		int close(int fd); // closes the file, as it is good practice
	}
return 0;          // returns 0
}
