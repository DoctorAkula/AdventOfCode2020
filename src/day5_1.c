#include"load.h"
void day5_1(){
	char *input = loadinput("../input/day5-1.txt");
	int i = 0;
	int bitpos = 9;
	int largestValue = 0;
	int currentValue = 0;
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
				bitpos = 10;
				currentValue = 0;
				break;
		}
		if(largestValue < currentValue) largestValue = currentValue;
		bitpos--;
		i++;
	}
	printf("%d\n", largestValue);
	free(input);
}
