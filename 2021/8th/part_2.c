#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define INPUT "input.txt"

typedef struct SimpleDict{
	char key;
	char value;
}Dict;

void insert(Dict d[], char key, char value){
	Dict* temp;
	for (int i = 0; i < 4; i++){
		temp = &d[i];

		if (temp->key == '0'){
			temp->key = key;
			temp->value = value;
			return;
		}
	}
	printf("Insert failed for key: %c value: %c\n", key, value);
}

typedef struct Trial{
	char input[10][8];
	char output[4][8];
	char numbers[10][8];
	Dict mapping[4];
	int number;
}Trial;

void print_trial(Trial trial){
	int i;
	for (i = 0; i < 9; i++){
		printf("%s\n", trial.input[i]);
	}
	printf("\n");
	for (i = 0; i < 4; i++){
		printf("%s\n", trial.output[i]);
	}
	printf("\n");
}

void setup_mapping(Trial* trial);
void find_easy(Trial* trial);
void find_a_c_f(Trial* trial);
void find_hard(Trial* trial, char fives[3][6], char sixes[3][7]);
void find_2_3_5(Trial* trial, char fives[3][6]);
void find_e(Trial* trial);
void find_0_6_9(Trial* trial, char sixes[3][7]);
void get_num(Trial* trial);
void symmetric_difference(char* left, char* right, char* c_1, char* c_2);
char translate(Trial* trial, char known);
bool str_eq(char* str1, char* str2);

void find_mappings(Trial* trial){
	setup_mapping(trial);

	find_easy(trial);

	find_a_c_f(trial);

	char fives[3][6], sixes[3][7];
	find_hard(trial, fives, sixes);

	find_2_3_5(trial, fives);

	find_e(trial);

	find_0_6_9(trial, sixes);

	get_num(trial);
}

void setup_mapping(Trial* trial){
	Dict temp;
	for (int i = 0; i < 4; i++){
		temp.key = '0';
		temp.value = '0';
		trial->mapping[i] = temp;
	}
}

void find_easy(Trial* trial){
	char* num;
	int n;

	for (int i = 0; i < 10; i++){
		num = trial->input[i];
		n = strlen(num);

		if (!(n == 2 || n == 3 || n == 4 || n == 7)){continue;}

		switch (n) {
			case 2:
				strcpy(trial->numbers[1], num);
				break;
			case 3:
				strcpy(trial->numbers[7], num);
				break;
			case 4:
				strcpy(trial->numbers[4], num);
				break;
			case 7:
				strcpy(trial->numbers[8], num);
				break;
		}
	}
}

void find_a_c_f(Trial* trial){
	char ret;
	symmetric_difference(trial->numbers[7], trial->numbers[1], &ret, NULL);
	insert(trial->mapping, ret, 'a');
	
	int count, i, j;
	for (i = 0; i < strlen(trial->numbers[1]); i++){
		count = 0;
		for (j = 0; j < 10; j++){
			if (strchr(trial->input[j], trial->numbers[1][i])){
				count++;
			}
		}

		if (count == 8){
			insert(trial->mapping, trial->numbers[1][i], 'c');
		}
		else if (count == 9){
			insert(trial->mapping, trial->numbers[1][i], 'f');
		}
	}
}

void find_hard(Trial* trial, char fives[3][6], char sixes[3][7]){
	int len_f = 0, len_s = 0;
	char* num;

	for (int i = 0; i < 10; i++){
		num = trial->input[i];

		if (strlen(num) == 5){
			strcpy(fives[len_f++], num);
		}
		else if (strlen(num) == 6){
			strcpy(sixes[len_s++], num);
		}
	}
}

void find_2_3_5(Trial* trial, char fives[3][6]){
	for (int i = 0; i < 3; i++){
		if (!strchr(fives[i], translate(trial, 'c'))){
			strcpy(trial->numbers[5], fives[i]);
		}
		else if (!strchr(fives[i], translate(trial, 'f'))){
			strcpy(trial->numbers[2], fives[i]);
		}
		else if (strchr(fives[i], translate(trial, 'c'))
				&& strchr(fives[i], translate(trial, 'f'))){
			strcpy(trial->numbers[3], fives[i]);
		}
		else{
			printf("%s was not found in fives.\n", fives[i]);
		}
	}
}

