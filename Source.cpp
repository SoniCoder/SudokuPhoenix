#include <stdio.h>
#include <stdlib.h>

int validate(int* sudoku, int i, int j) {
	int row;
	int col;
	for (row = i, col = 0; col < 9; ++col) {
		if (col != j) {
			if (sudoku[9 * i + j] == sudoku[9 * row + col]) return 0;
		}
	}
	for (row = 0, col = j; row < 9; ++row) {
		if (row != i) {
			if (sudoku[9 * i + j] == sudoku[9 * row + col]) return 0;
		}
	}
	int mini_square_i = 3 * (i / 3);
	int mini_square_j = 3 * (j / 3);
	int a, b;
	for (a = mini_square_i; a < mini_square_i + 3; ++a) {
		for (b = mini_square_j; b < mini_square_j + 3; ++b) {
			if (!(i==a && j==b) && sudoku[9 * i + j] == sudoku[9 * a + b]) {
				//printf("Number %d denied at %d, %d because %d, %d has it\n", sudoku[9 * i + j], i, j, a, b);
				return 0;
			}

		}
	}
	return 1;
}

int solve(int* sudoku, int i, int j) {
	if (i > 8) return 1;
	if (sudoku[9 * i + j]) {
		int next_i, next_j;
		if (j == 8) {
			next_i = i + 1;
			next_j = 0;
		}
		else {
			next_i = i;
			next_j = j + 1;
		}
		int solved = solve(sudoku, next_i, next_j);
		if (solved) return 1;
		else return 0;
	}
	int trial;
	for (trial = 1; trial < 10; ++trial) {
		sudoku[i * 9 + j] = trial;
		int validated = validate(sudoku, i, j);
		if (validated) {
			//printf("validated %d at %d , %d\n", trial, i, j);
			int next_i, next_j;
			if (j == 8) {
				next_i = i + 1;
				next_j = 0;
			}
			else {
				next_i = i;
				next_j = j + 1;
			}
			int solved = solve(sudoku, next_i, next_j);
			if (solved) return 1;
		}
	}
	sudoku[i * 9 + j] = 0;
	return 0;
}

int main() {
	FILE* fp = fopen("sudoku.txt", "r");
	if (fp == NULL){
		printf("Read Error!\n");
		getchar();
		return -1;
	}
	int* sudoku = (int*)malloc(sizeof(int) * 9 * 9);
	int i, j;
	for (i = 0; i < 9; ++i) {
		for (j = 0; j < 9; ++j) {
			fscanf(fp, "%d",sudoku + i * 9 + j);
		}
	}

	int isSolved = solve(sudoku, 0, 0);

	for (i = 0; i < 9; ++i) {
		for (j = 0; j < 9; ++j) {
			printf("%d ", sudoku[i * 9 + j]);
		}
		printf("\n");
	}

	if (isSolved) {
		printf("Solved Successfully!\n");
	}
	else printf("Error Solving!\n");
	getchar();
	return 0;
}