#include "set.h"

int main()
{
	char cmd_from_stdin[MAX_COMMAND_LENGTH];
	int i;

	initialize_sets();
	
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

