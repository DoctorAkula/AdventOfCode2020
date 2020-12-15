#include"load.h"
#include<string.h>
#include<stdbool.h>
char *DelimBagLines(char **input)
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
void ParseInputIntoNamesAndEntries(char *input, char **bagRuleName, char **bagRuleEntry, int bagCount) 
{
	char *dupein = input;
	for(int i = 0; i < bagCount; i++)
	{
		char *rules = DelimBagLines(&dupein);
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
int countBags(char **bagRuleName, char **bagRuleEntry, char *searchName, int bagCount)
{
	int retVal = 0;
	for(int i = 0; i < bagCount; i++)
	{
		if(strstr(bagRuleName[i], searchName))
		{
			retVal = countBags(bagRuleName, bagRuleEntry, "placeholder", bagCount);
		}
	}
	return retVal;
}
void day7_2(){
	char *input = loadinput("../input/day7-1.txt");
	int i = 0;
	int bagCount = 0;
	while(input[i] != '\0')
		if(input[i++] == '\n') bagCount++;
	char **bagRuleName = calloc(bagCount, sizeof(char*));
	char **bagRuleEntry = calloc(bagCount, sizeof(char*));
	printf("%d\n", bagCount);
	ParseInputIntoNamesAndEntries(input, bagRuleName, bagRuleEntry, bagCount);
	int count = countBags(bagRuleName, bagRuleEntry, "shiny gold bags", bagCount);
	printf("\nBag Containers: %d\n", count);
	free(input);
}
