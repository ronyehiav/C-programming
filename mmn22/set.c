#include "set.h"

void read_numbers_to_set_name()
{
	char cmd_from_stdin[MAX_COMMAND_LENGTH];
	char * backup_set_value, * chunk_of_cmd_from_stdin = NULL;
	int i, to_be_inserted;

	if (scanf("%s", cmd_from_stdin) == 1)
	{
		/* looking for the index of the requested set */
		for ( i = 0 ; i< NUMBER_OF_SETS ;  i++ )
		{
			if (strcmp(cmd_from_stdin, sets[i].set_name) == 0)
				break;
		}
		
		/* set name not found */
		if ( i == NUMBER_OF_SETS )
			printf("ERROR - Undefined set name: %s\n", cmd_from_stdin);
		else /* set name found */
		{
			if (scanf(" %[^\n]s", cmd_from_stdin) == 1)
			{
				/* validating input */ 
				if (validate_list_of_elements(cmd_from_stdin) >= 0)
				{
					/* allocate for backing up the set value, in case an out of range number is found */ 
					backup_set_value = malloc(strlen(sets[i].set_values) +1);

					if (!backup_set_value)
						printf("ERROR - Failed to allocate more memory\n");
					else
					{
						/* back up the set value */
						strcpy(backup_set_value, sets[i].set_values);
						
						/* splitting the command to multiple chunks, when the delimitter is ',' */
						* chunk_of_cmd_from_stdin = * strtok(cmd_from_stdin, ",");
						
						while (chunk_of_cmd_from_stdin != NULL)
						{
							/* translate string to int */
							to_be_inserted = atoi(chunk_of_cmd_from_stdin);

							/* validating string is in the range */ 
							if (to_be_inserted > MAX_ELEMENT_VALUE || to_be_inserted < MIN_ELEMENT_VALUE) 
							{
								printf("ERROR - Invalid set member - value out of range\n");
								
								/* reset the set value as before */
								strcpy(sets[i].set_values, backup_set_value);
								break;
							}
							else /* adding numbers to set */
							{
								printf("%d\n",to_be_inserted);
								if (to_be_inserted != -1)
									printf("ADDD NUMBERRRRR\n");
							}
						}
						free(backup_set_value);
					}
				}
			}
			else
				printf("ERROR - Can't read from stdin\n"); 
		}
	}
	else
		printf("ERROR - Can't read from stdin\n");
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

/* stop the program */
void stop()
{
	printf("Exiting ...\n");
	exit(1);
}

/* print help */ 
void help()
{
	int i;

	printf("%sHelp%s\n", BAR, BAR);
	for ( i = 0 ; cmds[i].command_function != NULL ; i++ )
		printf("Command: %s\nDescription: %s\nUsage: %s\n\n", cmds[i].command_name, cmds[i].description, cmds[i].usage);
}
