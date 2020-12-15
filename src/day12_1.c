#include"load.h"
#include<string.h>
void day12_1(){
	char *input = loadinput("../input/day12-1.txt");
	int navCount = 0;
	char *dupin = input;
	while(*dupin++ != '\0') if(*dupin == '\n') navCount++;
	char **navCode = calloc(navCount, sizeof(char*));
	dupin = input;
	for(int i = 0; i < navCount; i++)
	{
		int lineLen = 0;
		while(*dupin++ != '\n') lineLen++;
		navCode[i] = calloc(lineLen+1, sizeof(char));
		strncpy(navCode[i], dupin-lineLen-1, lineLen);
		printf("%d: <%s>\n",lineLen, navCode[i]);
	}
	int xCoord = 0;
	int yCoord = 0;
	int rot = 90;
	for(int i = 0; i < navCount; i++)
	{
		switch(navCode[i][0]){
			case 'N':
				yCoord += atoi(navCode[i]+1);
				break;
			case 'E':
				xCoord += atoi(navCode[i]+1);
				break;
			case 'S':
				yCoord -= atoi(navCode[i]+1);
				break;
			case 'W':
				xCoord -= atoi(navCode[i]+1);
				break;
			case 'L':
				rot -= atoi(navCode[i]+1);
				if(rot < 0)
					rot = 360 + rot;
				break;
			case 'R':
				rot += atoi(navCode[i]+1);
				rot %= 360;
				break;
			case 'F':
				switch(rot){
					case 0:
						yCoord += atoi(navCode[i]+1);
						break;
					case 90:
						xCoord += atoi(navCode[i]+1);
						break;
					case 180:
						yCoord -= atoi(navCode[i]+1);
						break;
					case 270:
						xCoord -= atoi(navCode[i]+1);
						break;
					default:
						printf("bad rot: %d\n", rot);
				}
				break;
		}
	}
	printf("x loc: %d | y loc: %d | rot: %d\n", xCoord, yCoord, rot);
	free(input);
}
