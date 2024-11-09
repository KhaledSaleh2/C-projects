////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_div0_handler.c
// Other Files:      my_c_signal_handler.c, send_signal.c
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

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int successful_operations = 0; // count of successful operations

/* handler for divide by zero (SIGFPE)
 * 
 * pre-conditions: this function is triggered by a SIGFPE signal, which occurs 
 * when a division by zero is attempted.
 * sig: the signal number (should be SIGFPE).
 * post-conditions: prints an error message, the total number of successful 
 * operations, and then terminates the program.
 */
void handle_SIGFPE(int sig) {
    printf("Attempted to divide by zero.\n");
    printf("Total successful operations: %d\n", successful_operations);
    printf("Terminating the program.\n");
    exit(0);
}

/* handler for SIGINT (ctrl+c)
 * 
 * pre-conditions: this function is triggered by a SIGINT signal, which occurs 
 * when the user presses Ctrl+C.
 * sig: the signal number (should be SIGINT).
 * post-conditions: prints the total number of successful operations and then 
 * terminates the program.
 */
void handle_SIGINT(int sig) {
    printf("\nTotal successful operations: %d\n", successful_operations);
    printf("Terminating the program.\n");
    exit(0);
}

/* main function to continuously read input and perform division operations
 * 
 * pre-conditions: no specific conditions; the program reads input from the user.
 * post-conditions: the program will repeatedly ask for two integers, perform 
 * division, and print the result. It will terminate upon a SIGFPE or SIGINT signal.
 */
int main() {
    // setup sigfpe handler
    struct sigaction sa_fpe;
    memset(&sa_fpe, 0, sizeof(sa_fpe));
    sa_fpe.sa_handler = handle_SIGFPE;
    if (sigaction(SIGFPE, &sa_fpe, NULL) < 0) {
        perror("sigaction error");
        exit(0);
    }

    // setup sigint handler
    struct sigaction sa_int;
    memset(&sa_int, 0, sizeof(sa_int));
    sa_int.sa_handler = handle_SIGINT;
    if (sigaction(SIGINT, &sa_int, NULL) < 0) {
        perror("sigaction error");
        exit(0);
    }

    while (1) {
        char input_buffer[100];
        printf("please enter the first integer: ");
        fgets(input_buffer, sizeof(input_buffer), stdin);
        int num1 = atoi(input_buffer);

        printf("please enter the second integer: ");
        fgets(input_buffer, sizeof(input_buffer), stdin);
        int num2 = atoi(input_buffer);

        // perform division and handle possible divide by zero
        int quotient = num1 / num2;
        int remainder = num1 % num2;
        printf("%d / %d = %d, remainder = %d\n", num1, num2, quotient, remainder);
        successful_operations++;
    }

    return 0;
}
