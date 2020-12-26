#include"load.h"
#include<string.h>
#define MASKSIZE 36
static void printBin(unsigned long long val)
{
	for(int i = MASKSIZE - 1; i >= 0; i--)
		printf("%lld", (val >> i) & 1);
	putchar('\n');
}
void day14_1(){
	char *input = loadinput("../input/day14-1.txt");
	unsigned long long Onmask;
	unsigned long long Offmask;
	char *dupin = input;
	unsigned long long *mem = calloc(0x10000, sizeof(long long));
	int larIndex = 0;
	do{
		int hash = dupin[0] + (dupin[1] << 1) + (dupin[2] << 2);
		int curIndex = 0;
		switch(hash){
			case ('m' + ('a' << 1) + ('s' << 2)):
				Onmask = 0;
				Offmask = 0;
				for(int i = 0; i < MASKSIZE; i++)
				{
					switch(dupin[MASKSIZE - i + 6]){
						case '0':
							Offmask |= (unsigned long long)1 << i;
							putchar(dupin[i + 7]);
							break;
						case '1':
							Onmask |= (unsigned long long)1 << i;
							putchar(dupin[i + 7]);
							break;
						default:
							putchar(dupin[i + 7]);
					}
				}
				putchar('\n');
				printBin(Onmask);
				printBin(Offmask);
				break;
			case ('m' + ('e' << 1) + ('m' << 2)):
				curIndex = atoi(dupin + 4);
				if(curIndex > larIndex)
					larIndex = curIndex;
				dupin = strchr(dupin, '=') + 1;
				unsigned long long val = atoi(dupin);
				val |= Onmask;
				val &= ~Offmask;
				mem[curIndex] = val;
				printf("mem[%d] = %llu\n", curIndex, val);
				break;
		}
	}while( (dupin = strchr(dupin, '\n') + 1) != (void*)1);
	unsigned long long cumSum = 0;
	for(int i = 0; i <= larIndex; i++)
		cumSum += mem[i];
	
	printf("cumulative sum: %llu\n", cumSum);
	free(mem);
	free(input);
}
