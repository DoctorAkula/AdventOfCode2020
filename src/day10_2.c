#include"load.h"
#include<stdbool.h>
void day10_2(){
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
	bool *removable = calloc(totalNum, sizeof(bool));
	adapters[totalNum] = adapters[totalNum - 1] + 3;
	for(i = 0; i < totalNum; i++)
	{	int difl;
		if(i == 0)
			difl = adapters[i] - 0;
		else
			difl = adapters[i] - adapters[i - 1];
		int difh = adapters[i + 1] - adapters[i];
		if((difl == 1) && (difh == 1))
			removable[i] = true;
	}
	int span = 0;
	unsigned long long cumProd = 1;
	for(i = 0; i < totalNum; i++)
	{
		if(removable[i])
			span++;
		else
		{
			switch(span){
				case 1:
					cumProd *= 2;
					break;
				case 2:
					cumProd *= 4;
					break;
				case 3:
					cumProd *= 7;
					break;
			}
			span = 0;
		}
	}
	printf("Total Combinations: %llu\n", cumProd);
}
