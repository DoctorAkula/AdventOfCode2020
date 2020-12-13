#include<stdio.h>
#include<stdlib.h>

#include"includes.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "arguments <day> <part>\n");
		exit(-1);
	}
	int day = atoi(argv[1]);
	int part = atoi(argv[2]);
	switch(day)
	{
		case 1:
			switch(part){
				case 1:
				day1_1();
				break;
				case 2:
				day1_2();
				break;
			}
			break;
		case 2:
			switch(part){
				case 1:
				day2_1();
				break;
				case 2:
				day2_2();
				break;
			}
			break;
		case 3:
			switch(part){
				case 1:
				day3_1();
				break;
				case 2:
				day3_2();
				break;
			}
			break;
		case 4:
			switch(part){
				case 1:
				day4_1();
				break;
				case 2:
				day4_2();
				break;
			}
			break;
		case 5:
			switch(part){
				case 1:
				day5_1();
				break;
				case 2:
				day5_2();
				break;
			}
			break;
		case 6:
			switch(part){
				case 1:
				day6_1();
				break;
				case 2:
				day6_2();
				break;
			}
			break;
		case 7:
			switch(part){
				case 1:
				day7_1();
				break;
				case 2:
				day7_2();
				break;
			}
			break;
		case 8:
			switch(part){
				case 1:
				day8_1();
				break;
				case 2:
				day8_2();
				break;
			}
			break;
		case 9:
			switch(part){
				case 1:
				day9_1();
				break;
				case 2:
				day9_2();
				break;
			}
			break;
		case 10:
			switch(part){
				case 1:
				day10_1();
				break;
				case 2:
				day10_2();
				break;
			}
			break;
		case 11:
			switch(part){
				case 1:
				day11_1();
				break;
				case 2:
				day11_2();
				break;
			}
			break;
		case 12:
			switch(part){
				case 1:
				day12_1();
				break;
				case 2:
				day12_2();
				break;
			}
			break;
		case 13:
			switch(part){
				case 1:
				day13_1();
				break;
				case 2:
				day13_2();
				break;
			}
			break;
		case 14:
			switch(part){
				case 1:
				day14_1();
				break;
				case 2:
				day14_2();
				break;
			}
			break;
		case 15:
			switch(part){
				case 1:
				day15_1();
				break;
				case 2:
				day15_2();
				break;
			}
			break;
		case 16:
			switch(part){
				case 1:
				day16_1();
				break;
				case 2:
				day16_2();
				break;
			}
			break;
		case 17:
			switch(part){
				case 1:
				day17_1();
				break;
				case 2:
				day17_2();
				break;
			}
			break;
		case 18:
			switch(part){
				case 1:
				day18_1();
				break;
				case 2:
				day18_2();
				break;
			}
			break;
		case 19:
			switch(part){
				case 1:
				day19_1();
				break;
				case 2:
				day19_2();
				break;
			}
			break;
		case 20:
			switch(part){
				case 1:
				day20_1();
				break;
				case 2:
				day20_2();
				break;
			}
			break;
		case 21:
			switch(part){
				case 1:
				day21_1();
				break;
				case 2:
				day21_2();
				break;
			}
			break;
		case 22:
			switch(part){
				case 1:
				day22_1();
				break;
				case 2:
				day22_2();
				break;
			}
			break;
		case 23:
			switch(part){
				case 1:
				day23_1();
				break;
				case 2:
				day23_2();
				break;
			}
			break;
		case 24:
			switch(part){
				case 1:
				day24_1();
				break;
				case 2:
				day24_2();
				break;
			}
			break;
		case 25:
			switch(part){
				case 1:
				day25_1();
				break;
				case 2:
				day25_2();
				break;
			}
			break;
		default:
			printf("You've don-goofed\n");
	}
}
