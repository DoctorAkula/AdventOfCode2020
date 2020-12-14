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
void countBags(char *input, char *bagname, int bagCount, bool *containGold) 
{
	char *dupein = input;
	for(int i = 0; i < bagCount; i++)
	{
		char *rules = delimBagLines(&dupein);
		if(!rules)
			return;
		char *next = strstr(rules, " contain");
		if(!next)
			return;
		unsigned long long containlen = (unsigned long long)(next - rules);
		char *containName = calloc(containlen, sizeof(char));
		strncpy(containName, rules, containlen);
		if(containName[containlen-1] == 's')
			containName[containlen-1] = '\0';
		else
			containName[containlen] = '\0';

		if(strstr(next, bagname))
		{
		//	printf("name:%s\n<%s>\n\n", containName, next);
			containGold[i] = true;
			countBags(input, containName, bagCount, containGold);
		}

		free(containName);
		free(rules);
	}
}
void day7_1(){
	char *input = loadinput("../input/day7-1.txt");
	int i = 0;
	int bagCount = 0;
	while(input[i] != '\0')
		if(input[i++] == '\n') bagCount++;
	bool *containGold = calloc(bagCount, sizeof(bool));
	printf("%d\n", bagCount);
	countBags(input, "shiny gold bag", bagCount, containGold);
	int count = 0;
	for(i  = 0; i < bagCount; i++)
	{
		printf("%d", containGold[i]);
		if(containGold[i]) count++;
	}
	printf("\nBag Containers: %d\n", count);
	free(containGold);
	free(input);
}
