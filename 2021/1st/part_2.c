#include <stdlib.h>
#include <stdio.h>

#define INPUT "input.txt"

int main()
{
int line_1, line_2, line_3;
int line;

int tally = 0;

FILE* input = fopen(INPUT, "r");
fscanf(input, "%d %d %d", &line_1, &line_2, &line_3);

while(!feof(input)) {
	fscanf(input, "%d", &line);
	
	if(line_2 + line_3 + line > line_1 + line_2 + line_3){
		tally++;
	}
	line_1 = line_2;
	line_2 = line_3;
	line_3 = line;
}
fclose(input);

printf("Tally: %d", tally);
return 0;
}