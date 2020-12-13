#include"load.h"
#include<string.h>
#include<stdbool.h>
char *delimBagLines(char **input)
{
	char *next = strchr(*input, '\n');
	if(!next)
		return NULL;
	unsigned long long len = (unsigned long long)(next - *input);
	char *group = calloc(len, sizeof(char));
	strncpy(group, *input, len);
	*input = next + 1;
	return group;
}
int countBags(char *input, char *bagname) 
{
	char *dupein = input;
	char *rules = delimBagLines(&dupein);
	char *containName;
	printf("<%s>\n\n", rules);
	free(rules);
}
void day7_1(){
	char *input = loadinput("../input/test6.txt");
	int i = 0;
	bagCount = 0;
	while(input[i] != '\0')
		if(input[i++] == '\n') bagCount++;
	bool *containGold = calloc(bagCount, sizeof(bool));
	free(input);
}
