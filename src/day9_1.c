#include"load.h"
#include<string.h>
static const int preambleLen = 25;
void day9_1(){
	char *input = loadinput("../input/day9-1.txt");
	char *dupin = input;
	int listSize = 0;
	while(*dupin++ != '\0')
		if(*dupin == '\n') listSize++;
	long long numbers[listSize];
	dupin = input;
	for(int i = 0; i < listSize; i++)
	{
		numbers[i] = atoll(dupin);
		dupin = strchr(dupin, '\n');
		if(!dupin) break;
		dupin++;
	}
	int x;
	for(x = preambleLen; x < listSize; x++)
	{
		for(int y = 1; y <= preambleLen; y++)
			for(int z = 1; z <= preambleLen; z++)
				if(numbers[x] == (numbers[x - y] + numbers[x - z])) goto found;
		goto notfound;
found:
		continue;
	}
	free(input);
	printf("all is well\n");
	return;
notfound:
	printf("This is borked: %d\n", numbers[x]);
	return;
}
