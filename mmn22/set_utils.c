#include "set.h"

/* cmds initialization */
command cmds[NUMBER_OF_COMMANDS] = {
                {"read_set", read_numbers_to_set_name, "Initialize and insert numbers to the given set.", "read_set <set_name>"},
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

