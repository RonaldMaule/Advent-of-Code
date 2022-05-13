#include <stdlib.h>
#include <stdio.h>

#define INPUT "input.txt"
#define NUM_DAYS 256

void clear_array(unsigned long* array){
	for (int i = 0; i < 9; i++){
		array[i] = 0;
	}
}

void copy_array(unsigned long* self, unsigned long* other){
	for (int i = 0; i < 9; i++){
		self[i] = other[i];
	}
}

void print_array(unsigned long* array){
	for (int i = 0; i < 9; i++){
		printf("%lu ", array[i]);
	}
	printf("\n");
}

unsigned long count_fish(unsigned long* school){
	unsigned long count = 0;
	for (int i = 0; i < 9; i++){
		count += school[i];
	}
	return count;
}

int main(){
	unsigned long school[9] = {0};
	FILE* input = fopen(INPUT, "r");

	int num;
	while(!feof(input)){
		fscanf(input, "%d,", &num);
		school[num]++;
	}
	fclose(input);

	unsigned long temp[9], i;
	for (int day = 0; day < NUM_DAYS; day++){
		clear_array(temp);

		for (i = 0; i < 9; i++){
			if (i == 0){
				temp[6] += school[0];
				temp[8] += school[0];
			}
			else{
				temp[i-1] += school[i];
			}
		}
		copy_array(school, temp);
	}

	unsigned long num_fish = count_fish(school);

	printf("Num fish: %lu\n", num_fish);
	return 0;
}