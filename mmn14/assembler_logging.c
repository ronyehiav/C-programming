#include "assembler.h"


/* print the given string to STDOUT */
void _message(char prefix[], char str[])
{
	fprintf(stdout, "%s%s\n", prefix, str);
}

/* print the given string as WARNING to STDOUT */
void _WARNING(char str[])
{
	_message("WARNING - ", str);
}

/* print the given string as DEBUG to STDOUT */
void _DEBUG(char str[])
{
	_message("DEBUG - ", str);
}

/* print the given string as ERROR to STDOUT */
void _ERROR(char str[])
{
	_message("ERROR - ", str);
}
