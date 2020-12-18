#include"load.h"
#include<string.h>
typedef struct binTree{
	unsigned long long val; /*The iteration it was spoken on*/
	unsigned long long key; /*The spoken number*/
	struct binTree *hNext;
	struct binTree *lNext;
}binTree;
static binTree *searchAppend(binTree *entry, unsigned long long key, unsigned long long val)
{
	if(entry){
		if(entry->key == key){
			return entry;
		}else if(entry->key > key){
			if(!entry->lNext){
				entry->lNext = searchAppend(entry->lNext, key, val);
				return entry->lNext;
			}else
				return searchAppend(entry->lNext, key, val);
		}else{
			if(!entry->hNext){
				entry->hNext = searchAppend(entry->hNext, key, val);
				return entry->hNext;
			}else
				return searchAppend(entry->hNext, key, val);
		}
	}else{
		entry = calloc(1, sizeof(binTree));
		entry->val = val;
		entry->key = key;
		return entry;
	}
}
static void freeBT(binTree *entry)
{
	if(entry->lNext) freeBT(entry->lNext);
	if(entry->hNext) freeBT(entry->hNext);
	free(entry);
}
void day15_1(){
	char *input = loadinput("../input/day15-1.txt");
	char *dupin = input;
	int listSize = 0;
	binTree *orgmem = NULL;
	binTree *mem = NULL;
	do{
		mem = searchAppend(orgmem, atoi(dupin), listSize);
		if(!orgmem) orgmem = mem;
		listSize++;
	}while((dupin = strchr(dupin, ',') + 1) != (void*)1);

	int curNum = 0;
	for(int i = listSize; i < 2020; i++)
	{
		printf("<%d>\n", curNum);
		mem = searchAppend(orgmem, curNum, i);
		if(mem->val == i){
			curNum = 0;
		}else{
			curNum = i - mem->val;
			mem->val = i;
		}
	}
	freeBT(orgmem);
	free(input);
}
