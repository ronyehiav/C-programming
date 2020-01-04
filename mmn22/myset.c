#include "set.h"

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

int main()
{
	char cmd_from_stdin[MAX_COMMAND_LENGTH];
	int i;

	initialize_sets();
	initialize_commands();
	
	puts("Hello and welcome to set calculator!\nFeel free to type the \"help\" command for more information\n");
	
	while(1)
	{
		printf(COMMAND_PROMPT);
		
		/* if input detected */
		if (scanf("%s", cmd_from_stdin) == 1) /* store the first word of the input into cmd_from_stdin */
		{
			for ( i = 0 ; cmds[i].command_function != NULL ; i++ )
			{
				if (strcmp(cmd_from_stdin, cmds[i].command_name) == 0) /* compare cmd_from_stdin with the list of commands available */
					break;
			}
			
			if (cmds[i].command_function == NULL) 
				printf("\nERROR - Undefined command name: %s\n", cmd_from_stdin);
			else
				(*cmds[i].command_function)(); /* run the according command function */ 
		}
	}
	
	return 1;
}

