#include"load.h"
#include<string.h>
void day13_1(){
	char *input = loadinput("../input/day13-1.txt");
	int earliest = atoi(input);
	printf("<%d>\n", earliest);
	char *dupin = strchr(input, '\n') + 1;
	int *buffer = NULL;
	int numCount = 0;
	while((dupin = strchr(dupin, ','))){
		dupin++;
		if(*dupin == 'x') continue;
		buffer = realloc(buffer, (numCount+1) * sizeof(int));
		buffer[numCount] = atoi(dupin);
		numCount++;
	}
	unsigned int smallest = ~0;
	int quotient = 0;
	int fastest = 0;
	for(int i = 0; i < numCount; i++)
	{
		div_t qurem = div(earliest, buffer[i]);
		printf("%d / %d:\nquotient: %d\nremainder: %d\n\n",
				earliest,
				buffer[i],
				qurem.quot, 
				qurem.rem);
		int dif = buffer[i] - qurem.rem;
		if(dif < smallest)
		{
			smallest = dif;
			fastest = i;
			quotient = qurem.quot;
		}
	}
	quotient++;
	printf("%d * ((%d * %d) - %d) = %d\n",
			buffer[fastest],
			buffer[fastest],
			quotient,
			earliest,
			buffer[fastest] * ((buffer[fastest] * quotient)- earliest));
	free(buffer);
	free(input);
}
