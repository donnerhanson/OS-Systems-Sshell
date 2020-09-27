/*
Version: 0.1
Name: Donner Hanson
Date: September 27, 2020
File: sshell.c

Process:
Enter loop
Get User input
Parse and place data into argument arrays
pass to execution function
   if contains ampersand : perform process in child process
   else
       return control to parent process


References:
1) man pages
2) copy substring: https://stackoverflow.com/questions/6205195/given-a-starting-and-ending-indices-how-can-i-copy-part-of-a-string-in-c/6205241
3)

*/

/*
 Objective
 Simple Shell Program Implementation
 The simple shell program (sshell.c) is a simple text-based program that takes
 user input from the parent then sends that input to the child process for
 execution.  The separate child process is created using the fork() system call,
 and the user’s command is executed using one of the system calls in the
 exec()family. A C/C++ program that provides the general operations of a
 command-line shell is supplied below. The main() function presents the prompt
 osh-> and outlines the steps to be taken after input from the user has been
 read.
 The main() function continually loops as long as input does not equal "exit\n".

When user inputs a command string a child process is forked and executes the
 command specified by the user. This is obtained by parsing what the user has entered into separate tokens and storing the tokens in an array of character strings.
 For example, if the user enters the command ps -ael at the prompt, the values
 stored in the args array are:
 args[0] = "ps"
 args[1] = "-ael"
 args[2] = NULL
 
 This args array will be passed to the execvp() function, which has the following prototype:
 
 execvp(char *command, char *params[]);
 Command represents the command to be performed and params stores the parameters to this command. For this project, the execvp() function is invoked as execvp(command, params).
 
 The program checks whether the user included an & to determine whether
 or not the parent process is to wait for the child to exit.
 
 Error Handling
 Perform the necessary error checking to ensure that a valid shell command was entered. - TODO

 
 */


#include <errno.h>  // defines error codes for exit
#include <fcntl.h>  // defines open/close, read/write flags
#include <stdio.h>  // defines BUFSIZ, printf
#include <stdlib.h> // defines EXIT_FAILURE
#include <string.h> // defines strlen, strcomp, strncpy
#include <unistd.h> // defines access, read, write


#define MAX_ARGS 80 // dont necessarily need this now - check

int contains_ampersand(char * arr, size_t arr_sz) {
    // printf("%zu\n", arr_sz);
    if (arr_sz > 1) {
        if (arr[arr_sz-1] == '&'){
            return 1;
        }
    }
    else if((arr_sz == 1) && ((strcmp(arr, "&")) == 0)) {
        return 1;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    printf("********** Welcome to the OSH **********\n");

    char exit_str[6] = "exit\n";
    char input[MAX_ARGS/2 + 1] = {'\0'};
    char command[BUFSIZ] = {'\0'};
    char *params[BUFSIZ];
    int args_len = 0;
    int n_args = 0;
    int status;
    pid_t pid;
    
    // if input == exit terminate loop
    while ((strcmp(exit_str,input)) != 0) {
        printf("osh> ");
        fflush(stdout);
        // clear arr contents
        memset(input, 0, sizeof input);
        // read in contents to char*
        fgets(input, BUFSIZ, stdin);
        if (strcmp(input, exit_str) == 0)
            break;
        // create a char* with max_args allowed
        char args[MAX_ARGS][BUFSIZ] = {'\0'};
        
        // get the length of the string without the null terminator
        for (int i = 0; (i < strlen(input)) && (i < BUFSIZ); i++, args_len++) {
            //printf("%d : %c\n", i, input[i]);
            if (input[i] == ' ' || input[i] == '\n') {
                if (n_args < MAX_ARGS) {
                    // starting index of next argument
                    int substring_start = i - args_len;
                    //printf("arg len: %d \t arg_first index: %d\n", args_len,substring_start);
                    // copy substring to char* arr
                    strncpy (args[n_args], input+substring_start,
                             i - substring_start );
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
        /* execvp(cmd, {"cmd", "-arg_flags or options",
         "arg_option", "arg_option", ...}) */
        if(strcmp(args[0], "exit") != 0) {
            
            for (int i = 0; i < MAX_ARGS - 1; i++, ch_num++) {
                if (i == 0) {
                    memcpy(command, args[i], sizeof(args[i]));
                    params[ch_num] = args[i];
                }
                else {
                    if (strcmp(args[i],"\0") != 0) {
                        
                        params[ch_num] = args[i];
                    }
                    else{
                        params[ch_num] = NULL;
                        break; // no need to copy NULL to end of arr
                    }
                }
            }
        }

        // Parsing what the user has entered into separate tokens
        // command = "ps"
        // params[0] = "ps"
        // params[1] = "-ael"
        // params[2] = NULL
        // make sure that theres a non-null cmd
        int has_Amp = contains_ampersand(command, strlen(command));
        for (int i = 0; i < n_args; i++) {
            has_Amp = contains_ampersand(params[i], strlen(params[i]));
                //printf("%s : Contains ending ampersand? %d\n",command,has_Amp);
        }
        
        if ((strcmp(command, "")) != 0 ) {
            pid = fork ();
            if (pid == 0) {
                /* This is the child process.  Execute the shell command. */
                execvp(command, params);
                _exit (EXIT_FAILURE);
            }
            else if (pid < 0) {
                /* The fork failed.  Report failure.  */
                status = -1;
            }
            else {
                // This is the parent process.  Wait for the child to complete.
                if (waitpid (pid, &status, 0) != pid) {
                    status = -1;
                    
                }
                if (has_Amp == 1) {
                    // run command as background process
                    int stat_val;
                    pid_t child_pid;

                    child_pid = wait(&stat_val);
                }
            }
        }
        n_args = 0;
        args_len = 0;
    }
    printf("********** GOODBYE **********\n");
    return 0;
}
