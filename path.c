#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"
#include "strings.h"

#ifdef WINDOWS
#include <direct.h>
#define getcurrdir _getcwd
#else
#include <direct.h>
#define getcurrdir getcwd
//#include <unistd.h>
//#define getcurrdir getcwd
#endif

node_t* root_node;
node_t* curr_node;
node_t* prev_node;
node_t* temp_node;

// Allocate memory for and create new node
void makenode(char* name_str)
{
	extern node_t* root_node, * curr_node, * prev_node, * temp_node;
	char* temp_name, * temp_ptr;
	
	// Determine length of string argument
	int name_len = 0;
	for (temp_ptr = name_str; *(temp_ptr) != '\0'; temp_ptr++)
		name_len++;
	
	// Actual memory allocation via malloc
	temp_node = malloc(sizeof(node_t));
	if (temp_node == NULL) printf("Failed to allocate %d bytes\n", sizeof(node_t));
	temp_name = malloc(sizeof(char) * (name_len + 1));
	if (temp_name == NULL) printf("Failed to allocate %d bytes\n", sizeof(char) * (name_len + 1));
	
	// Copy the string argument into the allocated memory
	temp_node->name = temp_name;
	copystr(name_str, temp_name);
	
	// If the root is empty, then this is the first node
	if (root_node == NULL)
	{
		curr_node = prev_node = root_node = temp_node;
		curr_node->next = NULL;
	}
	// Otherwise move to the next node
	else
	{
		prev_node = curr_node;
		curr_node = curr_node->next = temp_node;
		curr_node->next = NULL;
	}
}

// Delete node
void delnode(void)
{
	if (curr_node != NULL)
	{	
		curr_node = root_node;
		while (curr_node->next != NULL)
		{
			prev_node = curr_node;
			curr_node = curr_node->next;
		}
		if (curr_node != root_node)
			free(curr_node->name);
		free(curr_node->next);
		
		curr_node = prev_node;
		curr_node->next = NULL;
	}
}

// Free node
void freenode(node_t* node)
{
	free(node->name);
	free(node);
}

// Print out all the nodes, c is a delimiter
void print_nodes(node_t* node, char c)
{
	while (node != NULL)
	{
		printf("%s%c", node->name, c);
		node = node->next;
	}
	//putchar('>');
}

// Initialize the current executable path
void initpath(void)
{
	char path[FILENAME_MAX];
	char* pathptr, * pathstart;

	// Set the first directory node to NULL
	root_node = NULL;
	
	// Get current working directory
	getcurrdir(path, FILENAME_MAX);
	pathptr = pathstart = path;

	/* Loop through the path string, replace \ with \0,
	make a path node from the string up until that point,
	and advance the start pointer to after that point */
	while (*(pathptr++))
	{
		if (*pathptr == '\\')
		{
			*(pathptr++) = '\0';
			makenode(pathstart);
			pathstart = pathptr;
		}
	}
	
	/* If the last character of the path wasn't a backslash, then
	the last directory was missed by the loop above; add it here. */
	if (*(pathptr-2) != '\\')
		makenode(pathstart);
}

// Build current directory path into a string
void buildpath(char* strarg)
{
	strarg[0] = '\0';
	curr_node = root_node;
	
	while (1)
	{
		strcat(strarg, curr_node->name);
		strcat(strarg, "\\");
		
		if (curr_node->next == NULL)
			break;
		else
			curr_node = curr_node->next;
	}
	
	strcat(strarg, "\0");
	chdir(strarg);
}

// A recursive function to delete all nodes
void delpath(node_t* node)
{
	if (node != NULL)
	{
		delpath(node->next);
		freenode(node);
	}
}