#include "set.h"

void read_numbers_to_set_name()
{
	printf("read_numbers_to_set_name");
}

void print_set()
{
	printf("print_set");
}

void union_set()
{
	printf("union_set");
}

void intersection_set()
{
	printf("intersection_set");
}

void substract_from_set()
{
	printf("substract_from_set");
}

void symetric_difference_set()
{
	printf("symetric_difference_set");
}

void stop()
{
	printf("symetric_difference_set");
}

void help()
{
	int i;

	printf("%sHelp%s\n", BAR, BAR);
	for ( i = 0 ; cmds[i].command_function != NULL ; i++ )
		printf("Command: %s\nDescription: %s\nUsage: %s\n\n", cmds[i].command_name, cmds[i].description, cmds[i].usage);
}
