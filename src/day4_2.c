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

int checkLenAndChar(char *str, int strLen, const char *expectedChars)
{
	unsigned char isValid = 1;
	int expLen = strlen(expectedChars);
	for(int s = 0; s < strLen; s++)
	{
		int i;
		for(i = 0; i < expLen; i++)
			if(str[s] == expectedChars[i])
			{
				i = -1;
				break;
			}
		if(i != -1)
			return 0;
	}
	return 1;
}

int eyeColors(char *color)
{
	const char *colors[] = 
	{
		"amb",
		"blu",
		"brn",
		"gry",
		"grn",
		"hzl",
		"oth"
	};
	for(int i = 0; i < (sizeof(colors) / 8); i++)
		if(strstr(color, colors[i]))
			return 1;
	return 0;
}

char *passportEntry(char *entryStart)
{
	if(!entryStart) return NULL;
	char *nextNewline = strchr(entryStart, '\n');
	if(!nextNewline) nextNewline =(char *)(~0);
	char *nextSpace = strchr(entryStart, ' ');
	if(!nextSpace) nextSpace =(char *)(~0);
	unsigned long long len;
	if(nextSpace < nextNewline){
		len = (unsigned long long)(nextSpace - entryStart);
	}else{
		len = (unsigned long long)(nextNewline - entryStart);
	}
	if((nextNewline ==(char *)(~0)) && (nextSpace ==(char *)(~0))) return NULL;
	len -= 4;
	char *entry = calloc(len + 1, 1);
	strncpy(entry, entryStart + 4, len);
	return entry;
}

void day4_2()
{
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
			temp[ppLen] = ' ';
			temp[ppLen+1] = '\0';
			char *entry;
			if((entry = passportEntry(strstr(temp, "byr:")))){
				int len = strlen(entry);
				int year = atoi(entry);
				if((len == 4) && (1920 <= year) && (year <= 2002))
					ppStat[curPP] |= byr;
			}
			free(entry);
			if((entry = passportEntry(strstr(temp, "iyr:")))){
				int len = strlen(entry);
				int year = atoi(entry);
				if((len == 4) && (2010 <= year) && (year <= 2020))
					ppStat[curPP] |= iyr;
			}
			free(entry);
			if((entry = passportEntry(strstr(temp, "eyr:")))){
				int len = strlen(entry);
				int year = atoi(entry);
				if((len == 4) && (2020 <= year) && (year <= 2030))
					ppStat[curPP] |= eyr;
			}
			free(entry);
			if((entry = passportEntry(strstr(temp, "hgt:")))){
				int height = atoi(entry);
				if(strstr(entry, "cm"))
				{
					if((150 <= height) && (height <= 193))
						ppStat[curPP] |= hgt;
				}else if(strstr(entry, "in")){
					if((59 <= height) && (height <= 76))
						ppStat[curPP] |= hgt;
				}
			}
			free(entry);
			if((entry = passportEntry(strstr(temp, "hcl:")))){
				if(strlen(entry) == 7)
					if(entry[0] == '#')
						if(checkLenAndChar(entry+1, 6, "abcdef0123456789"))
							ppStat[curPP] |= hcl;
			}
			free(entry);
			if((entry = passportEntry(strstr(temp, "ecl:")))){
				if(eyeColors(entry))
					ppStat[curPP] |= ecl;
			}
			free(entry);
			if((entry = passportEntry(strstr(temp, "pid:")))){
				if(strlen(entry) == 9)
					if(checkLenAndChar(entry, 9, "0123456789"))
						ppStat[curPP] |= pid;
			}
			free(entry);
			if((entry = passportEntry(strstr(temp, "cid:")))){
				ppStat[curPP] |= cid;
			}
			free(entry);
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
	for(int i = 0; i < ppCount; i++){
		if((ppStat[i] == poleMask) || (ppStat[i] == passMask))	validPP++;
	}
	printf("%d : %d\n", ppCount, validPP);
	free(input);
}
