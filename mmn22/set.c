#include "set.h"

/* read list of numbers stdin and store them accordingly in the requested set */
void read_numbers_to_set_name()
{
	char cmd_from_stdin[MAX_COMMAND_LENGTH];
	char * backup_set_value = NULL, * chunk_of_cmd_from_stdin = NULL, * tmp_set_name = NULL;
	int i, to_be_inserted, count = 0;

	if (scanf(" %[^\n]s", cmd_from_stdin) == 1)
	{
		/* removing blank space from cmd_from_stdin */
		remove_spaces(cmd_from_stdin);
		
		/* allocate and copy set name */
		tmp_set_name = malloc(SET_NAME_LENGTH +1);

		for (i = 0; i < SET_NAME_LENGTH; i++)
			tmp_set_name[i] = cmd_from_stdin[i];
		tmp_set_name[i] = '\0';

		/* validating 1st command argument is a defined set and keeping sets index into i*/
		if ((i = get_set_index(tmp_set_name)) < 0 )
		{
			free(tmp_set_name);
			return;
		}

		free(tmp_set_name);

		/* validating list of elements from input */ 
		if (validate_list_of_elements(cmd_from_stdin + (SET_NAME_LENGTH +1)) >= 0) /* pointing to the beggining of the list of elements */
		{
		
			/* splitting the command to multiple chunks, when the delimitter is ',' */
			chunk_of_cmd_from_stdin = strtok(cmd_from_stdin, ",");

			while (chunk_of_cmd_from_stdin != NULL)
			{
				count++;

				if (count == 1) /* means 1 chunk of command */
				{
					/* allocate for backing up the set value, in case an out of range number is found */
					backup_set_value = malloc(strlen(sets[i].set_values) +1);

					if (!backup_set_value)
					{
						printf("ERROR - Failed to allocate more memory\n");
						break;
					}
					
					/* back up the set value */
					strcpy(backup_set_value, sets[i].set_values);
				}
				else /* means we are running over elements */ 
				{
					/* translate string to int */
					to_be_inserted = atoi(chunk_of_cmd_from_stdin);
	
					/* validating string is in the range */
					if (to_be_inserted > MAX_ELEMENT_VALUE || to_be_inserted < MIN_ELEMENT_VALUE)
					{
						if (to_be_inserted != -1)
						{
							printf("ERROR - Invalid set member - value out of range\n");
		
							/* reset the set value as before */
							strcpy(sets[i].set_values, backup_set_value);
							break;
						}
						else /* means we arrived the end of the line and finished our job */ 
							break;
					}
					else /* adding numbers to set */
					{
						if (to_be_inserted != -1)
							add_int_to_set(to_be_inserted, i);
					}
				}
				chunk_of_cmd_from_stdin = strtok(NULL, ",");
			}
			if (backup_set_value)
				free(backup_set_value);
		}
	}
	else
		printf("ERROR - Can't read from stdin\n"); 
}

/* print the set elements in croissant order */
void print_set()
{
	char cmd_from_stdin[MAX_COMMAND_LENGTH];
	char * tmp_set_name = NULL;
	int i, char_index, byte, byte_index, count = 0;

	if (scanf(" %[^\n]s", cmd_from_stdin) == 1)
	{
                /* allocate and copy set name */
                tmp_set_name = malloc(SET_NAME_LENGTH +1);

                for (i = 0; i < SET_NAME_LENGTH; i++)
                        tmp_set_name[i] = cmd_from_stdin[i];
		tmp_set_name[i] = '\0';

                /* validating 1st command argument is a defined set and keeping sets index into i*/
                if ((i = get_set_index(tmp_set_name)) < 0 )
		{
                        free(tmp_set_name);
                        return;
                }

                free(tmp_set_name);

		/* printing every element in set separed by tab with max of 16 per line */
		printf("%s =\n", sets[i].set_name);
		for ( char_index = 0; char_index < SET_SIZE_MAX / (sizeof(char) * 8) ; char_index++)
		{
			/* print the content off each character */
			for (byte = 1 << ((sizeof(char) * 8) -1), byte_index = 0 ; byte != 0 ; byte = byte >> 1, byte_index++)
			{
				/* checking if element exists */
				if ((sets[i].set_values[char_index] & byte) != 0)
				{
					printf("%ld\t", (char_index * (sizeof(char) * 8)) + byte_index);
					count++;
				}

				/* checking if return to a new line is needed */
				if (count == 16 && byte_index != 0)
				{
					count = 0;	
					putchar('\n');
				}
			}
		}
		printf("\n");
	}
        else
                printf("ERROR - Can't read from stdin\n");
	
}

/* print the binary representation of the set value */
void print_set_bin()
{
	char cmd_from_stdin[MAX_COMMAND_LENGTH];
	unsigned char char_index;
	unsigned char byte;
	char * tmp_set_name = NULL;
	int i;
	
	if (scanf(" %[^\n]s", cmd_from_stdin) == 1)
	{
                /* allocate and copy set name */
                tmp_set_name = (char *) malloc(SET_NAME_LENGTH +1);

                for (i = 0; i < SET_NAME_LENGTH; i++)
                        tmp_set_name[i] = cmd_from_stdin[i];
		tmp_set_name[i] = '\0';

                /* validating 1st command argument is a defined set and keeping sets index into i*/
                if ((i = get_set_index(tmp_set_name)) < 0 )
		{
                        free(tmp_set_name);
                        return;
                }

                free(tmp_set_name);

		/* printing every byte one by line */
		for ( char_index = 0; char_index < SET_SIZE_MAX / (sizeof(char) * 8) ; char_index++)
		{
			/* print the content off each byte */
			for (byte = 1 ; byte != 1 >> (sizeof(char) * 8) ; byte = byte << 1)
				putchar((sets[i].set_values[char_index] & byte) ? '1' : '0');
			putchar('\n');
		}
	}
        else
                printf("ERROR - Can't read from stdin\n");
}

/* union between the first and second set - stored in third set */
void union_set()
{
	do_operation_on_set(UNION);
}

/* intersection  between the first and second set - stored in third set */
void intersection_set()
{
	do_operation_on_set(INTERSECTION);
}

/* substract the second set from the first set - stored in third set */
void substract_from_set()
{
	do_operation_on_set(SUBSTRACT);
}

/* symetrical difference between the first and second set - stored in third set */
void symetric_difference_set()
{
	do_operation_on_set(SYMETRICAL_DIFFERENCE);
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

