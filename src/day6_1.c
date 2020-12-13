#include"load.h"
#include<string.h>
char *delimit(char **input)
{
	char *next = strstr(*input, "\n\n");
	if(!next)
		return NULL;
	unsigned long long len = (unsigned long long)(next - *input);
	char *group = calloc(len, sizeof(char));
	int i2 = 0;
	for(int i = 0; i < len; i++)
		if((*input)[i] != '\n') group[i2++] = (*input)[i];
	*input = next + 2;
	return group;
}
void day6_1(){
	char *input = loadinput("day6-1.txt");
	int counts = 0;
	char *group;
	char *next = input;
	while(1)
	{
		unsigned int letters = 0;
		group = delimit(&next);
		if(!group) break;
		int len = strlen(group);
		//printf("<%s>\n\n", group);
		for(int i = 0; i < len; i++)
			letters |= (1 << (group[i] - 'a'));
		for(int i = 0; i < 26; i++)
			if((letters >> i) & 1) counts++;
		free(group);
	}
	printf("count: %d\n", counts);
	free(input);
}
