#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT "input.txt"

int main()
{
	int depth = 0;
	int position = 0;
	long answer;

	FILE* input = fopen(INPUT, "r");
	char command[10];
	int distance;

	while(!feof(input)){
		fscanf(input, "%s %d", command, &distance);
		
		if(!strcmp(command, "forward")){
			position += distance;
		}
		else if(!strcmp(command, "down")){
			depth += distance;
		}
		else if(!strcmp(command, "up")){
			depth -= distance;
		}
		else{
			printf("Command not read properly\n");
			return -1;
		}
	}
	fclose(input);

	answer = depth * position;
	printf("Answer: %ld\n", answer);
	return 0;
}