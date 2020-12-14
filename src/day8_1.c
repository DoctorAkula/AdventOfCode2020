#include"load.h"
#include<string.h>
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
void day8_1(){
	char *input = loadinput("../input/day8-1.txt");
	int inputlen = strlen(input);
	int proglen = 0;
	for(int i = 0; i < inputlen; i++)
		if(input[i] == '\n') proglen++;
	bool *visited = calloc(proglen, sizeof(bool));
	char bootCode[proglen][10];

	free(input);
}
