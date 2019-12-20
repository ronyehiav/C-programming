#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_NAME_LIST 30 
#define NUMBER_OF_NAMES_TO_PRINT 10
#define DUPLICATED_NAME -999 /* return code for duplicated name */

/* global variables */
char name_list[MAX_NAME_LIST +1][MAX_NAME_LENGTH +1]; /* +1 for the zero */

/* function prototypes */
void store_names(int number_of_name);
int is_name_duplicated(char name[], int last_index_used);
char * get_name();


int main()
{
	int i;

	printf("Please insert %d name(s):\n", MAX_NAME_LIST);
	store_names(MAX_NAME_LIST);

	printf("\nThis program randomly picked the following %d names from the inserted list:\n", NUMBER_OF_NAMES_TO_PRINT);

	for (i = 1; i <= NUMBER_OF_NAMES_TO_PRINT ; printf("%s \n", get_name()), i++)
	;

	return 0;
}


/* store number_of_name names from stdin without whitespaces into the global 
array of array of characters name_list and check for duplicated name */
void store_names(int number_of_name)
{
	int i;

	for (i = 0; i <= MAX_NAME_LIST -1; i++)
	{
		scanf("%s", name_list[i]);		
		
		if (is_name_duplicated(name_list[i], i) < 0)
		{
			printf("ERROR! Exiting the program...\n");
			exit(DUPLICATED_NAME);
		}

		printf("Name #%d: %s\n", i +1, name_list[i]);  
	}
}


/* verify if the array of character name[] is already stored in name_list.
the last_index_used allows to check for duplicate only on the already stored values.
the returned value is DUPLICATED_NAME if the inserted value is duplicated. */
int is_name_duplicated(char name[], int last_index_used)
{
	char tmp_lowered_name_from_list[MAX_NAME_LENGTH +1], tmp_lowered_name_from_input[MAX_NAME_LENGTH +1]; /* +1 for the zero */
	int j, i=last_index_used;

	/* keep the last inserted value with lower case only */
	for (j = 0; j <= MAX_NAME_LENGTH ; j++)
		tmp_lowered_name_from_input[j] = tolower(name[j]);

	for (;i >= 0; i--)
	{
		if (i != last_index_used) /* Not comparing last inserted name with itself */
		{
			/* keep the last iterated value with lower case only */
			for (j = 0; j <= MAX_NAME_LENGTH ; j++)
				tmp_lowered_name_from_list[j] = tolower(name_list[i][j]);

			if (strcmp(tmp_lowered_name_from_input,tmp_lowered_name_from_list) == 0)
			{
				printf("Found duplicated names: \'%s\' and \'%s\'\n", name, name_list[i]);
				return DUPLICATED_NAME;	
			}
		}
	}
	return 0;
}


/* return an array of char containing a random name from the name_list */
char * get_name()
{
	return name_list[rand() % MAX_NAME_LIST];
}

