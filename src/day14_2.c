#include"load.h"
#include<string.h>
#define MASKSIZE 36
typedef struct memStruct{
	unsigned long long addr;
	unsigned long long val;
	struct memStruct *next;
}memStruct;
static memStruct *searchAppend(memStruct *mem, unsigned long long addr)
{
	if(mem){
		if(mem->addr == addr){
			return mem;
		}else{
			if(!mem->next){
				mem->next = searchAppend(mem->next, addr);
				return mem->next;
			}else
				return searchAppend(mem->next, addr);
		}
	}else{
		mem = calloc(1, sizeof(memStruct));
		mem->addr = addr;
		return mem;
	}
}
static void freeLL(memStruct *mem)
{
	if(mem->next) freeLL(mem->next);
	free(mem);
}
unsigned long long genCombinations(int combNum, int xcount, unsigned char *xOffsets, unsigned long long addr)
{
	for(int i = 0; i < xcount; i++)
	{
		int temp = (combNum >> i) & 1;
		switch(temp){
			case 0:
				addr &= (unsigned long long)~(1 << xOffsets[i]);
				break;
			case 1:
				addr |= (unsigned long long)1 << xOffsets[i];
				break;
		}
	}
	return addr;
}
void day14_2(){
	char *input = loadinput("../input/day14-1.txt");
	char *dupin = input;
	memStruct *mem = NULL;
	memStruct *orgmem = NULL;
	int xcount = 0;
	unsigned long long Onmask;
	unsigned char xOffsets[MASKSIZE];
	do{
		int hash = dupin[0] + (dupin[1] << 1) + (dupin[2] << 2);
		unsigned long long addr;
		switch(hash){
			case ('m' + ('a' << 1) + ('s' << 2)):
				xcount = 0;
				Onmask = 0;
				for(int i = 0; i < MASKSIZE; i++)
					switch(dupin[(MASKSIZE + 6) - i]){
						case 'X':
							xOffsets[xcount] = i;
							xcount++;
							break;
						case '1':
							Onmask |= (unsigned long long)1 << i;
							break;
					}
				break;
			case ('m' + ('e' << 1) + ('m' << 2)):
				addr = strtoull(dupin + 4, NULL, 10) | Onmask;
				dupin = strchr(dupin, '=') + 1;
				unsigned long long val = atoi(dupin);
				unsigned long long combs = (unsigned long long)1 << xcount;
				printf("%llu\n", combs);
				for(int i = 0; i < combs; i++){
					unsigned long long mod = genCombinations(i, xcount, xOffsets, addr);
					mem = searchAppend(orgmem, mod);
					mem->val = val;
					if(!orgmem) orgmem = mem;
				}
				break;
		}
	}while( (dupin = strchr(dupin, '\n') + 1) != (void*)1);
	unsigned long long cumSum = 0;
	mem = orgmem;
	while(mem){
		printf("mem[0x%llX] = %llu\n", mem->addr, mem->val);
		cumSum += mem->val;
		mem = mem->next;
	}
	printf("cumulative sum: %llu\n", cumSum);
	freeLL(orgmem);
	free(input);
}
