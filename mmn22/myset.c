#include "set.h"

int main()
{
	char cmd_from_stdin[MAX_COMMAND_LENGTH];
	int i, return_code;

	initialize_sets();
	
	puts("Hello and welcome to set calculator!\nFeel free to type the \"help\" command for more information\n");
	
	while(1)
	{
		printf(COMMAND_PROMPT);
		
		/* if input detected */
		if ((return_code = scanf("%s", cmd_from_stdin)) == 1) /* store the first word of the input into cmd_from_stdin */
		{
			/* printing command to stdout */
			printf("%s", cmd_from_stdin);

			for ( i = 0 ; cmds[i].command_function != NULL ; i++ )
			{
				if (strcmp(cmd_from_stdin, cmds[i].command_name) == 0) /* compare cmd_from_stdin with the list of commands available */
					break;
			}
			
			/* checking if the command exists */
			if (cmds[i].command_function == NULL) 
			{
				/* if the command dont exists, print the end of the command to stdout */
				if (( scanf(" %[^\n]s", cmd_from_stdin)) == 1) 
				{
					printf(" %s", cmd_from_stdin);
					printf("\nERROR - Undefined command name: %s\n", cmd_from_stdin);
				}
			}
			else
				(*cmds[i].command_function)(); /* run the according command function */ 
		}
		else if (return_code == EOF)
		{
			printf("\nERROR - The program was not exited correctly\n");
			stop();
		}
	}
	
	return 1;
}

