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
void parseInputIntoNamesAndEntries(char *input, char **bagRuleName, char **bagRuleEntry, int bagCount) 
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
		unsigned long long nextlen = strlen(next);
		bagRuleEntry[i] = calloc(nextlen, sizeof(char));
		bagRuleName[i] = calloc(containlen, sizeof(char));
		strncpy(bagRuleName[i], rules, containlen);
		strncpy(bagRuleEntry[i], next, nextlen);
		if(bagRuleName[i][containlen-1] == 's')
			bagRuleName[i][containlen-1] = '\0';
		else
			bagRuleName[i][containlen] = '\0';

		free(rules);
	}
}
void detectBags(char **bagRuleName, char **bagRuleEntry, bool *containGold, char *searchName, int bagCount)
{
	for(int i = 0; i < bagCount; i++)
	{
		if(strstr(bagRuleEntry[i], searchName))
		{
			containGold[i] = true;
			detectBags(bagRuleName, bagRuleEntry, containGold, bagRuleName[i], bagCount);
		}
	}
}
void day7_1(){
	char *input = loadinput("../input/day7-1.txt");
	int i = 0;
	int bagCount = 0;
	while(input[i] != '\0')
		if(input[i++] == '\n') bagCount++;
	bool *containGold = calloc(bagCount, sizeof(bool));
	char **bagRuleName = calloc(bagCount, sizeof(char*));
	char **bagRuleEntry = calloc(bagCount, sizeof(char*));
	printf("%d\n", bagCount);
	parseInputIntoNamesAndEntries(input, bagRuleName, bagRuleEntry, bagCount);
	detectBags(bagRuleName, bagRuleEntry, containGold, "shiny gold bag", bagCount);
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
