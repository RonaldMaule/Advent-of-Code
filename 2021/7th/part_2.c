#include <stdlib.h>
#include <stdio.h>

#define INPUT "input.txt"

unsigned int find_cost_position(int x, int* positions, int size){
	int cost = 0, n;

	for (int i = 0; i < size; i++){
		n = 1 + abs(positions[i] - x);
		cost += n * (n - 1) / 2;
	}

	return cost;
}

void find_min_max(int* array, int size, int* small, int* large){
	int s = array[0], l = array[0];
	int current;

	for (int i = 0; i < size; i++){
		current = array[i];
		if (current < s){
			s = current;
		}
		if (current > l){
			l = current;
		}
	}
	*small = s;
	*large = l;
}

void min(unsigned int* array, int size, unsigned int* small){
	unsigned int s = array[0];
	int current;

	for (int i = 0; i < size; i++){
		current = array[i];
		if (current < s){
			s = current;
		}
	}
	*small = s;
}

int main(){
	FILE* input = fopen(INPUT, "r");
	int* positions = (int*)malloc(5 * sizeof(int));
	int pos_size = 5, num_crabs = 0;

	int crab;
	while(!feof(input)){
		fscanf(input, "%d,", &crab);
		positions[num_crabs++] = crab;

		if (num_crabs >= pos_size){
			positions = (int*)realloc((void*)positions, (pos_size+5) * sizeof(int));
			pos_size += 5;
		}
	}
	fclose(input);

	int small, large;
	find_min_max(positions, num_crabs, &small, &large);

	int diff = (large - small) + 1;

	unsigned int* fuel_costs = (unsigned int*)malloc(diff * sizeof(int));
	for (int pos = small, i = 0; pos <= large; pos++, i++){
		fuel_costs[i] = find_cost_position(pos, positions, num_crabs);
	}

	unsigned int cheapest;
	min(fuel_costs, diff, &cheapest);

	printf("Minimum: %d\n", cheapest);

	free(positions);
	free(fuel_costs);
	return 0;
}