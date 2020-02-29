#include "assembler.h"

int main(int argc, char * argv[])
{
	FILE * fd_input;
	int file_index;

	/* Following some example about how to use functions: 
	_WARNING(WARNING_EXAMPLE);
	_ERROR(ERROR_EXAMPLE);
	_DEBUG(DEBUG_EXAMPLE);
	_DEBUG(opcodes_table[0].name); 	
	add_to_symbol_table("eliott", 420, DATA, ENTRY);
	add_to_symbol_table("irit", 101, DATA, NONE);
	add_to_symbol_table("liott", 40, CODE, EXTERNAL);
	add_to_symbol_table("tt", 20, CODE, ENTRY);
	print_symbol_table();
	free_symbol_table();
	print_symbol_table();
	add_to_image(INSTRUCTION_TABLE_TYPE, 111, "11");
	add_to_image(DATA_TABLE_TYPE, 222, "2");
	*/	
	

	/* validate minimum number of arguments */
	if (argc < MIN_NUMBER_OF_ARGS)
	{
		_ERROR(INVALID_ARGS_NUM);
		return 1;
	}


	/* iterate over every argument */
	for (file_index = 1; file_index < argc; file_index++)
	{
		/* open file */
		if (!(fd_input = fopen(argv[file_index], "r")))
		{
			_ERROR(FILE_OPEN);
			_ERROR(argv[file_index]);
			_ERROR(strerror(errno));
			return 2;
		}

		/* do_assembler will be here */
		do_assembler(fd_input);		

		/* close file */
		fclose(fd_input);
	}	


	/* free the dynamically allocated memory */
	free_symbol_table();

	return 0;
}
