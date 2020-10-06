#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "strings.h"
#include "input.h"
#include "path.h"
#include "file.h"
#include "dir.h"
#include "bsearch.h"

char* cmds[LAST+1];
char* cmddesc[LAST+1];
char strarg[MAXPATH] = "";
char drive[2];

void command(char* instr)
{	
	// Update the path
	buildpath(strarg);
	// Update colour
	printf("\033[1;34m");
	
	/* Find a command from the input string,
	then execute the corresponding function */
	switch(findcmd(instr))
	{
	case GOTODRIVE:
		printf("Changing drive\n");
		drive[0] = instr[0];
		drive[1] = ':';
		cmd_gotodrive(drive);
		break;
	case CURRDIR:
		cmd_currdir(instr[1]);
		break;
	case GOTODIR:
		cmd_gotodir(instr);
		break;
	case PREVDIR:
		cmd_prevdir();
		break;
	case COMPARE:
		cmd_compare(instr);
		break;
	case COUNT:
		cmd_count(instr+6);
		break;
	case HELP:
		cmd_help();
		break;
	case EXIT:
		cmd_exit();
		break;
	case BLAH:
		cmd_blah();
		break;
	default:
		printf("Invalid command - type \"help\" to list available commands\n");
		break;
	}
}

// Find a command string from the given input
int findcmd(char* string)
{	
	int i;

	// Command strings are listed here
	cmds[GOTODRIVE]	= "*:";
	cmds[CURRDIR]	= ".";
	cmds[GOTODIR]	= "cd ";
	cmds[PREVDIR]	= "cd..";
	cmds[COMPARE]	= "comp";
	cmds[COUNT]		= "count";
	cmds[HELP]		= "help";
	cmds[EXIT]		= "exit";
	cmds[BLAH]		= "blah";
	cmds[LAST]		= "";
	
	// Command descriptions   
	cmddesc[GOTODRIVE]	= "Change drive; <drive>:";
	cmddesc[CURRDIR]	= "List current directory contents;\n\t.a alphabetically, .s by size, .d by date";
	cmddesc[GOTODIR]	= "Change directory; cd <dirname>";
	cmddesc[PREVDIR]	= "Return to the previous directory";
	cmddesc[COMPARE]	= "Compare two files; comp <file1> <file2>";
	cmddesc[COUNT]		= "Count instances of unique words; count <file>";
	cmddesc[HELP]		= "Display this information";
	cmddesc[EXIT]		= "Exit the program";
	cmddesc[BLAH]		= "$Secret function";
	cmddesc[LAST]		= "";

	if (string[1] == ':' && string[0] >= 'A' && string[0] <= 'z')
	{
		if (string[0] >= 'a')
			string[0] -= ('a' - 'A');
		return GOTODRIVE;
	}
	
	// Compare the input string with each command string until a match is found
	for (i = 1; i < LAST; i++)
	{
		if ((str_len = findstr(cmds[i], string)))
			return i;
	}
	
	return -1;
}

// Change drive command function
void cmd_gotodrive(char* drive)
{
/////////////
	
	if ((lookdrive(drive)))
	{
		delpath(root_node);
		makenode(drive);
	}
	else
		printf("No such drive\n");
}

// List the contents of the current directory
void cmd_currdir(char sorttype)
{
	listfiles(strarg);
	if (sorttype)
		sortfiles(sorttype);
	printfiles();
	freefiles();
}

// Change directory command function
void cmd_gotodir(char* gotodir)
{
	gotodir += str_len;
	
	if ((lookdir(strarg, gotodir)))
		makenode(gotodir);
	else
		printf("No such directory\n");
}

// Previous directory command function
void cmd_prevdir(void)
{
	delnode();
}

// Compare strings
void cmd_compare(const char* instr)
{
	int i;
	extern char filename1[];
	extern char filename2[];
	
	sscanf(instr, "%*s %s %s", filename1, filename2);
	
	i = fileopen2(filename1, filename2);
	
	if (!i)
		filediff(file1, file2);
	else
	{
		printf("Unable to compare files\n");
		if (i & 1)
			printf("Failed to load \"%s\"\n", filename1);
		if (i & 2)
			printf("Failed to load \"%s\"\n", filename2);
	}
}

// Count words
void cmd_count(char* infile)
{
	if (wordcount(infile))
		printf("Word counting operation failed\n");
}

// Display commands
void cmd_help(void)
{
	int i;
	
	printf("\033[1;31mCommands:\n");
	for (i = 0; i < LAST; i++)
	{
		if (cmddesc[i][0] != '$')
			printf("\033[1;34m%s\t\033[0;35m%s\n", cmds[i], cmddesc[i]);
	}
}

// Exit
void cmd_exit(void)
{
	printf("Bye!\n");
	exit(0);
}

// Blah!
void cmd_blah(void)
{
printf("\a\n\
  (\\_/)\n\
  (d b)\n\
 =/\\o/\\=\n\
 ( )\"( )\n\
 /\\| |/\\   )\n\
(  \"_\"  ) /\n\
 \\ / \\ /\\(_\n\
  \\| |/  \\_)\n\
  \"   \"\n");
}