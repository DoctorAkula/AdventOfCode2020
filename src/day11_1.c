#include"load.h"
#include<string.h>
#include<stdbool.h>
#define LIN(x, y, w) y * w + x
#define INR(l, x, h) l <= x && x < h
static const char xoffs[8] = {-1, 0, 1, 1, 1, 0,-1,-1};
static const char yoffs[8] = { 1, 1, 1, 0,-1,-1,-1, 0};
void day11_1(){
	char *input = loadinput("../input/day11-1.txt");
	int inLen = strlen(input);
	char *dupin = calloc(inLen+1, sizeof(char));
	strncpy(dupin, input, inLen);
	int width = 0;
	while(input[width++] != '\n');
	char *sep = calloc(width, sizeof(char));
	memset(sep, '-', width);
	int height = inLen / width;
	char *cur[2] = {input, dupin};
	bool notChanged = false;
	bool swap = false;
	while(!notChanged)
	{
		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++)
			{
				int io = LIN(x, y, width);
				if(cur[swap][io] == '\n') continue;
				int count = 0;
				for(int i = 0; i < 8; i++)
				{
					int xoff = x+xoffs[i];
					int yoff = y+yoffs[i];
					if(INR(0,xoff,width) && INR(0,yoff,height))
					{
						int in = LIN(xoff, yoff, width);
						if(cur[swap][in] == '#') count++;
					}
				}
				switch(cur[swap][io])
				{
					case '#':
						if(count >= 4)
							cur[!swap][io] = 'L';
						else
							cur[!swap][io] = '#';
						break;
					case 'L':
						if(count == 0)
							cur[!swap][io] = '#';
						else
							cur[!swap][io] = 'L';
						break;
				}
			}
		notChanged = true;
		for(int i = 0; i < inLen; i++)
			if(cur[swap][i] != cur[!swap][i])
			{
				notChanged = false;
				break;
			}
		swap = !swap;
	}
	int count = 0;
	for(int i = 0; i < inLen; i++)
		if(cur[!swap][i] == '#') count++;
	printf("%s%s\n%s\n\ncount: %d\n", cur[swap], sep, cur[!swap], count);
	free(dupin);
	free(input);
}
