#include"load.h"
#include<string.h>
#include<stdbool.h>
#define INCR(l, x, h) l <= x && x <= h
void day16_2(){
	char *input = loadinput("../input/day16-1.txt");
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
	/*Collect entries from tickets*/
	char *nearbyT = strstr(input, "nearby tickets:") + sizeof("nearby tickets:");
	int ticketCount = 0;
	int nearLen = 0;
	while(nearbyT[nearLen] != '\0')
	{
		if(nearbyT[nearLen] == '\n')
			ticketCount++;
		nearLen++;
	}
	printf("T:%d\nL:%d\n", ticketCount, nearLen);
	unsigned int ticketEntries[ticketCount][notecount];
	for(int y = 0; y < ticketCount; y++)
	{
		for(int x = 0; x < notecount; x++)
		{
			ticketEntries[y][x] = atoi(nearbyT);
			printf("%d,", ticketEntries[y][x]);
			if(x < (notecount-1))
				nearbyT = strchr(nearbyT, ',') + 1;
		}
		puts("");
		nearbyT = strchr(nearbyT, '\n') + 1;
		if(nearbyT == (void*)1)
			break;
	}
	/*Validate Tickets*/
	bool invalidTickets[ticketCount];
	int invalidTicketCount = 0;
	for(int y = 0; y < ticketCount; y++)
	{
		for(int x = 0; x < notecount; x++)
		{
			int i;
			for(i = 0; i < notecount; i++)
				if(INCR(ranges[i][0], ticketEntries[y][x], ranges[i][1])
						||
				   INCR(ranges[i][2], ticketEntries[y][x], ranges[i][3]))
				{
					i = -1;
					break;
				}
			if(i != -1){
				invalidTickets[y] = true;
				invalidTicketCount++;
				printf("%d/%d\r", invalidTicketCount, ticketCount);
				break;
			}else
				invalidTickets[y] = false;
		}
	}
	puts("");
	/*Do The Sieve*/
	bool notFound[notecount];
	bool entryKnown[notecount];
	unsigned int bottomMask[notecount];
	/*Initialize arrays*/
	for(int it = 0; it < notecount; it++)
	{
		entryKnown[it] = false;
		notFound[it] = true;
		bottomMask[it] = ~0;
	}
	while(1){
		for(int x = 0; x < notecount; x++)
		{
			if(entryKnown[x]) continue;
			for(int y = 0; y < ticketCount; y++)
			{
				if(invalidTickets[y]) continue;
				unsigned int curMask = 0;
				int i;
				/*Match entries on bit field*/
				for(i = 0; i < notecount; i++){
					if(!notFound[i]) continue;
					if(INCR(ranges[i][0], ticketEntries[y][x], ranges[i][1])
							||
					   INCR(ranges[i][2], ticketEntries[y][x], ranges[i][3]))
					{
						curMask |= 1 << i;
					}
				}
				/*Elimate non valid entries from bit field*/
				bottomMask[x] &= curMask;
			}
			int bitCount = 0;
			int bitPos = 0;
			/*Find Entry to Remove*/
			for(int it = 0; it < notecount; it++)
			{
				if((bottomMask[x] >> it) & 1)
				{
					bitCount++;
					bitPos = it;
				}
				if(bitCount > 1)
					break;
			}
			if(bitCount == 1){
				notFound[bitPos] = false;
				entryKnown[x] = true;
			}
		}
		int i;
		/*Check for remaining unkown entries*/
		for(i = 0; i < notecount; i++)
			if(notFound[i])
			{
				i = -1;
				break;
			}
		if(i != -1) break;
	}
	for(int i = 0; i < notecount; i++){
		int it;
		for(it = 0; it < 20; it++) 
			if((bottomMask[i] >> it) & 1) break;
		printf("Ticket Entry:%d = Note Entry:%d\n", i + 1, it + 1);
	}
	free(notes);
	free(input);
}
