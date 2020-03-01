#include "assembler.h"

/* operation code table initialization */
opcode opcodes_table[NUM_OF_OPCODE] = {
	{0, "mov"},
	{1, "cmp"},
	{2, "add"},
	{3, "sub"},
	{4, "lea"},
	{5, "clr"},
	{6, "not"},
	{7, "inc"},
	{8, "dec"},
	{9, "jmp"},
	{10, "bne"},
	{11, "red"},
	{12, "prn"},
	{13, "jsr"},
	{14, "rts"},
	{15, "stop"}
	};

/* symbol table initialization */
symbol * symbol_table = NULL;


/* add entry the the symbol table
	return 0 if succeeded     */
int add_to_symbol_table(char * name, int value, symbol_type type, symbol_location location)
{
	/* new symbol dynamic allocation */
	symbol * new_symbol = (symbol *)malloc(sizeof(symbol));

	_DEBUG("-->> add_to_symbol_table");

	if (!new_symbol) 
	{
		_ERROR(ALLOCATION_ERROR);
		return -1;
	}
	
	/* initialization of the new_symbol */
	new_symbol->name = name;
	new_symbol->value = value;
	new_symbol->type = type;
	new_symbol->location = location;
	new_symbol->next = NULL;

	/* choosing the next based on file the table is empty or not */
	if (symbol_table == NULL)
		symbol_table = new_symbol;
	else
	{
		new_symbol->next = symbol_table;
		symbol_table = new_symbol;
	}

	_DEBUG("Added new symbol in symbol table");

	_DEBUG("<<-- add_to_symbol_table");	
	return 0;
}

/* print the symbol table */
void print_symbol_table()
{
	symbol * sym = symbol_table;
	char buffer[MAX_SYMBOL_LENGTH +1]; /* +1 for \0 - value of the end of array of char */

	_DEBUG("-->> print_symbol_table");
	
	_DEBUG(PRINT_SYM_TABLE);
	_DEBUG(LINE);
	while (sym != NULL)
	{
		_DEBUG(sym->name);

		sprintf(buffer, "%d", sym->value);
		_DEBUG(buffer);

		sprintf(buffer, "%d", sym->type);
		_DEBUG(buffer);

		sprintf(buffer, "%d", sym->location);
		_DEBUG(buffer);
		_DEBUG(LINE);

		sym = sym->next;
	}

	_DEBUG("<<-- print_symbol_table");
}

/* free the dynamically allocated symbol table */
void free_symbol_table()
{
	symbol * sym;

	_DEBUG("-->> free_symbol_table");

	while(symbol_table)
	{
		sym = symbol_table;
		symbol_table = symbol_table->next;
		free(sym);
	}
	_DEBUG("<<-- free_symbol_table");
}

/* check if the given string is configured as name of a symbol */
int is_a_symbol(char str[])
{
	symbol * sym = symbol_table;

	while (sym != NULL) 
	{
		if ((strcmp(sym->name)) == ZERO)
			return -1;
		sym = sym->next;
	}
	return 0;	
}

/* check if the given string is an operation name */
int is_an_operation_name(char str[])
{
	int i;
	
	for(i = 0;i < NUM_OF_OPCODE ; i++)
	{
		if(strcmp(opcodes_table[i]->name, str) == ZERO)
			return -1;
	}
	return 0;
}
