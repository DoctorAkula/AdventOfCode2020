#include"load.h"
#include<string.h>
static long long findLoops(int key)
{
	long long loops;
	int subject = 7;
	long long value = 1;
	for(loops = 1; 1; loops++)
	{
		value *= subject;
		value %= 20201227ll;
		if(value == key)
			break;
	}
	return loops;
}
static long long doLoops(long long subject, int loopCount)
{
	long long value = 1;
	for(int i = 0; i < loopCount; i++)
	{
		value *= subject;
		value %= 20201227ll;
	}
	return value;
}
void day25_1(){
	//char *input = loadinput("../input/test19.txt");
	char *input = loadinput("../input/day25-1.txt");
	char *second = strchr(input, '\n');
	if(!second)
	{
		printf("Bad Input file");
		return;
	}
	/*Parse input*/
	int secKey = atoi(second + 1);
	int firKey = atoi(input);
	printf("First Key: %d\nSecond Key: %d\n", firKey, secKey);
	/*Find loop count*/
	long long firLoops = findLoops(firKey);
	long long secLoops = findLoops(secKey);
	printf("First Key Loops: %lld\n", firLoops);
	printf("Second Key Loops: %lld\n", secLoops);
	/*Encrypt keys*/
	long long firEncrypt = doLoops(firKey, secLoops);
	long long secEncrypt = doLoops(secKey, firLoops);
	printf("First encryption: %lld\n", firEncrypt);
	printf("Second encryption: %lld\n", secEncrypt);
	/*Done*/
	free(input);
}
