#include"load.h"
#include<string.h>
void day8_1(){
	char *input = loadinput("../input/day8-1.txt");
	int inputlen = strlen(input);
	int proglen = 0;
	for(int i = 0; i < inputlen; i++)
		if(input[i] == '\n') proglen++;
	free(input);
}
