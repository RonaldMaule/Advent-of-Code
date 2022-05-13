#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT "input.txt"

int main()
{
	int depth = 0;
	int position = 0;
	int aim = 0;

	FILE* input = fopen(INPUT, "r");
	char command[10];
	int distance;

	while(!feof(input)){
		fscanf(input, "%s %d", command, &distance);

		if(!strcmp(command, "forward")){
			position += distance;
			depth += distance * aim;
		}
		else if(!strcmp(command, "down")){
			aim += distance;
		}
		else if(!strcmp(command, "up")){
			aim -= distance;
		}
		else{
			printf("Command not read properly\n");
			return -1;
		}
	}
	fclose(input);

	long answer = depth * position;
	printf("Answer: %ld\n", answer);
	return 0;
}