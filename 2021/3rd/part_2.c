#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

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

void get_line(FILE* input, int line[]){
	char c;
	
	for(int i = 0; i < NUM_LEN; i++){
		c = fgetc(input);
		line[i] = c - '0';
	}

	c = fgetc(input);
}

int main()
{
	int oxygen[NUM_LEN];
	int co2[NUM_LEN];

	FILE* input = fopen(INPUT, "r");
	int tally[NUM_LEN] = {0};
	int line[NUM_LEN];
	int i, j;
	bool Match;
	for(i = 0; i < NUM_LEN; i++){
		fseek(input, 0, SEEK_SET);

		while(!feof(input)){
			get_line(input, line);
			Match = true;

			for(j = 0; j < i; j++){
				if(line[j] != oxygen[j]){
					Match = false;
					break;
				}
			}

			if(Match == false){continue;}

			switch(line[i]){
				case 0:
					tally[i] -= 1;
					break;
				
				case 1:
					tally[i] += 1;
					break;
			}
		}

		if(tally[i] >= 0){
			oxygen[i] = 1;
		}
		else{
			oxygen[i] = 0;
		}
	}

	for(i = 0; i < NUM_LEN; i++){
		tally[i] = 0;
	}
	
	for(i = 0; i < NUM_LEN; i++){
		fseek(input, 0, SEEK_SET);
		int matching_numbers = 0;

		while(!feof(input)){
			get_line(input, line);
			Match = true;

			for(j = 0; j < i; j++){
				if(line[j] != co2[j]){
					Match = false;
					break;
				}
			}

			if(Match == false){continue;}
			
			matching_numbers += 1;

			switch(line[i]){
				case 0:
					tally[i] -= 1;
					break;
				
				case 1:
					tally[i] += 1;
					break;
			}
		}
		if(matching_numbers == 1){
			if(tally[i] == 1){
				co2[i] = 1;
			}
			else{
				co2[i] = 0;
			}
		}
		else{
			if(tally[i] >= 0){
				co2[i] = 0;
			}
			else if(tally[i] < 0){
				co2[i] = 1;
			}
		}
	}
	fclose(input);

	int ox = b_array_to_i(oxygen);
	int co = b_array_to_i(co2);
	long answer = ox * co;

	printf("Life Support Rating: %ld\n", answer);
	return 0;
}