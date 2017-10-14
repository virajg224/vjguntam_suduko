/*
 * suduko_solver.c
 *
 *  Created on: June 20, 2017
 *      Author: virajguntamukkala
 */
 
#include <stdio.h>

int is_available(int puzzle[][9], int row, int col, int num) {
    int row_start = (row / 3) * 3;
    int col_start = (col / 3) * 3;
    int i, j;

    for (i = 0; i < 9; ++i) {
        if (puzzle[row][i] == num) {
         	return 0;
         	}
        if (puzzle[i][col] == num) {
        	return 0;
        	}
        if (puzzle[row_start + (i % 3)][col_start + (i / 3)] == num) {
        	return 0;
        	}
    } 
    return 1;
}

int fill_sudoku(int puzzle[][9], int row, int col) {
    int i;
    if (row < 9 && col < 9) {
        if (puzzle[row][col] != 0) {
            if ((col + 1) < 9) {
             	return fill_sudoku(puzzle, row, col+1);
             }
            else if ((row + 1) < 9) {
             	return fill_sudoku(puzzle, row + 1, 0);
             }
            else {
            	return 1;
            	}
        }
        else {
            for (i = 0; i < 9; ++i) {
                if (is_available(puzzle, row, col, i + 1)) {
                    puzzle[row][col] = i + 1;
                    if ((col + 1) < 9) {
                        if(fill_sudoku(puzzle, row, col + 1)) {
                        	 return 1;
                        	}
                        else {
                        	 puzzle[row][col] = 0;
                        	 }
                    }
                    else if ((row + 1) < 9) {
                        if(fill_sudoku(puzzle, row + 1, 0)) return 1;
                        else puzzle[row][col] = 0;
                    }
                    else {
                    	return 1;
                    }
                }
            }
        }
        return 0;
    }
    else {
    	return 1;
    }
}

int main() {
    int i, j;
    int puzzle[9][9];

    if (fill_sudoku(puzzle, 0, 0)) {
        printf("\n");
        for(i = 1; i < 10; ++i) {
            for(j = 1; j < 10; ++j) {
                if (j % 3 == 0 && j != 9) printf(" %d |", puzzle[i - 1][j - 1]);
                else printf(" %d", puzzle[i - 1][j - 1]);
            }
            printf("\n");
            if (i % 3 == 0 && i != 9) printf("-------|-------|-------\n");
        }
    }
    else printf("\nThere is no solution.\n");
    return 0;
}



