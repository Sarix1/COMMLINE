#include <stdio.h>

#define MAXNAME 256

typedef struct
{
	char* name;
	unsigned long date;
	unsigned long size;
} infostruct;

extern FILE* file1;
extern FILE* file2;
extern char filename1[MAXNAME];
extern char filename2[MAXNAME];

extern unsigned filecount;
extern infostruct* infolist;

int fileopen2(const char*, const char*);
void fileinfo(const char*);
void filediff(FILE* fp1, FILE* fp2);

void makeinfo(char*);
void sortfiles(char);
void printfiles(void);
void freefiles(void);