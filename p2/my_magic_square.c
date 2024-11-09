////////////////////////////////////////////////////////////////////////////////
// Main File:        my_magic_square.c
// This File:        my_magic_square.c
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
////////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2024, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
	int size;           // dimension of the square
	int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* 
 * Promps the user for the magic square's size, read it,
 * check if it's an odd number >= 3 (if not, display the required
 * error message and exit)
 *
 * return the valid number
 */
int getSize() {
	int size;
    printf("Enter magic square's size (odd integer >= 3)\n");
    scanf("%d", &size);

    // size must be greater than or equal to 3
    if (size < 3) {
        printf("Magic square size must be >= 3.\n");
        exit(1);
    }

    // size must be an odd number
    if (size % 2 == 0) {
        printf("Magic square size must be odd.\n");
        exit(1);
    }
    
    return size;   
} 

/*
 * Makes a magic square of size n,
 * and stores it in a MagicSquare (on the heap)
 *
 * It may use the Siamese magic square algorithm 
 * or alternate from assignment 
 * or another valid algorithm that produces a magic square.
 *
 * n - the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n) {
    MagicSquare *square = (MagicSquare *)malloc(sizeof(MagicSquare));

    // exit in case malloc fails
    if (square == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    square->size = n;
    square->magic_square = (int **)malloc(n * sizeof(int));

    // exit and free space in case malloc fails
    if (square->magic_square == NULL) {
        printf("Memory allocation failed.\n");
        free(square);
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        (*(square->magic_square + i)) = (int *)malloc(n * sizeof(int));

        // in case malloc fails, free up space in entire row and exit
        if (*(square->magic_square + i) == NULL) {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(*(square->magic_square + j));
            }
            free(square->magic_square);
            free(square);
            exit(1);
        }
    }
    int num = 1; // implement numbers in order 1...n^2
    int row = 0; // top most row
    int col = n / 2; // start at middle column
    int next_row; // used to find the next row
    int next_col; // used to find the next column

    // while loop to fill up magic square
    while (num <= n * n) {

        // constantly move up one and to the right placing
        // numbers 1...n^2
        *(*(square->magic_square + row) + col) = num;
        num++;

        // if at top row, wrap back around to last row
        if (row == 0) {
            next_row = n - 1;
        }
        else {
            next_row = row - 1;
        }

        // if at last column, wrap back around to first column
        if (col == n - 1) {
            next_col = 0;
        }
        else {
            next_col = col + 1;
        }

        // if next position is alredy occupied, go one row down
        if (*(*(square->magic_square + next_row) + next_col)) {
            row = (row + 1) % n; // wraps back to top row if necessary
        }
        else {
            row = next_row;
            col = next_col;
        }
    }
	return square;    
} 

/*  
 * Opens a new file (or overwrites the existing file)
 * and writes the magic square values to the file
 * in the specified format.
 *
 * magic_square - the magic square to write to a file
 * filename - the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    FILE *file = fopen(filename, "w");

    // in case there was an error opening the file
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    
    fprintf(file, "%d\n", magic_square->size);

    // writes magic square into the file
    for (int i = 0; i < magic_square->size; i++) {
        for (int j = 0; j < magic_square->size; j++) {
            fprintf(file, "%d", *(*(magic_square->magic_square + i) + j));
            if (j < magic_square->size - 1) {
                fprintf(file, ","); // places commas between each number
            }
        }
        fprintf(file, "\n"); // puts new line after every row
    }

    fclose(file); // close file
}


/*
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 * 
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
   // Should have 2 arguments
   if (argc != 2) {
       	printf("Usage: ./my_magic_square <output_filename>\n");
        exit(1);
    }
   char *filename = *(argv + 1); // gets filename
   int size = getSize(); // gets size from user
   MagicSquare *magic_square = generateMagicSquare(size); // generates magic square
   fileOutputMagicSquare(magic_square, filename); // writes it into given file
	

    // Free allocated memory
    for (int i = 0; i < size; i++) {
        free(*(magic_square->magic_square + i));
    }
    free(magic_square->magic_square);
    free(magic_square);

    return 0;
} 

// Summer 2024
