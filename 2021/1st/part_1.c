#include <stdlib.h>
#include <stdio.h>

#define INPUT "input.txt"

int main()
{
int previous_line;
int line;
int tally = 0;

FILE* input = fopen(INPUT, "r");
fscanf(input, "%d", &previous_line);

while(!feof(input)) {
	fscanf(input, "%d", &line);
	if(line > previous_line){
		tally++;
	}

	previous_line = line;
}
fclose(input);

printf("Tally: %d", tally);

return 0;
}