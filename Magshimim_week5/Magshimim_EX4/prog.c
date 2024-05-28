/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{

	char help[] = "help";
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], help) == 0)
		{
			printf("Breathe :) everything is OK ");
			break;
		}
		else
		{
			printf(":) ");
		}
	}

	getchar();
	return 0;
}