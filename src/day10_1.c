#include"load.h"

void day10_1(){
	char *input = loadinput("../input/day10-1.txt");
	int i = 0;
	int totalNum = 0;
	while(input[i] != '\0')
		if(input[i++] == '\n') totalNum++;
	int adapters[totalNum + 1];
	char *index = input;
	for(i = 0; i < totalNum; i++)
	{
		adapters[i] = atoi(index);
		while(*index++ != '\n');
	}
	qsort(adapters, totalNum, sizeof(int), cmpfunc);
	int Onejolts = 0;
	int Threejolts = 0;
	for(i = 1; i < totalNum; i++)
	{
		int dif = adapters[i] - adapters[i - 1];
		if(dif == 3)
			Threejolts++;
		else if(dif == 1)
			Onejolts++;
	}
	Threejolts++;
	Onejolts++;
	printf("\n%d\n", totalNum);
	printf("%d * %d = %d\n",
			Onejolts,
			Threejolts,
			Onejolts * Threejolts);
}
