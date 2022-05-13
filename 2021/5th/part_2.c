#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INPUT "input.txt"
#define GRID_WIDTH 1000

typedef struct Point{
	int x;
	int y;
	int count;
} Point;

bool point_eq(Point self, Point other){
	return self.x == other.x && self.y == other.y;
}

bool point_lt(Point self, Point other){
	return self.y < other.y;
}

typedef struct Grid{
	Point grid[GRID_WIDTH][GRID_WIDTH];
	int dangerous;
} Grid;

void grid_setup(Grid* points){
	points->dangerous = 0;

	Point point;
	int i, j;

	for (i = 0; i < GRID_WIDTH; i++){
		for (j = 0; j < GRID_WIDTH; j++){
			point.x = i;
			point.y = j;
			point.count = 0;

			points->grid[i][j] = point;
		}
	}
}

Grid points;

bool is_diagonal(int* left, int* right){
	return left[0] != right[0] && left[1] != right[1];
}

bool is_horizontal(int* left, int* right){
	return left[1] == right[1];
}

void create_horizontal(lower, upper, y){
	Point* current;
	int i;

	for (i = lower; i <= upper; i++){
		current = &points.grid[i][y];
		
		current->count++;
		if (current->count == 2){
			points.dangerous++;
		}
	}
}

void create_vertical(lower, upper, x){
	Point* current;
	int i;

	for (i = lower; i <= upper; i++){
		current = &points.grid[x][i];

		current->count++;
		if (current->count == 2){
			points.dangerous++;
		}
	}
}

void find_smaller_x(int* left, int* right, int** smaller, int** larger){
	if (left[0] < right[0]){
		*smaller = left;
		*larger = right;
	}
	else{
		*smaller = right;
		*larger = left;
	}
}

void create_diagonal_down(int* smaller, int* larger){
	Point* current;
	int i, y;

	for (i = smaller[0], y = smaller[1]; i <= larger[0]; i++, y++){
		current = &points.grid[i][y];

		current->count++;
		if (current->count == 2){
			points.dangerous++;
		}
	}
}

void create_diagonal_up(int* smaller, int* larger){
	Point* current;
	int i, y;

	for (i = smaller[0], y = smaller[1]; i <= larger[0]; i++, y--){
		current = &points.grid[i][y];

		current->count++;
		if (current->count == 2){
			points.dangerous++;
		}
	}
}

int main(){
	grid_setup(&points);

	FILE* input = fopen(INPUT, "r");
	int left[2], right[2];
	int *smaller, *larger;

	do{
		fscanf(input, " %d,%d -> %d,%d ", &left[0], &left[1], &right[0], &right[1]);

		if (is_diagonal(left, right)){
			find_smaller_x(left, right, &smaller, &larger);
			if (smaller[1] < larger[1]){
				create_diagonal_down(smaller, larger);
			}
			else{
				create_diagonal_up(smaller, larger);
			}
		}
		else if (is_horizontal(left,right)){
			if (left[0] < right[0]){
				create_horizontal(left[0], right[0], left[1]);
			}
			else{
				create_horizontal(right[0], left[0], left[1]);
			}
		}
		else{
			if (left[1] < right[1]){
				create_vertical(left[1], right[1], left[0]);
			}
			else{
				create_vertical(right[1], left[1], left[0]);
			}
		}
	}while(!feof(input));
	fclose(input);

	printf("Number of points: %d\n", points.dangerous);

	return 0;
}