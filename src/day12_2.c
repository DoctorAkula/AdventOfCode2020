#include"load.h"
#include<string.h>
void day12_2(){
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
	int xShip = 0;
	int yShip = 0;
	int xWay = 10;
	int yWay = 1;
	for(int i = 0; i < navCount; i++)
	{
		int mag;
		switch(navCode[i][0]){
			case 'N':
				yWay += atoi(navCode[i]+1);
				break;
			case 'E':
				xWay += atoi(navCode[i]+1);
				break;
			case 'S':
				yWay -= atoi(navCode[i]+1);
				break;
			case 'W':
				xWay -= atoi(navCode[i]+1);
				break;
			case 'L':
				switch(atoi(navCode[i]+1)){
					case 90:
						xWay += yWay;
						yWay = xWay - yWay;
						xWay -= yWay;
						xWay = -xWay;
						break;
					case 180:
						xWay = -xWay;
						yWay = -yWay;
						break;
					case 270:
						xWay += yWay;
						yWay = xWay - yWay;
						xWay -= yWay;
						yWay = -yWay;
						break;
				}
				break;
			case 'R':
				switch(atoi(navCode[i]+1)){
					case 90:
						xWay += yWay;
						yWay = xWay - yWay;
						xWay -= yWay;
						yWay = -yWay;
						break;
					case 180:
						xWay = -xWay;
						yWay = -yWay;
						break;
					case 270:
						xWay += yWay;
						yWay = xWay - yWay;
						xWay -= yWay;
						xWay = -xWay;
						break;
				}
				break;
			case 'F':
				mag = atoi(navCode[i]+1);
				xShip += (xWay * mag);
				yShip += (yWay * mag);
				break;
		}
	}
	printf("x loc: %d | y loc: %d\n", xShip, yShip);
	free(input);
}
