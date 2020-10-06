#include <stdio.h>
#include <stdlib.h>
#include "input.h"

char instr[MAXIN];
int input(char*);

// Input from command line
int input(char* string)
{	
	char ch;
	char* strptr = string;

	while ((ch = getchar()))
	{
		if (ch == '\n' || ch == EOF)
		{
			*strptr = '\0';
			fflush(stdin);
			return 1;
		}
		else if (strptr - string >= MAXIN - 1)
		{
			*strptr = '\0';
			printf("Too many characters; maximum is %d\n", MAXIN - 1);
			fflush(stdin);
			return 0;
		}
		else
		{
			*strptr = ch;
			++strptr;
		}
	}
	
	fflush(stdin);
	return 0;
}