#include"load.h"
#define mapwid 32
void day3_2(){
	char *input = loadinput("../input/day3-1.txt");
	int height = 0;
	int i = 0;
	while(input[++i] != '\0')
		if(input[i] == '\n')
			height++;
	int hits[5] = {0,0,0,0,0};
	const int xdif[5] = {1,3,5,7,1};
	const int ydif[5] = {1,1,1,1,2};
	long long cumProd = 1;
	for(i = 0; i < 5; i++)
	{
		int x = 0;
		int y = 0;
		while(y < height)
		{
			if(input[y*mapwid + x % (mapwid-1)] == '#')
				hits[i]++;
			y += ydif[i];
			x += xdif[i];
		}
		printf("%d\n",hits[i]);
		cumProd *= hits[i];
	}
	printf("Product %lld\n", cumProd);
	free(input);
}
