#include"load.h"
#include<string.h>
typedef enum{
	byr = 0x01,
	iyr = 0x02,
	eyr = 0x04,
	hgt = 0x08,
	hcl = 0x10,
	ecl = 0x20,
	pid = 0x40,
	cid = 0x80
}ppFlags;
void day4_1(){
	char *input = loadinput("../input/day4-1.txt");
	unsigned int ppCount = 0;
	char *substr = input;
	while(1)
	{
		substr = strstr(substr, "\n\n");
		if(substr){
			substr += 2;
			ppCount++;
		}else
			break;
	}
	unsigned char ppStat[ppCount];
	for(int i = 0; i < ppCount; i++)
		ppStat[i] = '\0';
	char temp[256];
	substr = input;
	int curPP = 0;
	while(1)
	{
		char *next = strstr(substr, "\n\n");
		if(next){
			unsigned long long ppLen = (unsigned long long)(next - substr);
			strncpy(temp, substr, ppLen);
			temp[ppLen] = '\0';
			if(strstr(temp, "byr:"))
				ppStat[curPP] |= byr;
			if(strstr(temp, "iyr:"))
				ppStat[curPP] |= iyr;
			if(strstr(temp, "eyr:"))
				ppStat[curPP] |= eyr;
			if(strstr(temp, "hgt:"))
				ppStat[curPP] |= hgt;
			if(strstr(temp, "hcl:"))
				ppStat[curPP] |= hcl;
			if(strstr(temp, "ecl:"))
				ppStat[curPP] |= ecl;
			if(strstr(temp, "pid:"))
				ppStat[curPP] |= pid;
			if(strstr(temp, "cid:"))
				ppStat[curPP] |= cid;
			//printf("Pass Port-<%s>-Stat=0x%X\n\n", temp, ppStat[curPP]);
			curPP++;
		}else
			break;
		substr = strstr(substr, "\n\n");
		substr += 2;
	}
	int validPP = 0;
	unsigned char poleMask = (byr | iyr | eyr | hgt | hcl | ecl | pid);
	unsigned char passMask = (byr | iyr | eyr | hgt | hcl | ecl | pid | cid);
	for(int i = 0; i < ppCount; i++)
		if((ppStat[i] == poleMask) || (ppStat[i] == passMask)) validPP++;
	printf("%d : %d\n", ppCount, validPP);
	free(input);
}
