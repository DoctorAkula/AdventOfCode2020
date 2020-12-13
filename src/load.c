#include"load.h"
char *loadinput(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if(!input)
	{
		perror("unable to open file");
		exit(-1);
	}
	fseek(input, 0, SEEK_END);
	long length = ftell(input);
	char *buffer = (char *)malloc(length * sizeof(char));
	fseek(input, 0, SEEK_SET);
	for(int i = 0; i < length; i++)
		buffer[i] = fgetc(input);
	fclose(input);
	return buffer;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
