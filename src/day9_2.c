#include"load.h"
#include<string.h>
static const int preambleLen = 25;
void day9_2(){
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
	printf("This is borked: %lld\n", numbers[x]);
	int theBorked = numbers[x];
	/*Searching for contiguos*/
	int u;
	int l;
	int a;
	for(u = x-1; u >= 0; u--)
	{
		for(l = 0; l < u; l++)
		{
			a = 0;
			for(int i = l; i <= u; i++)
			{
				a += numbers[i];
			}
			if(a == theBorked) goto foundContig;
		}
	}
	printf("No found\n");
	return;
foundContig:;
	unsigned long long smallest = ~0;
	unsigned long long greatest = 0;
	for(unsigned long long i = l; i <= u; i++)
	{
		greatest = (numbers[i] > greatest) ? numbers[i] : greatest;
		smallest = (numbers[i] < smallest) ? numbers[i] : smallest;
	}
	printf("smallest: %llu | largest: %llu | sum: %llu\n", smallest, greatest, smallest + greatest);
}
