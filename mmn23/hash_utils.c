#include "hash.h"

void read_file_values_into_hash_table(FILE * fd, char * file_name, node * hash_table[])
{
	int value;

	/* iterate over every value in file */
	while (fscanf(fd, "%d", &value) != EOF)
	{
		insert_value_to_list(file_name, hash_table[value]);
	}
}

void insert_value_to_list(char * file_name, node * head)
{
	node * new_node, * pointer;

	/* allocate new node */
	if(!(new_node = malloc(sizeof(node))))
	{
		printf("ERROR - Can't allocate a new node\n");
		return;
	}

	/* new node initialization */
	strcpy(new_node->file_name, file_name);
	new_node->count = 1;
	new_node->next = NULL;

	/* empty list case */
	if (head == NULL)
	{
		head = new_node;
	}
	else /* not empty list */
	{
		pointer = head;

		/* traverse the linked list until file_name is found or before last node in list found */
		while (strcmp(pointer->file_name, file_name) != 0 && pointer->next != NULL)
			pointer = pointer->next;
		
		/* existing node with same file name found */
		if (pointer->file_name == file_name)
		{
			pointer->count++;

			/* no need to keep the new node as an existing node is being used */
			free(new_node);
		}
		else /* before last node in list case */
		{
			pointer->next = new_node;
		}
	}
}
