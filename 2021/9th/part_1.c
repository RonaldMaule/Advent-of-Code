#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INPUT "input.txt"

bool is_lowpoint(int row, int col, int** heatmap, int num_row, int row_len){
	int point = heatmap[row][col];
	int left[2], right[2], up[2], down[2];
	bool l, r, u, d;

	left[0] = row; left[1] = col - 1;
	if (left[1] < 0){
		l = true;
	}
	else if (point < heatmap[left[0]][left[1]]){
		l = true;
	}
	else{
		l = false;
	}

	right[0] = row; right[1] = col + 1;
	if (right[1] >= row_len){
		r = true;
	}
	else if (point < heatmap[right[0]][right[1]]){
		r = true;
	}
	else{
		r = false;
	}

	up[0] = row - 1; up[1] = col;
	if (up[0] < 0){
		u = true;
	}
	else if (point < heatmap[up[0]][up[1]]){
		u = true;
	}
	else{
		u = false;
	}

	down[0] = row + 1; down[1] = col;
	if (down[0] >= num_row){
		d = true;
	}
	else if (point < heatmap[down[0]][down[1]]){
		d = true;
	}
	else{
		d = false;
	}

	return l && r && u && d;
}

int main(){
	FILE *input = fopen(INPUT, "r");
	char c;

	// Start with space for 5 rows
	int **heatmap = (int**)malloc(5 * sizeof(int*));
	int len_heatmap = 5, num_rows = 0;

	// Start with rows of 5 numbers
	heatmap[0] = (int*)malloc(5 * sizeof(int));
	int size = 5, row_len = 0;

	c = fgetc(input);
	while(c != '\n'){
		heatmap[0][row_len++] = c - '0';

		if (row_len >= size){
			heatmap[0] = (int*)realloc(heatmap[0], (size+5) * sizeof(int));
			size += 5;
		}
		c = fgetc(input);
	}
	num_rows = 1;
	
	int i, j;
	while (!feof(input)){
		heatmap[num_rows] = (int*)malloc(row_len * sizeof(int));

		for (i = 0; i < row_len; i++){
			c = fgetc(input);
			heatmap[num_rows][i] = c - '0';
		}

		fgetc(input);
		num_rows++;

		if (num_rows >= len_heatmap){
			heatmap = (int**)realloc(heatmap, (len_heatmap+5) * sizeof(int*));
			len_heatmap += 5;
		}
	}

	// Start with space for 5 lowpoints
	int* lowpoints = (int*)malloc(5 * sizeof(int));
	int space = 5, num_lp = 0;

	for (i = 0; i < num_rows; i++){
		for (j = 0; j < row_len; j++){
			if (is_lowpoint(i, j, heatmap, num_rows, row_len)){
				lowpoints[num_lp++] = heatmap[i][j];

				if (num_lp >= space){
					lowpoints = (int*)realloc(lowpoints, (space+5)*sizeof(int));
					space += 5;
				}
			}
		}
	}

	int risk_level = 0;
	for (i = 0; i < num_lp; i++){
		risk_level += lowpoints[i] + 1;
	}

	printf("Risk Sum: %d\n", risk_level);

	for (i = 0; i < num_rows; i++){
		free(heatmap[i]);
	}
	free(heatmap);
	free(lowpoints);
	return 0;
}