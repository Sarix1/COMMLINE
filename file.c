#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "file.h"

#define BUFSIZE 1024

FILE* file1, * file2;
char filename1[MAXNAME], filename2[MAXNAME];
unsigned filecount;
infostruct* infolist;

// Open two files
int fileopen2(const char* fname1, const char* fname2)
{	
	int ret = 0;
	// Set 1st bit if file 1 fails
	if ((file1 = fopen(fname1, "r")) == NULL)
		ret |= 1;
	// Set 2nd bit if file 2 fails
	if ((file2 = fopen(fname2, "r")) == NULL)
		ret |= 2;
	return ret;
}

// Compare two files line by line, print differing lines
void filediff(FILE* fp1, FILE* fp2)
{
	unsigned line, endpos1, endpos2;
	char buf1[BUFSIZE], buf2[BUFSIZE];
	
	// Get the end positions of both files
	fseek(fp1, 0, SEEK_END);
	fseek(fp2, 0, SEEK_END);
	endpos1 = ftell(fp1);
	endpos2 = ftell(fp2);
	fseek(fp1, 0, SEEK_SET);
	fseek(fp2, 0, SEEK_SET);
	
	// Keep getting lines until either file has reached the end
	line = 0;
	while (ftell(fp1) != endpos1 && ftell(fp2) != endpos2)
	{	
		line++;
		fgets(buf1, BUFSIZE, fp1);
		fgets(buf2, BUFSIZE, fp2);
		
		// Compare the strings; if different, execute this block
		if (strcmp(buf1, buf2))
		{
			printf("\033[1;31mDifference(s) found on line %d\n\033[0;31m", line);
			printf("File 1: %s", buf1);
			// If the line in file 1 had no newline, add one to stdout
			if (*(buf1 + strlen(buf1) - 1) != '\n')
				putchar('\n');
			// Same as above for the line of file 2
			printf("File 2: %s", buf2);
			if (*(buf2 + strlen(buf2) - 1) != '\n')
				putchar('\n');
		}
	}
	
	fclose(fp1);
	fclose(fp2);
}

// Make a file information structure, appending it at the end of infolist
void makeinfo(char* fname)
{
	extern unsigned filecount;
	infostruct* newinfo;
	
	struct stat filestat;
	stat(fname, &filestat);
	
	/*  Allocate memory for a series of structs starting
	from the address of the struct pointer: infolist */
	infolist = (infostruct*) realloc(infolist, (++filecount * sizeof(*infolist)));
	
	/* Assign a pointer to the last slot of memory in the
	infolist chain, which should be free and undefined */
	newinfo = infolist + filecount - 1;
	
	/* Separate malloc() for string; because the string
	is of unknown length */
	newinfo->name = malloc(strlen(fname) + 1);
	strcpy(newinfo->name, fname);
	
	// Insert the other data obtained by stat()
	newinfo->date = filestat.st_ctime;
	newinfo->size = filestat.st_size;
}

int compare(infostruct* info1, infostruct* info2, char type)
{
	int i;
	
	if (type == 'd')
		i = info1->date - info2->date;
	else if (type == 's')
		i = info1->size - info2->size;
	else
		i = strcmp(info1->name, info2->name);
	
	return i;
}

// Sort files
void sortfiles(char sorttype)
{
	int i, j, gap;
	infostruct temp;
	
	// Sorting algorithm
	for (gap = filecount / 2; gap > 0; gap /= 2)
	{
		for (i = gap; i < filecount; i++)
		{
			temp = infolist[i];
			
			for (j = i; j >= gap && compare(&infolist[j - gap], &temp, sorttype) > 0; j -= gap)
			{
				infolist[i] = infolist[j - gap];
			}
			infolist[j] = temp;
		}	
	}
}

// Print file information in order
void printfiles(void)
{
	int i;
	infostruct* currinfo = infolist;
	
	printf("Filename                      \
Last Modified                 \
Size in Bytes\n");
	
	for (i = 0; i < filecount; i++, currinfo++)
	{
		printf("%-30s%-.24s      %lu\n",
		(currinfo->name), ctime((const time_t *)&(currinfo->date)), currinfo->size);
	}
}

// Free the memory allocated for the file information structures
void freefiles(void)
{
	int i;
	infostruct* currinfo = infolist;

	for (i = 0; i < filecount; i++, currinfo++)
		free(currinfo->name);
	
	free(infolist);
	infolist = NULL;
	filecount = 0;
}