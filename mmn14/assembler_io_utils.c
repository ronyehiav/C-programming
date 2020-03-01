#include "assembler.h"

/* is_data checks if the string given as parameter is from directive type data */
int is_data(char str[])
{
	if (strcmp(str, DATA_DIRECTIVE_TEXT))
		return 1;
	return 0;
}

/* is_string checks if the string given as parameter is from directive type string */
int is_string(char str[])
{
	if (strcmp(str, STRING_DIRECTIVE_TEXT))
		return 1;
	return 0;
}

/* is_entry checks if the string given as parameter is from directive type entry */
int is_entry(char str[])
{
	if (strcmp(str, ENTRY_DIRECTIVE_TEXT))
		return 1;
	return 0;
}

/* is_extern checks if the string given as parameter is from directive type external */
int is_extern(char str[])
{
	if (strcmp(str, EXTERN_DIRECTIVE_TEXT))
		return 1;
	return 0;
}

/* is_directive checks if the string given as parameter is from any directive type */
int is_directive(char str[])
{
	if ((is_data(str)) || (is_string(str)) || (is_entry(str)) || (is_extern(str)))
		return 1;
	return 0;
}

/* is_label checks if the string given as parameter have the label format */
int is_label(char str[])
{
	int len = 0;
	/* label start with a letter */
	if (!(isalpha(str[ZERO]))
		return 0;

	/* label is not more than MAX_SYMBOL_LENGTH long */
	if ((len = strlen(str)) >= (MAX_SYMBOL_LENGTH +2)) /* +2 for the ":" and the \0 end of string */
		return 0;

	/* label declaration finished by ":" */
	if (str[len -1] != ':') 
		return 0;
	
	return 1;
}

/* is_valid_label checks if the string given as a label is valid
	this function is triming the last character of the label declaration - ':'
*/
int is_valid_label(char str[])
{
	/* trunckating the last character (':') to keep the label itself */
	str[strlen(p)-1] = '\0';

	/* valid label is not already initialized */
	if (is_a_symbol(str))
		return 0;

	/* valid label is not a register name */
	if (is_a_register(str))
		return 0;

	/* valid label is not an operation name */
	if (is_an_operation_name(str))
		return -1;
	
	return 0;
}

/* check if the given string is a register name (r0, r1, ... , r7) */)
int is_a_register(char str[])
{
	if (str[ZERO] == 'r')
		if ((str[1] == '0') ||
		(str[1] == '1') ||
                (str[1] == '2') ||
                (str[1] == '3') ||
                (str[1] == '4') ||
                (str[1] == '5') ||
                (str[1] == '6') ||
                (str[1] == '7'))
			if (str[2] == '\0')
				return 1;
	return 0;
}

/* check if the given string is a valid list of elements means int values sperated by ','
	return the number of elements found 
	if error encountered - return -1
*/
int validate_list_of_elements(char str[])
{
	int elements_found = 0;
	int i = 0;
	int num_started = NO;
	
	for(i = 0; str[i] != '\0'; i++)
	{
		if((str[i] == '+') ||  (str[i] == '-'))
		{
			if (num_started == YES)
			{
				element_found = -1;
				break;
			}
			num_started = YES;
		}
		else if(isdigit(str[i]))
			num_started = YES;
		else if (str[i] == ',')
		{
			if (num_started == NO) /* 2 ',' in a row case */
			{
				element_found = -1;
				break;
			}

			/* new element found */
			element_found++;
			num_started = NO;
		}
		else
		{
			element_found = -1;
			break;
		}
	}
	return ++elements_found; /* +1 for the last element between the last ',' and the '\0' */
}