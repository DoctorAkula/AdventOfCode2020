#include"load.h"
void day2_1(){
	char *input = loadinput("../input/day2-1.txt");
	char *dupin = input;
	int ValidPSW = 0;
	int InvalidPSW = 0;
	while((*dupin) != '\0')
	{
		int lower = atoi(dupin);
		while(*dupin++ != '-');
		int upper = atoi(dupin);
		while(*dupin++ != ' ');
		char letter = *dupin;
		dupin += 2;
		int count = 0;
		while(*dupin++ != '\n')
			if(*dupin == letter) count++;
		if((count >= lower) && (count <= upper))
			ValidPSW++;
		else
			InvalidPSW++;
	}
	printf("Valid: %d\nInvalid: %d\n",
			ValidPSW,
			InvalidPSW);
	free(input);
}
