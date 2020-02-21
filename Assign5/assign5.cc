#include <iostream>  // You will always need this
using namespace std; // You need this, unless its "241 c++"

#include <unistd.h> //fork()

#include <sys/types.h> //wait()
#include <sys/wait.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>

/***********************************************************************
 * CSCI 330, Assignment 5, Fall Semester
 * Abel Vega Arteaga
 * z1883490
 * Section 1
 * November 5, 2019
 *
 * Purpose: The purpose of this assignment is to make sure that the
 * students can work effectively with the fork, pipe, and
 * dup, system calls. It should also grant some insight into how the
 * shell enables input and output redirection behind the scenes
***********************************************************************/

int main()
{
	char quit[] = "quit"; // array to use for the while loop, so i can quit

	char command1[255]; //these are for the commands that will be
	char command2[255];  //passed on the command line

	char *Opt1[10]; //these two char will take the options
	char *Opt2[10];

	int status; //used for waitpid.
	int i = 0; // used for the strtok loop


///This part of code will take the user's input for both commands and
/// either quit or actual commands
	//this three lines will take the user's command and options
	cout << "Please enter a command1: [command] [option]" << endl;
	cin.getline(command1, 255); ///
	cout << "You had entered: " << command1 << endl;
	
	//This is the loop, it will keep repeating unless command1 is "quit" which will return 0
	while(strcmp(command1, quit) != 0) 
	{	
		cout << "Please enter a command2: [command] [option]" << endl;
		cin.getline(command2, 255);                      // gets the user input for the second command
		
		cout << "You had entered: " << command2 << endl; //I have added this block
		if(strcmp(command2, quit) == 0)                  // in case the user wants
		{												 // to quit on the second
			cout << " You had entered 'quit'" << endl;   // command
			break;                                       //this will break the command
		}
///This part of the code will take each part of the command and break it into pecies and place in the right variables

		i = 0;
        Opt1[i++] = strtok(command1, " "); // this will return the first part of command1
//// loop throught the string token to get all of the first commands
        while ((Opt1[i] = strtok(NULL, " ")) != 0)
        {i++;}
        
        i = 0;
        Opt2[i++] = strtok(command2, " "); // this will return the first part of command2
//// loops throught the string token to get all of the second commands
        while ((Opt2[i] = strtok(NULL, " ")) != 0) 
        {i++;}
		
///This part of the code will do the fun Fork/Dup/Close/Exec stuff

		int pipefd[2]; // 0 for read side, 1 write side, 2 error.
		
		
		
		if(pipe(pipefd) == -1) //error check for the pipe 
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		
		int pid1 = fork(); // this will create the two proccess
		
		if (pid1 < 0) // check for error for first child.
		{
			perror("1st Fork error");
			exit(EXIT_FAILURE);
		}
		
		if(pid1 == 0) // child 1
		{
			close(pipefd[0]);   // child  close unused read end.
			dup2(pipefd[1], 1); // dup2 will take indicated from stdout and copy it into slot 1
			close(pipefd[1]);   // close write end of pipe
			
			// the execvp will replace the child process with execvp
			// it will then 
			int errorCheck1 = execvp(Opt1[0], Opt1);
			if(errorCheck1 < 0)
			{
				perror("exec() #1 failed!");
				exit(EXIT_FAILURE);
			}
		}
		
		waitpid( -1, &status, 0); //  -1 is for wait for any child process. 
								  //  &status wait is for... ok, i am not sure what this was use for but man-page said I need it.
								  //  0 is for wait any child id that is 0.
								  
		int pid2 = fork(); // this will create new fork ONLY FOR THE PARENT.
		
		if(pid2 == 0) //child 2
		{
			close(pipefd[1]); //close write end of pipe
			dup2(pipefd[0],0);// // dup2 will take indicated from stdin and copy it into slot 0 
			close(pipefd[0]); //close read end of pipe
			
			// this will replace the current child process with the execvp
			//but if it doesnt work, then it will go into the if statment
			//and tell the user it didnt work. 
			int errorCheck2 = execvp(Opt2[0], Opt2); 
			if(errorCheck2 < 0)
			{
				perror("exec() #2 failed!");
				exit(EXIT_FAILURE);
			}
		}	
		// This is after all of the piping stuff and only the parent is left.
		close(pipefd[0]); //close read  end of pipe of parent
		close(pipefd[1]); //close write end of pipe of parent
		waitpid( -1, &status, 0); //  -1 is for wait for any child process. 
								  //  &status wait is for... ok, i am not sure what this was use for.
								  //  0 is for wait any child id that is 0.

		// after the parent and child proccess are done, 
		// this block will ask the user for more commands or quit.
		
		
		cout << "Please enter a command1: [command] [option]" << endl;
		cin.getline(command1, 255);
		cout << "You had entered: " << command1 << endl;
	}
	return 0; // return 0.
}
