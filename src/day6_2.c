#include"load.h"
#include<string.h>
char *Delimit(char **input)
{
	char *next = strstr(*input, "\n\n");
	if(!next)
		return NULL;
	unsigned long long len = (unsigned long long)(next - *input);
	char *group = calloc(len, sizeof(char));
	strncpy(group, *input, len);
	*input = next + 2;
	return group;
}
int DelimPeople(char *input, int len)
{
	int peepCount = 0;
	for(int i = 0; i < len; i++)
		if(input[i] == '\n') peepCount++;
	unsigned int *charFlags = calloc(peepCount, sizeof(int));
	int peepIndex = 0;
	for(int i = 0; i < len; i++)
	{
		if(('a' <= input[i]) && (input[i] <= 'z'))
			charFlags[peepIndex] |= (1 << (input[i] - 'a'));
		else if(input[i] == '\n')
			peepIndex++;
	}
	unsigned int mask = charFlags[0];
	for(int i = 1; i <= peepCount; i++)
		mask &= charFlags[i];
	int count = 0;
	for(int i = 0; i < 26; i++)
		if((mask >> i) & 1) count++;
	return count;
}
void day6_2(){
	char *input = loadinput("../input/day6-1.txt");
	int counts = 0;
	char *group;
	char *next = input;
	while(1)
	{
		unsigned int letters = 0;
		group = Delimit(&next);
		if(!group) break;
		int len = strlen(group);
		counts += DelimPeople(group, len);
		//printf("<%s>\n\n", group);
		free(group);
	}
	printf("count: %d\n", counts);
	free(input);
}
