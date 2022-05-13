#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INPUT "input.txt"
#define NUM_LEN 12

int b_array_to_i(int array[]){
	int ret = 0;

	for(int i = 0; i < NUM_LEN; i++){
		ret += array[i] * pow(2, NUM_LEN - 1 - i);
	}

	return ret;
}

void print_array(int tally[]){
	for(int i = 0; i < NUM_LEN; i++){
		printf("%d ", tally[i]);
	}
	printf("\n");
}

int main()
{
	int gamma[NUM_LEN] = {0};
	int epsilon[NUM_LEN] = {0};
	int tally[NUM_LEN] = {0};

	FILE* input = fopen(INPUT, "r");
	int i;
	char c;

	while(!feof(input)){
		for(i = 0; i <= NUM_LEN; i++){
			c = fgetc(input);

			switch(c){
				case '0':
					tally[i] -= 1;
					break;
				
				case '1':
					tally[i] += 1;
					break;
			}
		}
	}
	fclose(input);

	for(i = 0; i < NUM_LEN; i++){
		if(tally[i] > 0){
			gamma[i] = 1;
			epsilon[i] = 0;
		}
		else if(tally[i] < 0){
			gamma[i] = 0;
			epsilon[i] = 1;
		}
		else{
			printf("Equal number of ones and zeroes\n");
			return -1;
		}
	}
	
	int g = b_array_to_i(gamma);
	int e = b_array_to_i(epsilon);
	long answer = g * e;
	
	printf("Power Consumption: %ld", answer);
	return 0;
}