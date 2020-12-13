#include"load.h"
#include<stdbool.h>
void day2_2(){
	char *input = loadinput("../input/day2-1.txt");
	char *dupin = input;
	int ValidPSW = 0;
	int InvalidPSW = 0;
	while(*dupin != '\0')
	{
		int first = atoi(dupin);
		while(*dupin++ != '-');
		int second = atoi(dupin);
		while(*dupin++ != ' ');
		char letter = *dupin;
		dupin += 2;
		int count = 0;
		bool firstValid = false;
		bool secondValid = false;
		while(*dupin++ != '\n')
		{
			count++;
			if((count == first) && (*dupin == letter))
				firstValid = true;
			if((count == second) && (*dupin == letter))
				secondValid = true;
		}
		if(firstValid ^ secondValid)
			ValidPSW++;
		else
			InvalidPSW++;
	}
	printf("Valid: %d\nInvalid: %d\n",
			ValidPSW,
			InvalidPSW);
	free(input);
}
