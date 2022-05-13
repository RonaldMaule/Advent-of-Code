#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INPUT "input.txt"
#define ROW 5
#define COL 5

typedef struct PLACE {
	int value;
	bool marked;
} place;

typedef struct ANS {
	place **board;
	int guess;
} ans;

void display_board(place** board){
	int r, c;
	for (r = 0; r < ROW; r++){
		for (c = 0; c < COL; c++){
			printf("%d ", board[r][c].value);
		}
		printf("\t");
		for (c = 0; c < COL; c++){
			printf("%d ", board[r][c].marked);
		}
		printf("\n");
	}
}

void display_boards(place*** boards, int num_boards){
	for(int i = 0; i < num_boards; i++){
		display_board(boards[i]);
		printf("\n");
	}
}

bool check_board(place **board, int r, int c){
	bool bingo_row = true;
	for (int col = 0; col < COL; col++){
		if (board[r][col].marked == false){
			bingo_row = false;
			break;
		}
	}

	bool bingo_col = true;
	for (int row = 0; row < ROW; row++){
		if (board[row][c].marked == false){
			bingo_col = false;
			break;
		}
	}

	return bingo_row || bingo_col;
}

bool already_won(place **board, place ***winners, int num_winners){
	for (int i = 0; i < num_winners; i++){
		if (winners[i] == board){
			return true;
		}
	}
	return false;
}

void find_last_winner(place ***boards, int num_boards, int *guesses, int num_guesses, ans *answer){
	int guess, board, r, c;
	place *num;

	place ***winners = (place***)malloc(num_boards * sizeof(place**));
	int num_winners = 0;

	for (guess = 0; guess < num_guesses; guess++){
		for (board = 0; board < num_boards; board++){
			if (already_won(boards[board], winners, num_winners)){continue;}

			for (r = 0; r < ROW; r++){
				for (c = 0; c < COL; c++){
					num = &boards[board][r][c];
					if ((!num->marked) && num->value == guesses[guess]){
						num->marked = true;
						if (check_board(boards[board], r, c)){
							answer->board = boards[board];
							answer->guess = guesses[guess];

							winners[num_winners++] = boards[board];
						}
					}
				}
			}
		}
		if (num_winners == num_boards){break;}
	}
	free(winners);
}

int calculate_score(ans answer){
	place **board = answer.board;
	int guess = answer.guess;
	int score = 0, r, c;

	for (r = 0; r < ROW; r++){
		for (c = 0; c < COL; c++){
			if (board[r][c].marked == false){
				score += board[r][c].value;
			}
		}
	}

	return score * guess;
}

void free_boards(place*** boards, int num_boards){
	int current, r;
	for (current = 0; current < num_boards; current++) {
		for (r = 0; r < ROW; r++){
			free(boards[current][r]);
		}
		free(boards[current]);
	}
	free(boards);
}

int main()
{
	FILE *input = fopen(INPUT, "r");
	int num;
	char c;

	// Start with space for 5 guesses
	int *guesses = (int*)malloc(5 * sizeof(int));
	int len_guesses = 5, num_guesses = 0, current = 0;
	
	do{
		fscanf(input, "%d", &num);
		fscanf(input, "%c", &c);
		guesses[current] = num;
		current++;
		
		if (current >= len_guesses) {
			guesses = (int*)realloc((void*)guesses, (len_guesses + 5) * sizeof(int));
			len_guesses += 5;
		}
	}while(c != '\n');
	num_guesses = current;
	
	// Start with space for 5 boards
	place ***boards = (place***)malloc(5 * sizeof(place**));
	int len_boards = 5, num_boards = 0; current = 0;

	int first, second, third, fourth, fifth;
	while(!feof(input)){
		boards[current] = (place**)malloc(ROW * sizeof(place*));
		for (int r = 0; r < ROW; r++){
			boards[current][r] = (place*)malloc(COL * sizeof(place));
		}

		for (int r = 0; r < ROW; r++){
			fscanf(input, " %d %d %d %d %d ", &first, &second, &third, &fourth, &fifth);

			boards[current][r][0].value = first;
			boards[current][r][1].value = second;
			boards[current][r][2].value = third;
			boards[current][r][3].value = fourth;
			boards[current][r][4].value = fifth;

			for (int c = 0; c < COL; c++){
				boards[current][r][c].marked = false;
			}
		}
		current++;
		if (current >= len_boards) {
			boards = (place***)realloc((void*)boards, (len_boards + 5) * sizeof(place**));
			len_boards += 5;
		}
	}
	num_boards = current;
	fclose(input);

	ans answer;
	find_last_winner(boards, num_boards, guesses, num_guesses, &answer);
	int score = calculate_score(answer);

	printf("Score: %d\n", score); 

	free(guesses);
	free_boards(boards, num_boards);
	return 0;
}