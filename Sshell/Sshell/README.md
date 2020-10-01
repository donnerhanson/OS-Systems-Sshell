#  Sshell  

Version: 0.2  
Name: Donner Hanson  
Date: September 30, 2020  
Project: Simple Shell
Files: sshell.c  
Student ID: 001276484  
email: hanso127@mail.chapman.edu  

*Project Description:*  
This program is a basic representation of a Linux shell program.  
The shell is able to process exec() family function commands.  
This main topic of the project was to introduce and explore threading in C  
Tested using MacOS  

*Process:*  
Enter loop  
Get User input  
Parse and place data into argument arrays - parse  
pass to execution function  
if contains ampersand
*  perform execution process in background child process and have parent wait for exit from process  
else  
*  return control to parent process  

*Sample Input:*  
ls  
ls &  

*Sample Output*  
note that the scheduler on my machine finishes the "ls -lah &" process execution  
after the input prompt is displayed 
********** Welcome to the OSH **********  
osh> ls -lah  
total 88  
drwxr-xr-x  4 Donner  admin   128B Sep 30 18:44 .  
drwxr-xr-x@ 4 Donner  admin   128B Sep 30 18:40 ..  
-rw-r--r--@ 1 Donner  admin   6.0K Sep 30 18:41 .DS_Store  
-rwxr-xr-x  1 Donner  admin    32K Sep 30 18:44 Sshell
osh> ls -lah &  
osh> total 88  
drwxr-xr-x  4 Donner  admin   128B Sep 30 18:44 .  
drwxr-xr-x@ 4 Donner  admin   128B Sep 30 18:40 ..  
-rw-r--r--@ 1 Donner  admin   6.0K Sep 30 18:41 .DS_Store  
-rwxr-xr-x  1 Donner  admin    32K Sep 30 18:44 Sshell  
osh> exit  
********** GOODBYE **********  

