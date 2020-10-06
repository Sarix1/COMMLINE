#include <stdio.h>
#include "strings.h"

int str_len;

// String copy function
void copystr(char* from, char* to)
{
	while ((*(to++) = *(from++)) != '\0');
}

// Find a substring within a string
int findstr(const char substr[], char string[])
{	
	int i;

	for (i = 0; string[i] != '\0'; i++)
	{
		//if (string[i] == '*')
		//	continue;
		
		if (substr[i] != string[i])
			return 0;
		
		else if (substr[i+1] == '\0')
			return i + 1;
	}
	
	return 0;
}

// Check if the strings match
int matchstr(const char string2[], char string1[])
{	
	int i;
	
	for (i = 0; string1[i] != '\0'; i++)
	{
		if (string2[i] != string1[i])
			return 0;
		
		else if (string2[i+1] == '\0')
		{
			if (string1[i+1] == '\0')
				return i + 1;
			else
				return 0;
		}
	}
	
	return 0;
}