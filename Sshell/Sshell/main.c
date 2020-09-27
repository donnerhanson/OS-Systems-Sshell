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
 2) copy substring: https://stackoverflow.com/questions/6205195/given-a-starting-and-ending-indices-how-can-i-copy-part-of-a-string-in-c/6205241
 3)
 
 */

#include <errno.h>  // defines error codes for exit
#include <fcntl.h>  // defines open/close, read/write flags
#include <stdio.h>  // defines BUFSIZ, printf
#include <stdlib.h> // defines EXIT_FAILURE
#include <string.h>
#include <unistd.h> // defines access, read, write


#define MAX_ARGS 9

int main(int argc, const char * argv[]) {
    
    //int should_run = 1;
    char should_run[6] = "exit\n";
    char input[BUFSIZ] = {'\0'};
    char command[BUFSIZ] = {'\0'};
    char *params[BUFSIZ] = {'\0'};
    int args_len = 0;
    int n_args = 0;
    while ((strcmp(should_run,input)) != 0) {
        printf("osh-> ");
        // clear arr contents
        memset(input, 0, sizeof input);
        // read in contents to char*
        fgets(input,BUFSIZ,stdin);
        printf("\n");
        
        // create a char* with max_args allowed
        char args[MAX_ARGS][BUFSIZ] = {'\0'};
        
        // get the length of the string without the null terminator
        //int space_flag = 0;
        for (int i = 0; (i < strlen(input)) && (i < BUFSIZ); i++, args_len++) {
            //printf("%d : %c\n", i, input[i]);
            if (input[i] == ' ' || input[i] == '\n') {
                if (n_args < MAX_ARGS) {
                    int substring_start = i - args_len;
                    //printf("arg len: %d \t arg_first index: %d\n", args_len,substring_start);
                    // copy substring to char* arr
                    
                    strncpy (args[n_args], input+substring_start, i - substring_start );
                    //printf("Arg num: %d\n", n_args+1);
                    // do not include space in substring start
                    args_len = -1;
                    ++n_args;
                    
                }
                else{
                    printf("too many arguments\n");
                    n_args = 0;
                    break;
                }
                
            }
        }
        int ch_num = 0;
        // FORMAT OUTPUT Arrays
        // execvp(cmd, {"cmd", "-argoption", "argoption", "arg option"})
        if(strcmp(args[0], "exit") != 0) {
            
            for (int i = 0; i < MAX_ARGS - 1; i++, ch_num++) {
                if (i == 0) {
                    //printf("%s ", args[i]);
                    memcpy(command, args[i], sizeof(args[i]));
                    params[ch_num] = args[i];
                }
                else {
                    if (strcmp(args[i],"\0") != 0) {
                        
                        params[ch_num] = args[i];
                    }
                    else{
                        params[ch_num] = NULL;
                    }
                }
                
                
            }
        }
        n_args = 0;
        args_len = 0;
        
        // when the user enters exit at the prompt, your program will set should_run to 0 and terminate.
        
        // This will require parsing what the user has entered into separate tokens and storing the tokens in an array of character strings. For example, if the user enters the command ps -ael at the osh > prompt, the values stored in the args array are:
        // command = "ps"
        //params[0] = "ps"
        //params[1] = "-ael"
        //params[2] = NULL
        
        if (( strcmp(command, "exit")) !=0 ) {
            int status;
            pid_t pid;
            
            pid = fork ();
            if (pid == 0) {
                /* This is the child process.  Execute the shell command. */
                execvp(command, params);
                //execl (SHELL, SHELL, "-c", command, NULL);
                _exit (EXIT_FAILURE);
            }
            else if (pid < 0) {
                /* The fork failed.  Report failure.  */
                status = -1;
            }
            else {
                /* This is the parent process.  Wait for the child to complete.  */
                if (waitpid (pid, &status, 0) != pid)
                {
                    status = -1;
                    
                }
                
            }
        }

    }
    
    return 0;
    
    
    //printf("%d, %s, %s\n", argc, argv[1], argv [2]);
    
}
