#include "hash.h"

void read_file_values_into_hash_table(FILE * fd, char * file_name, node * hash_table[])
{
	int value;

	/* iterate over every value in file */
	while (fscanf(fd, "%d", &value) != EOF)
	{
		insert_value_to_list(file_name, &hash_table[value]);
	}
}

void insert_value_to_list(char * file_name, node ** head)
{
	node * new_node, * pointer;
	char * new_file_name;

	/* allocate new node */
	if(!(new_node = malloc(sizeof(node))))
	{
		printf("ERROR - Can't allocate a new node\n");
		return;
	}

	/* copy file name to be used by the node */
	if(!(new_file_name = malloc(sizeof(file_name))))
	{
		printf("ERROR - Can't allocate a new file name\n");
		return;
	}
	strcpy(new_file_name, file_name);

	/* new node initialization */
	new_node->file_name = new_file_name;
	new_node->count = 1;
	new_node->next = NULL;

	/* empty list case */
	if (* head == NULL)
		* head = new_node;

	else /* not empty list */
	{
		pointer = * head;

		/* traverse the linked list until file_name is found or before last node in list found */
		while (strcmp(pointer->file_name, file_name) != 0 && pointer->next != NULL)
			pointer = pointer->next;
		
		/* existing node with same file name found */
		if (strcmp(pointer->file_name, file_name) == 0)
		{
			pointer->count++;

			/* no need to keep the new node nor the new file name as an existing node is being used */
			free(new_node);
			free(new_file_name);
		}
		else /* before last node in list case */
		{
			pointer->next = new_node;
		}
	}
}

void print_hash_table(node * hash_table[])
{
	int i;
	node * node;

	/* iterate over all the possible value in the hash table */
	for (i = 0; i < MAX_NUMBER_VALUE - MIN_NUMBER_VALUE +1; i++)
	{
		/* no action item needed if the number was not encountered */ 
		if (hash_table[i] != NULL)
		{
			/* set the pointer to be on the head of the linked list */
			node = hash_table[i];
			printf("%d appears in ", i);

			/* traverse the linked list */
			while (node != NULL)
			{
				/* not file to print case */
				if (node != hash_table[i])
					printf(", ");

				printf("file %s - %d time", node->file_name, node->count);

				/* add plural if needed */
				if (node->count > 1)
					putchar('s');
				
				node = node->next;
			}
			putchar('\n');
		}
	} 
}
