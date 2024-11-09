////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_c_signal_handler.c
// Other Files:      send_signal.c, my_div0_handler.c
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

// global variable for num seconds for alarm
int num_seconds = 5;

// counts times SIGUSR1 is received
int count_SIGUSR1 = 0;

/* Function to handle SIGALRM
 *
 * Pre-conditions: the function is called when the SIGALRM signal is received.
 *                 no parameters required.
 * sig: the signal number that triggered this handler.
 *
 * Post-conditions: the current process ID and time are printed, and the alarm is
 *                  re-armed to go off again after the specified number of seconds.
 */
void handle_alarm(int sig) {
    // get process ID
    pid_t pid = getpid();

    // get time
    time_t now;

    if (time(&now) == -1) {
      perror("Error time");
      exit(0);
    }
    // prints PID and current time
    printf("PID: %d", pid);
    printf(" Current time: %s", ctime(&now));

    // set alarm to go off in 5 seconds
    alarm(num_seconds);
}

/* Function to handle SIGUSR1
 *
 * Pre-conditions: the function is called when the SIGUSR1 signal is received.
 *                 no parameters required.
 * sig: the signal number that triggered this handler.
 *
 * Post-conditions: the count of SIGUSR1 signals received is incremented.
 */
void handle_SIGUSR1(int sig) {
    printf("SIGUSR1 caught!\n");
    count_SIGUSR1++;
}

/* Function to handle SIGINT
 *
 * Pre-conditions: the function is called when the SIGINT signal is received.
 *                 no parameters required.
 * sig: the signal number that triggered this handler.
 *
 * Post-conditions: the total count of SIGUSR1 signals received is printed,
 *                  and the program is terminated.
 */
void handle_SIGINT(int sig) {
    printf("\nSIGINT received.\n");
    printf("SIGUSR1 was received %d times. Exiting now.\n", count_SIGUSR1);
    exit(0);
}

int main() {
    // provide instructions
    printf("PID and time print every 5 seconds.\n");
    printf("Type Ctrl-C to end the program.\n");

    // establish signal handler for alarm
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = handle_alarm;

    if (sigaction(SIGALRM, &act, NULL) != 0) {
      // in case error occurs
      perror("sigaction");
      exit(0);
    }

    // establish signal handler for SIGUSR1
    struct sigaction act2;
    memset(&act2, 0, sizeof(act2));
    act2.sa_handler = handle_SIGUSR1;

    if (sigaction(SIGUSR1, &act2, NULL) != 0) {
      // in case error occurs
      perror("sigaction");
      exit(0);
    }

    // establish signal handler for SIGINT
    struct sigaction act3;
    memset(&act3, 0, sizeof(act3));
    act3.sa_handler = handle_SIGINT;
    if (sigaction(SIGINT, &act3, NULL) < 0) {
      perror("Error handling");
      exit(0);
    }
    // sets alarm to go off 5 seconds later
    alarm(num_seconds);

    // enter infinite loop
    while (1) {
    }
}
