////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        send_signal.c
// Other Files:      my_c_signal_handler.c, my_div0_handler.c
// Semester:         CS 354 Summer 2024
// Instructor:       Shayne Wadle
// 
// Author:           Khaled Saleh
// Email:            khsaleh@wisc.edu
// CS Login:         ksaleh
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//
// Online sources:   None
////////////////////////////////////////////////////////////////////////////////
// Copyright 2013,2019-2024
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for Spring 2024
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

/* Main function to send a signal to a specified process.
 *
 * Pre-conditions: the function is executed with exactly two command-line arguments.
 * argc: the number of command-line arguments.
 * argv: an array containing the command-line arguments; argv[1] specifies the
 *       signal type (-i for SIGINT, -u for SIGUSR1), and argv[2] specifies the PID.
 *
 * Post-conditions: sends the specified signal to the process with the given PID.
 *                  prints an error message if the input is invalid or the signal 
 *                  could not be sent.
 */
int main (int argc, char* argv[]) {
    // input must have two arguments
    if (argc != 3) {
        printf("Usage: <signal type> <pid>\n");
        exit(0);
    }
    // get pid from input
    pid_t pid = atoi(argv[2]);

    // if user specifies SIGINT
    if (strcmp(argv[1], "-i") == 0) {
        if (kill(pid, SIGINT) == -1) {
			perror("Error");
			exit(0);
		}
    // if user specifies SIGUSR1
    } else if (strcmp(argv[1], "-u") == 0) {
        if (kill(pid, SIGUSR1) == -1) {
            perror("Error");
            exit(0);
        }
    }
    else {
        perror("Invalid");
		exit(0);
    }
    return 0;
}
