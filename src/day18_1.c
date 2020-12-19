#include"load.h"
#include<string.h>
#include<stdbool.h>
static long long PerformMath(char *line, int *idp)
{
	int id = *idp;
	long long val = 0;
	char Operator = 0;
	do{
		switch(line[id]){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if(Operator == '+')
					val += atoll(line+id);
				else if(Operator == '*')
					val *= atoll(line+id);
				else
					val = atoll(line+id);
				int span = strspn(line+id, "0123456789") - 1;
				id += span;
				break;
			case '(':
				id++;
				if(Operator == '+')
					val += PerformMath(line, &id);
				else if(Operator == '*')
					val *= PerformMath(line, &id);
				else
					val = PerformMath(line, &id);
				break;
			case ')':
				*idp = id;
				return val;
				break;
			case '*':
			case '+':
				Operator = line[id];
				break;
		}
	}while(line[id++] != '\0');
	return val;
}
void day18_1(){
	char *input = loadinput("../input/day18-1.txt");
	char *dupin = input;
	/*Split into lines*/
	char **lines = NULL;
	int lineCount = 0;
	while(1)
	{
		lineCount++;
		lines = realloc(lines, lineCount * sizeof(char*));
		lines[lineCount - 1] = dupin;
		dupin = strchr(dupin, '\n');
		if(!dupin) break;
		*dupin = '\0';
		dupin++;
	}
	lineCount--;
	/*Check if input was split correctly*/
	printf("Lines: %d\n", lineCount);
	for(int i = 0; i < lineCount; i++)
		printf("<%s>\n", lines[i]);
	/*Start Parsing Lines*/
	long long cumSum = 0;
	for(int i = 0; i < lineCount; i++){
		int start = 0;
		long long val = PerformMath(lines[i], &start);
		cumSum += val;
		printf("Cumulative: %lld, Result:%lld\n", cumSum, val);
	}
	free(input);
}
