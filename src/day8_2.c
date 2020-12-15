#include"load.h"
#include<string.h>
#include<stdbool.h>
void DelimTheCode(char *input, char **bootCode, int proglen) 
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
void day8_2(){
	char *input = loadinput("../input/day8-1.txt");
	int inputlen = strlen(input);
	int proglen = 0;
	for(int i = 0; i < inputlen; i++)
		if(input[i] == '\n') proglen++;
	bool *visited = calloc(proglen, sizeof(bool));
	char **bootCode = calloc(proglen, sizeof(char*));
	DelimTheCode(input, bootCode, proglen);
	int pc;
	int a;
	for(int i = 0; i < proglen-1; i++)
	{
		pc = 0;
		a = 0;
		unsigned int oHash = (bootCode[i][0]) + (bootCode[i][1] << 1) + (bootCode[i][2] << 2);
		switch(oHash)
		{
			/*nop*/
			case (('n')+('o'<<1)+('p'<<2)):
				printf("%d:%s -> ", i, bootCode[i]);
				bootCode[i][0] = 'j';
				bootCode[i][1] = 'm';
				bootCode[i][2] = 'p';
				printf("%s\n", bootCode[i]);
				break;
			/*jmp*/
			case (('j')+('m'<<1)+('p'<<2)):
				printf("%d:%s -> ", i, bootCode[i]);
				bootCode[i][0] = 'n';
				bootCode[i][1] = 'o';
				bootCode[i][2] = 'p';
				printf("%s\n", bootCode[i]);
				break;
			case (('a')+('c'<<1)+('c'<<2)):
				break;
			default:
				printf("illegal instruction swap: %s\n", bootCode[i]);
		}
		/*Make sure to reset visited to all zeroes after running!*/
		for(int y = 0; y < proglen-1; y++) visited[y] = false;
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
					//printf("<nop = %d>- a:%d - pc:%d\n", op,a,pc);
					break;
				/*jmp*/
				case (('j')+('m'<<1)+('p'<<2)):
					op = atoi(bootCode[pc] + 3);
					//printf("<jmp = %d>- a:%d - pc:%d\n", op,a,pc);
					pc += op - 1;
					break;
				/*acc*/
				case (('a')+('c'<<1)+('c'<<2)):
					op = atoi(bootCode[pc] + 3);
					//printf("<acc = %d>- a:%d - pc:%d\n", op,a,pc);
					a += op;
					break;
				default:
					printf("illegal opcode: %s\n", bootCode[pc]);
			}
			pc++;
			if(pc > proglen-1) goto success;
		}
		oHash = (bootCode[i][0]) + (bootCode[i][1] << 1) + (bootCode[i][2] << 2);
		switch(oHash)
		{
			/*nop*/
			case (('n')+('o'<<1)+('p'<<2)):
				printf("%d:%s -> ", i, bootCode[i]);
				bootCode[i][0] = 'j';
				bootCode[i][1] = 'm';
				bootCode[i][2] = 'p';
				printf("%s\n", bootCode[i]);
				break;
			/*jmp*/
			case (('j')+('m'<<1)+('p'<<2)):
				printf("%d:%s -> ", i, bootCode[i]);
				bootCode[i][0] = 'n';
				bootCode[i][1] = 'o';
				bootCode[i][2] = 'p';
				printf("%s\n", bootCode[i]);
				break;
			case (('a')+('c'<<1)+('c'<<2)):
				break;
			default:
				printf("illegal instruction swap: %s\n", bootCode[i]);
		}
	}
	printf("Nothing works!\n");
	goto end;
success:
	printf("Accumulator: %d\n", a);
end:
	free(input);
}
