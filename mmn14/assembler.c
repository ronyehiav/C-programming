#include "assembler.h"

int main(int argc, char * argv[])
{
	FILE * fd_input;
	int file_index;

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

		/* start assembling this file */
		do_assembler(fd_input);

		/* close file */
		fclose(fd_input);
	}	

	return 0;
}
