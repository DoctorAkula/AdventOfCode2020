#include"load.h"
void day1_2(){
	char *input = loadinput("../input/day1-1.txt");
	int numcount = 0;
	int i = 0;
	while(input[i++] != '\0')
		if(input[i] == '\n') numcount++;
	int numbers[numcount];
	char *dupein = input;
	for(i = 0; i < numcount; i++)
	{
		numbers[i] = atoi(dupein);
		while(*dupein++ != '\n');
	}
	int x,y,z;
	for(x = 0; x < numcount; x++)
		for(y = 0; y < numcount; y++)
			for(z = 0; z < numcount; z++)
				if((numbers[x] + numbers[y] + numbers[z]) == 2020) goto found;
found:
	printf("%d * %d * %d = %d\n",
		numbers[x],
		numbers[y],
		numbers[z],
		numbers[x] * numbers[y] * numbers[z]);
	free(input);
}
