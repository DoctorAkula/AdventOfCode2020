#include"load.h"
void day5_2(){
	char *input = loadinput("../input/day5-1.txt");
	int i = 0;
	int arPoint = 0;
	int bitpos = 9;
	int currentValue = 0;
	int numCount = 0;
	while(input[i] != '\0')
		if(input[i++] == '\n') numCount++;
	i = 0;
	int *passIDS = calloc(numCount, sizeof(int));
	while(input[i] != '\0')
	{
		switch(input[i])
		{
			case 'B': 
				currentValue |= 1 << bitpos;
				break;
			case 'R':
				currentValue |= 1 << bitpos;
				break;
			case '\n':
				passIDS[arPoint++] = currentValue;
				bitpos = 10;
				currentValue = 0;
				break;
		}
		bitpos--;
		i++;
	}
	qsort(passIDS, numCount, sizeof(int), cmpfunc);
	for(i = 1; i < numCount; i++)
	{
		if((passIDS[i-1] + 2) == (passIDS[i]))
			break;
	}
	printf("My Passport: %d\n", passIDS[i]-1);
	free(input);
}
