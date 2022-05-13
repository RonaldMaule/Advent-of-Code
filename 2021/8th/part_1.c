#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT "input.txt"

typedef struct Trial{
	char numbers[10][8];
	char output[4][8];
}Trial;

void print_trial(Trial trial){
	int i;
	for (i = 0; i < 9; i++){
		printf("%s\n", trial.numbers[i]);
	}
	printf("\n");
	for (i = 0; i < 4; i++){
		printf("%s\n", trial.output[i]);
	}
	printf("\n");
}

int count_easy(Trial trial){
	int count = 0;

	size_t n;
	for (int i = 0; i < 4; i++){
		n = strlen(trial.output[i]);

		if (n == 2 || n == 3 || n == 4 || n == 7){
			count++;
		}
	}
	return count;
}

int main(){
	Trial* trials = (Trial*)malloc(5 * sizeof(Trial));
	int trials_len = 5, num_trials = 0;

	FILE* input = fopen(INPUT, "r");
	while(!feof(input)){
		fscanf(input, " %s %s %s %s %s %s %s %s %s %s | %s %s %s %s ",
			trials[num_trials].numbers[0],
			trials[num_trials].numbers[1],
			trials[num_trials].numbers[2],
			trials[num_trials].numbers[3],
			trials[num_trials].numbers[4],
			trials[num_trials].numbers[5],
			trials[num_trials].numbers[6],
			trials[num_trials].numbers[7],
			trials[num_trials].numbers[8],
			trials[num_trials].numbers[9],

			trials[num_trials].output[0],
			trials[num_trials].output[1],
			trials[num_trials].output[2],
			trials[num_trials].output[3]);
		
		num_trials++;

		if (num_trials >= trials_len){
			trials = (Trial*)realloc((void*)trials, (trials_len+5) * sizeof(Trial));
			trials_len += 5;
		}
	}
	fclose(input);

	int count = 0;
	for (int i = 0; i < num_trials; i++){
		count += count_easy(trials[i]);
	}

	printf("Count: %d\n", count);
	
	free(trials);
	return 0;
}