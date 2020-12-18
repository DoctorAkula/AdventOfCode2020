#include"load.h"
#include<string.h>
#define INCR(l, x, h) l <= x && x <= h
void day16_1(){
	char *input = loadinput("../input/day16-1.txt");
	char *nearbyT = strstr(input, "nearby tickets:") + sizeof("nearby tickets:");
	unsigned int fieldLen = (unsigned int)(strstr(input, "\n\n") - input);
	char *notes = calloc(fieldLen + 1, sizeof(char));
	strncpy(notes, input, fieldLen);
	notes[fieldLen] = '\0';
	int notecount = 1;
	for(int i = 0; i < fieldLen; i++)
		if(notes[i] == '\n') notecount++;
	printf("note count: %d\n", notecount);
	unsigned int ranges[notecount][4];
	char *dupnotes = notes;
	/*Collect ranges from notes*/
	for(int y = 0; y < notecount; y++)
	{
		dupnotes = strchr(dupnotes, ':') + 2;
		int x = 0;
		ranges[y][x] = atoi(dupnotes);
		printf("%d", ranges[y][x]);
		x++;
		dupnotes = strchr(dupnotes, '-') + 1;
		ranges[y][x] = atoi(dupnotes);
		printf("-%d ", ranges[y][x]);
		x++;

		dupnotes = strstr(dupnotes, " or ") + sizeof(" or");

		ranges[y][x] = atoi(dupnotes);
		printf("|| %d", ranges[y][x]);
		x++;
		dupnotes = strchr(dupnotes, '-') + 1;
		ranges[y][x] = atoi(dupnotes);
		printf("-%d\n", ranges[y][x]);
	}
	int cumSum = 0;
	/*Check tickets for invalid values*/
	while(1)
	{
		int ticketEntry = atoi(nearbyT);
		int i;
		for(i = 0; i < notecount; i++)
			if(INCR(ranges[i][0], ticketEntry, ranges[i][1])
					||
			   INCR(ranges[i][2], ticketEntry, ranges[i][3]))
			{
				i = -1;
				break;
			}
		if(i != -1) cumSum += ticketEntry;
		char *nextNL = strchr(nearbyT, '\n');
		char *nextCM = strchr(nearbyT, ',');
		if(!nextCM || !nextNL)
			break;
		else if(nextNL < nextCM)
			nearbyT = nextNL + 1;
		else
			nearbyT = nextCM + 1;
	}
	printf("Cumulative sum: %d\n", cumSum);
	free(notes);
	free(input);
}
