#include"load.h"
#include<stdbool.h>
#include<string.h>
void day1_1(){
	char *input = loadinput("../input/day1-1.txt");
	int numcount = 0;
	int i = 0;
	while(input[i++] != '\0')
		if(input[i] == '\n') numcount++;
	int numbers[numcount];
	int difference[numcount];
	char *dupein = input;
	bool found[2020]; //LUT for things
	memset(found, false, sizeof(found));
	for(i = 0; i < numcount; i++)
	{
		int num = atoi(dupein);
		numbers[i] = num;
		if(num < sizeof(found)) found[num] = true;
		difference[i] = 2020 - num;
		while(*dupein++ != '\n');
	}
	for(i = 0; i < numcount; i++)
	{
		if(found[difference[i]]) break;
	}
	printf("%d + %d = %d\n", 
		difference[i],
		2020 - difference[i],
		(2020 - difference[i]) * difference[i]);
	free(input);
}
