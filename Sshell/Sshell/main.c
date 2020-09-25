/*
 Objective
 The objective of this assignment consists of designing a C/C++ program to serve as a shell interface that accepts user commands and then executes each command in a separate process. This project can be completed on any Linux, UNIX, or Mac OS X system.
 Assignment: Using the Fork System Call
 Write a simple shell interface program that gives the user a prompt, after which the next command is entered. The example below illustrates the prompt osh> and the user’s next command: cat prog.c. (This command displays the file prog.c on the terminal using the UNIX cat command.)

 osh> cat prog.c
 Simple Shell Program Implementation
 The simple shell program (sshell.c) is a simple text-based program that takes user input from the parent then sends that input to the child process for execution.  The separate child process is created using the fork() system call, and the user’s command is executed using one of the system calls in the exec()family. A C/C++ program that provides the general operations of a command-line shell is supplied below. The main() function presents the prompt osh-> and outlines the steps to be taken after input from the user has been read. The main() function continually loops as long as should_run equals 1; when the user enters exit at the prompt, your program will set should_run to 0 and terminate.

 The objective is to modify the main() function in the code provided below so that a child process is forked and executes the command specified by the user. This will require parsing what the user has entered into separate tokens and storing the tokens in an array of character strings. For example, if the user enters the command ps -ael at the osh > prompt, the values stored in the args array are:
 args[0] = "ps"
 args[1] = "-ael"
 args[2] = NULL

 This args array will be passed to the execvp() function, which has the following prototype:

 execvp(char *command, char *params[]);

 Here, command represents the command to be performed and params stores the parameters to this command. For this project, the execvp() function should be invoked as execvp(args[0], args). Be sure to check whether the user included an & to determine whether or not the parent process is to wait for the child to exit.

 Figure 1: Outline of Simple Shell
 Error Handling
 Perform the necessary error checking to ensure that a valid shell command was entered.
 Grading
 The program will be graded on the basic functionality, error handling and how well the implementation description was followed. Be sure to name your program sshell.c (no extra characters, capitals) Note that documentation and style are worth 10% of the assignment's grade!
 Submission
 The program source code should be posted to Canvas as well as a README file with sample output.

*/
/*
 Version: 0.1
 Name: Donner Hanson
 Date: September 18, 2020
 File: filecpy.c
 This program uses system calls to copy a file to a new file
 
 
 Process:

 
 
 References:
 1) man pages
*/

#include <errno.h>  // defines error codes for exit
#include <fcntl.h>  // defines open/close, read/write flags
#include <stdio.h>  // defines BUFSIZ, printf
#include <stdlib.h> // defines EXIT_FAILURE
#include <unistd.h> // defines access, read, write

int main(int argc, const char * argv[]) {

    // check argument count
    if (argc < 3){
        printf("Program requires an input and output file path\n");
        return EINVAL;
    }
    if (argc > 3) {
        printf("Too many arguments...\nProgram requires an input and output file path\n");
        return EINVAL;
    }
    int should_run = 1;
    
    while (should_run) {
        printf("osh-> ");
        
        // when the user enters exit at the prompt, your program will set should_run to 0 and terminate.
        //args[0] = "ps"
        //args[1] = "-ael"
        //args[2] = NULL
        // This will require parsing what the user has entered into separate tokens and storing the tokens in an array of character strings. For example, if the user enters the command ps -ael at the osh > prompt, the values stored in the args array are:
        break;
        
    }
    
    //execvp(argv[1], &argv[2]);
    printf("%d, %s, %s\n", argc, argv[1], argv [2]);
    return 0;
}
