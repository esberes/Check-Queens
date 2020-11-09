////////////////////////////////////////////////////////////////////////////////
// Main File:       check_queens.c
// This File:        check_queens.c
// Other Files:    (name of all other files if any)
// Semester:       CS 354 SPRING 2019
//           
// Author:           Ellie Beres
// Email:             esberes@wisc.edu
// CS Login:        beres
//           
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//           
// Persons:    Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//           
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>   

char *COMMA = ",";

/* Retrieves from the first line of the input file,
 * the number of rows and columns for the board.
 * 
 * fp: file pointer for input file
 * rows: pointer to number of rows
 * cols: pointer to number of columns
 */
void get_dimensions(FILE *fp, int *rows, int *cols) {
	char *line = NULL;
	size_t len = 0;
	if (getline(&line, &len, fp) == -1) {
		printf("Error in reading the file\n");
		exit(1);
	}

	char *token = NULL;
	token = strtok(line, COMMA);
	*rows = atoi(token);

	token = strtok(NULL, COMMA);
	*cols = atoi(token);
}

/* Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * rows: number of rows
 * cols: number of columns
 */
int check_queens(int **board, int rows, int cols) {

	// temporary row and column positions to move through the board to check for other queens
	int tempCol = 0;
	int tempRow = 0;

	for (int m = 0; m < rows; ++m) {
		for (int n = 0; n < cols; ++n) {

			// enter the flow if the position contains a queen
			if (*(*(board + m) + n) == 1) {

				// check the row for other queens
				tempCol = n + 1;
				while ((tempCol) < cols) {
					// return if there is another queen in the row
					if (*(*(board + m) + (tempCol)) == 1) {
						return 1;
					}
					++tempCol;
				}

				// check the column for other queens
				tempRow = m + 1;
				while ((tempRow) < rows) {
					// return if there is another queen in the column
					if (*(*(board + (tempRow)) + n) == 1) {
						return 1;
					}
					++tempRow;
				}

				// check the bottom right diagonal
				tempRow = m + 1;
				tempCol = n + 1;
				while (tempRow < rows && tempCol < cols) {
					// return if there is another queen in the right diagonal
					if (*(*(board + (tempRow)) + (tempCol)) == 1) {
						return 1;
					}
					++tempRow;
					++tempCol;
				}

				// check the bottom left diagonal
				int tempRow = m + 1;
				int tempCol = n - 1;
				while (tempRow < rows && tempCol >= 0) {
					// return if there is another queen in the left diagonal
					if (*(*(board + tempRow) + tempCol) == 1) {
						return 1;
					}
					tempCol--;
					tempRow++;
				}

			}
		}
	}

	return 0;
}

/* This program prints true if the input file has any pair
 * of queens that can attack each other, and false otherwise
 * 
 * argc: CLA count
 * argv: CLA value 
 */
int main(int argc, char *argv[]) {

	//Check if number of command-line arguments is correct.
	if (argc != 2) {
		printf("Incorrect number of command-line arguments\n");
		exit(1);
	}

	//Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Cannot open file for reading\n");
		exit(1);
	}

	//Declare local variables.
	int rows, cols;

	//Call get_dimensions to retrieve the board dimensions.
	get_dimensions(fp, &rows, &cols);

	//Dynamically allocate a 2D array of dimensions retrieved above.
	int **board;
	board = malloc(sizeof(int*) * rows);
	if (board == NULL) {
		printf("Failed to allocate memory\n");
		exit(1);
	}
	for (int i = 0; i < rows; ++i) {
		*(board + i) = malloc(sizeof(int) * cols);
		if (*(board + i) == NULL) {
			printf("Failed to allocate memory\n");
			exit(1);
		}
	}

	//Read the file line by line.
	//Tokenize each line wrt comma to store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < rows; i++) {

		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading the file\n");
			exit(1);
		}

		token = strtok(line, COMMA);
		for (int j = 0; j < cols; j++) {
			// initialize the 2D array
			*(*(board + i) + j) = atoi(token);
			token = strtok(NULL, COMMA);
		}
	}

	//Call the function check_queens and print the appropriate
	//output depending on the function's return value.
	int returnValue = check_queens(board, rows, cols);

	if (returnValue == 1) {
		printf("%s\n", "true");
	} else {
		printf("%s\n", "false");
	}

	//Free all dynamically allocated memory.
	for (int i = 0; i < rows; ++i) {
		free(*(board + i));
	}
	free(board);
	board = NULL;

	//Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file\n");
		exit(1);
	}

	return 0;
}
