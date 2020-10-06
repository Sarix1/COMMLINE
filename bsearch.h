#define MAXSTR 256

#ifndef _BSEARCH_H_
#define _BSEARCH_H_

typedef struct bin
{
	char* word;
	unsigned count;
	struct bin_t* left;
	struct bin_t* right;
} bin_t;

int wordcount(char*);
bin_t* newbin(char*);
void insertbin(char*);
void deltree(bin_t*);
void printtree(bin_t*);

#endif