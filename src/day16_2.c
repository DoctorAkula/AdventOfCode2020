#include"load.h"
#include<string.h>
#include<stdbool.h>
#define INCR(l, x, h) l <= x && x <= h
void day16_2(){
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
	/*Print Valid Tickets*/
	bool invalid = false;
	char *wholeTicket = nearbyT;
	int validTicketCount = 0;
	char *validTickets[3];
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
		if(i != -1) invalid = true;
		char *nextNL = strchr(nearbyT, '\n');
		char *nextCM = strchr(nearbyT, ',');
		if(!nextCM || !nextNL)
			break;
		else if(nextNL < nextCM)
		{
			*nextNL = '\0';
			if(!invalid){
				printf("<%s>\n", wholeTicket);
				validTickets[validTicketCount++] = wholeTicket;
			}
			nearbyT = nextNL + 1;
			wholeTicket = nearbyT;
		}
		else
			nearbyT = nextCM + 1;
	}
	while(1){
		unsigned int rangeMask = ~0;
		for(int x = 0; x < validTicketCount; x++)
		{
			unsigned int thisMask = 0;
			int ticketEntry = atoi(validTickets[x]);
			for(int i = 0; i < 6; i++)
				if(INCR(ranges[i][0], ticketEntry, ranges[i][1])
						||
				   INCR(ranges[i][2], ticketEntry, ranges[i][3]))
				{
					thisMask |= 1 << i;
				}
			rangeMask &= thisMask;
			validTickets[x] = strchr(validTickets[x], ',') + 1;
			if(validTickets[x] == (void*)1) goto ende;
		}
		printf(" %X ", rangeMask);
	}
ende:
	puts("");
	free(notes);
	free(input);
}
