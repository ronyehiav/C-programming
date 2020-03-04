#include "assembler.h"

/* images initialization */
image_entry * instruction_image = NULL;
image_entry * data_image = NULL;

/* add entry an image - return 0 if succeeded     */
int add_to_image(image_type type, int address, short int code)
{
	/* new image entry dynamic allocation */
	image_entry * new_entry = (image_entry *)malloc(sizeof(image_entry));

	if ((!new_entry))
	{
		_ERROR(1, ALLOCATION_ERROR);
		return -1;
	}

	/* initialization of the new_entry */
	new_entry->address = address;
	new_entry->code = code;
	new_entry->next = NULL;
	
	

	/* choosing the next based on file the table is empty or not */
	if (type == INSTRUCTION_TABLE_TYPE)
	{
		if (instruction_image == NULL)
			instruction_image = new_entry;
		else
		{	
			image_entry * p = instruction_image;
			while (p->next != NULL)
				p = p->next;
			p->next = new_entry;
		}
	} 
	else /* (type == DATA_TABLE_TYPE) */
	{
		if (data_image == NULL)
			data_image = new_entry;
		else
		{	
			image_entry * p = data_image;
			while (p->next != NULL)
				p = p->next;
			p->next = new_entry;
		}
	}
	return 0;
}

/* free the dynamically allocated image*/
void free_image(image_type type)
{
	image_entry * entry;

	if (type == INSTRUCTION_TABLE_TYPE)
	{
		while(instruction_image)
		{
			entry = instruction_image;
			instruction_image = instruction_image->next;
			free(entry);
		}
	}
	else /* (type == DATA_TABLE_TYPE) */
	{
		while(data_image)
		{
			entry = data_image;
			data_image = data_image->next;
			free(entry);
		}
	}
}

/* print the symbol table */
void print_image(image_type type)
{
        image_entry * entry;
        char buffer1[MAX_ADDRESS_SIZE]; 
	char buffer2[MAX_DATA_SIZE];

	if (type == INSTRUCTION_TABLE_TYPE)
	{
		entry = instruction_image;
        	_DEBUG(1, PRINT_INSTRUCTION_TABLE);
	}
	else /* (type == DATA_TABLE_TYPE) */
	{
		entry = data_image; 
		_DEBUG(1, PRINT_CODE_IMAGE);
	}

        _DEBUG(1, LINE);
	
	while (entry != NULL)
	{
		sprintf(buffer1, "%d", entry->address);
		sprintf(buffer2, "%d", entry->code);
		_DEBUG(2, buffer1, buffer2);
		_DEBUG(1, LINE);
		entry = entry->next;
	}
}
