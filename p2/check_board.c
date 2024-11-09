////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:      None
//
// Semester:         CS 354 Summer 2024
// Instructor:       wadle
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
//////////////////////////// 80 columns wide ///////////////////////////////////
// ALL C SOURCE CODE FILES MUST HAVE FILE HEADER COMMENTS

////////////////////////////////////////////////////////////////////////////////
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, Deb Deppeler, SPRING 2024
////////////////////////////////////////////////////////////////////////////////
// Fix compiler error
// Implement remaining functionality


///////////////////////////////////////////////////////////////////////////////
// Copyright 2021-24 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get 
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
// 01/24/2022 Revised to use pointers for CLAs
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* TODO: implement this function
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) {
	// size must be 1-9 to be valid
	if (size > 9 || size < 1) {
		return 0;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int num = *(*(board + i) + j);
			// invalid if num size negative or greater than the size
			if (num < 0 || num > size) {
				return 0;
			}
			// if num is 0 it can be ignored
			if (num == 0) {
				continue;
			}
			// check for numbers in same row
			for (int col = j + 1; col < size; col++) {
				if (*(*(board + i) + col) == num) {
					return 0;
				}
			}
			// check for numbers in same col
			for (int row = i + 1; row < size; row++) {
				if (*(*(board + row) + j) == num) {
					return 0;
				}
			}
		}
	}
	return 1; // if passes through everything board is valid
}    

/* COMPLETED (DO NOT EDIT):       
 * Read the first line of file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {      
	char *line = NULL;
	size_t len = 0;

	// 'man getline' to learn about <stdio.h> getline
	if ( getline(&line, &len, fptr) == -1 ) {
		printf("Error reading the input file.\n");
		free(line);
		exit(1);
	}

	char *size_chars = NULL;
	size_chars = strtok(line, DELIM);
	*size = atoi(size_chars);

	// free memory allocated for line 
	free(line);
	line = NULL;
}


/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 * It prints "invalid" (without quotes) if the input file is not valid.
 *
 * Usage: A single CLA that is the name of a file that contains board data.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if able to correctly output valid or invalid.
 * Exit with a non-zero result if unable to open and read the file given.
 */
int main( int argc, char **argv ) {              

	// Checks if number of command-line arguments is correct.
	// Should have only 2 command-line arguments
	if (argc != 2) {
		printf("Usage: ./check_board <input_filename>\n");
		exit(1);
	}
	// Open the file 
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Can't open file for reading.\n");
		exit(1);
	}

	// will store the board's size, number of rows and columns
	int size;

	// Calls get_board_size to read first line of file as the board size.
	get_board_size(fp, &size);
	// Dynamically allocates a 2D array for given board size.
	// Done by dyamically creating a 1D array of pointers to other 1D arrays of ints
	int **arr = malloc(sizeof(int *) * size);
	// check to make sure malloc worked properly
	if (arr == NULL) {
		printf("malloc returned NULL\n");
		exit(1);
	}
	// Allocates each row a 1D array of pointers to other ints
	for (int i = 0; i < size; i++) {
		*(arr + i) = malloc(sizeof(int) * size);
		// check to make sure malloc worked properly
		if (*(arr + i) == NULL) {
			printf("malloc returned NULL\n");
			exit(1);
		}
	}
	// Read the remaining lines.
	// Tokenize each line and store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < size; i++) {

		// read the line
		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading line %i of the file.\n", i+2);
			exit(1);
		}

		token = strtok(line, DELIM);
		for (int j = 0; j < size; j++) {
			// initialize elements of your 2D array.
			*(*(arr + i) + j)  = atoi(token); 
			token = strtok(NULL, DELIM);
		}
	}

	// Calls valid_board and print the appropriate
	// output depending on the function's return value.
	int valid = valid_board(arr, size); // 1 if board is valid, 0 otherwise
	if (valid == 1) {
		printf("valid\n");
	} else {
		printf("invalid\n");
	}	
	// Frees the  memory of inner pointers of arr
	for (int i = 0; i < size; i++) {
		free(*(arr + i));
	}
	free(arr); // free initially allocated array

   	// Closes the file, checks if worked properly
   	if (fclose(fp) != 0) {
        	printf("Error while closing the file.\n");
       		exit(1);
    	}  

	return 0;       
}     	  

