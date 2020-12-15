#include"load.h"
#include<string.h>
#include<stdbool.h>
void delimTheCode(char *input, char **bootCode, int proglen) 
{
	char *dupein = input;
	for(int i = 0; i < proglen; i++)
	{
		char *next = strchr(dupein, '\n');
		if(!next) continue;
		size_t instLen = (size_t)(next - dupein);
		bootCode[i] = calloc(instLen + 1, sizeof(char));
		strncpy(bootCode[i], dupein, instLen);
		dupein = next + 1;
	}
}
void day8_1(){
	char *input = loadinput("../input/day8-1.txt");
	int inputlen = strlen(input);
	int proglen = 0;
	for(int i = 0; i < inputlen; i++)
		if(input[i] == '\n') proglen++;
	bool *visited = calloc(proglen, sizeof(bool));
	char **bootCode = calloc(proglen, sizeof(char*));
	delimTheCode(input, bootCode, proglen);
	int pc = 0;
	int a = 0;
	/*Useless VM!*/
	while(!visited[pc])
	{
		unsigned int iHash = (bootCode[pc][0]) + (bootCode[pc][1] << 1) + (bootCode[pc][2] << 2);
		visited[pc] = true;
		int op = 0;
		switch(iHash)
		{
			/*nop*/
			case (('n')+('o'<<1)+('p'<<2)):
				op = atoi(bootCode[pc] + 3);
				printf("nop = %d\n", op);
				break;
			/*jmp*/
			case (('j')+('m'<<1)+('p'<<2)):
				op = atoi(bootCode[pc] + 3);
				printf("jmp = %d\n", op);
				pc += op - 1;
				break;
			/*acc*/
			case (('a')+('c'<<1)+('c'<<2)):
				op = atoi(bootCode[pc] + 3);
				printf("acc = %d\n", op);
				a += op;
				break;
			default:
				puts("illegal opcode");
		}
		pc++;
	}
	printf("Accumulator: %d\n", a);
	free(input);
}
