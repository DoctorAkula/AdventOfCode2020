#include"load.h"
#include<string.h>
void day13_2(){
	char *input = loadinput("../input/day13-1.txt");
	int earliest = atoi(input);
	printf("<%d>\n", earliest);
	char *dupin = strchr(input, '\n') + 1;
	long long *buffer = NULL;
	long long *timebuf = NULL;
	int numCount = 0;
	int timeOff = -1;
	int largest = 0;
	int largestValOff = 0;
	while((dupin = strchr(dupin, ','))){
		dupin++;
		timeOff++;
		if(*dupin == 'x') continue;
		timebuf = realloc(timebuf, (numCount+1) * sizeof(long long));
		timebuf[numCount] = timeOff;
		buffer = realloc(buffer, (numCount+1) * sizeof(long long));
		buffer[numCount] = atoi(dupin);
		if(buffer[numCount] > largest){
			largest = buffer[numCount];
			largestValOff = timebuf[numCount];
		} 
		printf("%lld - %lld\n", timebuf[numCount], buffer[numCount]);
		numCount++;
	}

	for(int i = 0; i < numCount; i++)
	{
		timebuf[i] -= largestValOff;
		printf("New offsets: %lld\n", timebuf[i]);
	}
	printf("largest: %d\n", largest);
	unsigned long long factor = 1;
	unsigned long long prod;
	while(1){
		int i;
		prod = factor * largest;
		for(i = 0; i < numCount; i++)
		{
			lldiv_t qurem = lldiv(prod + timebuf[i], buffer[i]);
			/*printf("%llu mod %llu = %llu\n",
					prod + timebuf[i],
					buffer[i],
					qurem.rem);*/
			if(qurem.rem != 0){
				i = -1;
				break;
			}
		}
		if(i != -1) goto ende;
		factor++;
	}
ende:
	printf("earliest: %llu\n", prod + timebuf[0]);
	free(buffer);
	free(input);
}
