#include "set.h"

/* cmds initialization */
command cmds[NUMBER_OF_COMMANDS] = {
                {"read_set", read_numbers_to_set_name, "Initialize and insert numbers to the given set.", "read_set <set_name> <num1>,...,<numN> -1"},
                {"print_set", print_set, "Print the given set's content", "print_set <set_name>"},
                {"union_set", union_set, "Store into set_name_3 the result of union operation between set_name_1 and set_name_2", "union_set <set_name_1>, <set_name_2>, <set_name_3>"},
                {"intersect_set", intersection_set, "Store into set_name_3 the result of intersection operation between set_name_1 and set_name_2", "intersect_set <set_name_1>, <set_name_2>, <set_name_3>"},
                {"sub_set", substract_from_set, "Store into set_name_3 the result of substracting set_name_2 from set_name_1 ", "sub_set <set_name_1>, <set_name_2>, <set_name_3>"},
                {"symdiff_set", symetric_difference_set, "Store into set_name_3 the result of symetric difference operation between set_name_1 and set_name_2", "symdiff_set <set_name_1>, <set_name_2>, <set_name_3>"},
                {"stop", stop, "Stop the set calculator", "stop"},
                {"help", help, "Print the help documentation", "help"},
                {"not_valid", NULL, NULL, NULL}
        };

/* Initialize all the sets as empty sets*/
void initialize_sets()
{
	int i, j;

	for ( i = 'A' ; i <= 'A' + NUMBER_OF_SETS && i <= 'A' + MAX_NUMBER_OF_SETS ; i++)
	{
		/* configure the set name with format: SET<capital_letter> */
		sprintf(sets[i - 'A'].set_name, SET_NAME_PREFIX "%c" , (char)i);

		for ( j = 0 ; j <= SET_SIZE_MAX / sizeof(char) ; j++ )
			/* configure the set as empty */
			sets[i-'A'].set_values[j] = 0;
	}
}

/* return a negative value if the string:
	- dont ends by -1
	- contains  anything else except int, blank spaces & ','
   additionally this function eliminates all the blank spaces */
int validate_list_of_elements(char * str)
{
	int i, comma_found = 0;

	/* removing blanck space from str */
	remove_spaces(str);

	for ( i = 0 ; str[i] != '\0' ; i++)
	{
		/* checking if '-1 is the last 2 chars of the string */
		if (str[i] == '-' && str[i+1] != '\0' && str[i+1] == '1' && str[i+2] == '\0') /* win case */
			return 0;

		/* checking if contains other than int or ',' */
		if (!(isdigit(str[i]) || str[i] == ','))
		{
			printf("ERROR - Invalid set member: not an integer\n");
			return -2;
		}

		/* checking multiple consecutive comma */
		if (comma_found != 0 && str[i] == ',')
		{
			printf("ERROR - Multiple consecutive commas\n");
			return -3;
		}
		/* checking not starting by a comma */
		if (str[i] == ',' && i == 0)
		{
			printf("ERROR - Illegal comma\n");
			return -4;
		}
			 
		if (str[i] == ',')
			comma_found = 1;
		else
			comma_found = 0;
	}
	
	/* if the progrmm arrive here, it means that no -1 was found by the end of the line */
	printf("ERROR - List of set members is not terminated correctly\n");	
	return -1;
}

/* remove spaces from the given string */
void remove_spaces (char *  str_trimmed)
{
	/* declare initialize and copy str_trimmed into str_untrimmed */
	char * str_untrimmed = (char *) malloc(strlen(str_trimmed) + 1);
	char * str_head_pointer = str_untrimmed;
	strcpy(str_untrimmed, str_trimmed); 

	while (*str_untrimmed != '\0')
	{
		if(!isspace(*str_untrimmed))
		{
			*str_trimmed = *str_untrimmed;
			str_trimmed++;
		}
		str_untrimmed++;
	}
	*str_trimmed = '\0';
	str_untrimmed = str_head_pointer;
	free(&*str_untrimmed);
}
