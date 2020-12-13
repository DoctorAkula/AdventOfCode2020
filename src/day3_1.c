#include"load.h"
#define mapwid 32
void day3_1(){
	char *input = loadinput("../input/day3-1.txt");
	int height = 0;
	int i = 0;
	while(input[++i] != '\0')
		if(input[i] == '\n')
			height++;
	int x = 0;
	int y = 0;
	int hits = 0;
	while(y < height)
	{
		if(input[y*mapwid + x % (mapwid-1)] == '#')
			hits++;
		y++;
		x += 3;
	}
	printf("%d\n", hits);
	free(input);
}
