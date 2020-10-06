#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsearch.h"

bin_t* rootbin;

// Count unique instances of words by storing them into a binary tree
int wordcount(char* infile)
{
	FILE* fp;
	unsigned end;
	char inword[MAXSTR];
	
	rootbin = NULL;
	
	if ((fp = fopen(infile, "r")) == NULL)
	{
		printf("File \"%s\" not found\n", infile);
		return 1;
	}
	else
	{
		fseek(fp, 0, SEEK_END);
		end = ftell(fp);
		fseek(fp, 0, SEEK_SET);
	}
	
	while (ftell(fp) != end)
	{
		fscanf(fp, "%s", inword);
		
		if (inword[0] == '\n')
			break;
		else
			insertbin(inword);
	}
	if (rootbin != NULL)
	{
		printf("Count\tWord\n");
		printtree(rootbin);
		deltree(rootbin);
	}
	else
	{
		printf("No words to count\n");
		return 1;
	}
	
	return 0;
}

// Allocate memory for a binary tree node and its string
bin_t* newbin(char* string)
{
	bin_t* new = malloc(sizeof(bin_t));
	if (new != NULL)
	{
		new->word = malloc(strlen(string) + 1);
		strcpy(new->word, string);
		
		if (new->word != NULL)
		{
			new->count = 1;
			new->left = NULL;
			new->right = NULL;
			return new;
		}
		else
		{
			free(new);
			return NULL;
		}
	}
	else
		return NULL;
}

// Insert a binary tree node into the tree structure
void insertbin(char* string)
{
	bin_t* currbin;
	int i;
	
	// Root
	if (rootbin == NULL)
		rootbin = newbin(string);
	
	else
	{
		currbin = rootbin;
		
		while (1)
		{
			i = strcmp(string, currbin->word);
			
			// Match
			if (i == 0)
			{
				currbin->count++;
				break;
			}
			// Lesser than
			else if (i < 0)
			{
				if (currbin->left == NULL)
				{
					currbin->left = newbin(string);
					break;
				}
				else
					currbin = currbin->left;
			}
			// Greater than
			else
			{
				if (currbin->right == NULL)
				{
					currbin->right = newbin(string);
					break;
				}
				else
					currbin = currbin->right;
			}
		}
	}
}

// Delete the binary tree down from this branch
void deltree(bin_t* target)
{
	free(target->word);
	if (target->left != NULL)
		deltree(target->left);
	if (target->right !=NULL)
		deltree(target->right);
	free(target);
}

// Print the binary tree down from this branch
void printtree(bin_t* target)
{
	printf("%-4u\t%s\n", target->count, target->word);
	if (target->left != NULL)
		printtree(target->left);
	if (target->right !=NULL)
		printtree(target->right);
}