void find_e(Trial* trial){
	char* num_2 = trial->numbers[2];
	char* num_3 = trial->numbers[3];

	char diff_0, diff_1;
	symmetric_difference(num_2, num_3, &diff_0, &diff_1);

	if (diff_0 != translate(trial, 'f')){
		insert(trial->mapping, diff_0, 'e');
	}
	else if (diff_1 != translate(trial, 'f')){
		insert(trial->mapping, diff_1, 'e');
	}
}

void find_0_6_9(Trial* trial, char sixes[3][7]){
	for (int i = 0; i < 3; i++){
		if (!strchr(sixes[i], translate(trial, 'c'))){
			strcpy(trial->numbers[6], sixes[i]);
		}
		else if (!strchr(sixes[i], translate(trial, 'e'))){
			strcpy(trial->numbers[9], sixes[i]);
		}
		else if (strchr(sixes[i], translate(trial, 'c')) && strchr(sixes[i], translate(trial, 'e'))){
			strcpy(trial->numbers[0], sixes[i]);
		}
		else {
			printf("%s was not found in sixes.\n", sixes[i]);
		}
	}
}

void symmetric_difference(char left[], char right[], char* c_1, char* c_2){
	int n_left = strlen(left), n_right = strlen(right);
	int num_found = 0;

	bool found;
	int i, j;
	for (i = 0; i < n_left; i++){
		found = false;
		for (j = 0; j < n_right; j++){
			if (left[i] == right[j]){
				found = true;
				break;
			}
		}
		if (!found){
			if (num_found == 0){
				*c_1 = left[i];
				num_found++;
			}
			else{
				*c_2 = left[i];
			}
		}
	}

	for (i = 0; i < n_right; i++){
		found = false;
		for (j = 0; j < n_left; j++){
			if (right[i] == left[j]){
				found = true;
				break;
			}
		}
		if (!found){
			if (num_found == 0){
				*c_1 = right[i];
				num_found++;
			}
			else{
				*c_2 = right[i];
			}
		}
	}
}

char translate(Trial* trial, char known){
	Dict temp;
	for (int i = 0; i < 4; i++){
		temp = trial->mapping[i];
		
		if (temp.value == known){
			return temp.key;
		}
	}
	printf("Value [%c] not found in mapping.\n", known);
	return '\0';
}

unsigned int get_number(Trial* trial){
	return trial->number;
}

void get_num(Trial* trial){
	int out[4] = {0};
	char* temp;
	int i, j;
	for (i = 0; i < 4; i++){
		temp = trial->output[i];
		for (j = 0; j < 10; j++){
			if (str_eq(temp, trial->numbers[j])){
				out[i] = j;
				break;
			}
		}
	}

	int num = 0;
	for (i = 0; i < 4; i++){
		num += pow(10, 3-i) * out[i];
	}
	trial->number = num;
}

bool str_eq(char* str1, char* str2){
	if (strlen(str1) != strlen(str2)){
		return false;
	}

	int len = strlen(str1);

	bool found;
	int i, j;
	for (i = 0; i < len; i++){
		found = false;
		for (j = 0; j < len; j++){
			if (str1[i] == str2[j]){
				found = true;
				break;
			}
		}

		if (!found){
			return false;
		}
	}

	return true;
}

int main(){
	Trial* trials = (Trial*)malloc(5 * sizeof(Trial));
	int trials_len = 5, num_trials = 0;

	FILE* input = fopen(INPUT, "r");
	while(!feof(input)){
		fscanf(input, " %s %s %s %s %s %s %s %s %s %s | %s %s %s %s ",
			trials[num_trials].input[0],
			trials[num_trials].input[1],
			trials[num_trials].input[2],
			trials[num_trials].input[3],
			trials[num_trials].input[4],
			trials[num_trials].input[5],
			trials[num_trials].input[6],
			trials[num_trials].input[7],
			trials[num_trials].input[8],
			trials[num_trials].input[9],

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

	int i;
	for (i = 0; i < num_trials; i++){
		find_mappings(&trials[i]);
	}
	
	unsigned int count = 0;
	for (i = 0; i < num_trials; i++){
		count += get_number(&trials[i]);
	}
	
	printf("Count: %u\n", count);
	
	free(trials);
	return 0;
}