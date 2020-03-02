#include "assembler.h"


/* print the given string to STDOUT */
void _message(char prefix[], char str[])
{
	fprintf(stdout, "%s%s\n", prefix, str);
}

/* print the given string as WARNING to STDOUT */
void _WARNING(int num_of_args, ... ) 
{
	va_list valist;
	char buffer[MAX_LINE_LENGTH] = {0};
	int i;
	
	va_start(valist, num_of_args);

	for (i = 0; i < num_of_args; i++)
	{
		strcat(buffer, va_arg(valist, char *));
		strcat(buffer, " ");
	}
	va_end(valist);

	_message("WARNING - ", buffer);
}

/* print the given string as DEBUG to STDOUT */
void _DEBUG(int num_of_args, ... )
{
	va_list valist;
	char buffer[MAX_LINE_LENGTH] = {0};
	int i;
	
	va_start(valist, num_of_args);

	for (i = 0; i < num_of_args; i++)
	{
		strcat(buffer, va_arg(valist, char *));
		strcat(buffer, " ");
	}
	va_end(valist);

	_message("DEBUG - ", buffer);
}

/* print the given string as ERROR to STDOUT */
void _ERROR(int num_of_args, ... )
{
	va_list valist;
	char buffer[MAX_LINE_LENGTH] = {0};
	int i;
	
	va_start(valist, num_of_args);

	for (i = 0; i < num_of_args; i++)
	{
		strcat(buffer, va_arg(valist, char *));
		strcat(buffer, " ");
	}
	va_end(valist);

	_message("ERROR - ", buffer);
}
