#include <stdio.h>
#include "path.h"
#include "input.h"
#include "commands.h"
#include "file.h"

int main()
{
	// Initialization procedures
	initpath();
	infolist = NULL;
	filecount = 0;

	printf("\033[0;36mWelcome to the generic command line utility!\n\n");
	command("help");
	putchar('\n');

	// Main program loop
	while (1)
	{
		int i = 0;
		// Update colour
		printf("\033[0;36m");
		// Show path
		print_nodes(root_node, '\\');

		if ((i = input(instr)))
			command(instr);
		else
			printf("Input failure\n");

		printf("\n");
	}
	return 0;
}
