#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "strings.h"
#include "file.h"

// List all files in a directory to infolist
int listfiles(const char* currdir)
{
	DIR *dir;
	struct dirent *ent;
	
	if ((dir = opendir(currdir)) != NULL)
	{	
		while ((ent = readdir(dir)) != NULL)
			makeinfo(ent->d_name);
		closedir(dir);
	}
	else
	{
		perror("");
		return 0;
	}
	return 1;
}

// Check if a directory exists
int lookdir(const char* currdir, char* gotodir)
{	
	DIR *dir;
	struct dirent *ent;
	
	if ((dir = opendir(currdir)) != NULL)
	{	
		while ((ent = readdir(dir)) != NULL)
		{
			if (matchstr(ent->d_name, gotodir))
			{
				return 1;
				break;
			}
		}
		closedir(dir);
		return 0;
	}
	else
	{
		perror("");
		return 0;
	}
}

// Check if a drive exists
int lookdrive(const char* drive)
{	
	DIR *dir;
	
	if ((dir = opendir(drive)) != NULL)
		return 1;
	return 0;
}