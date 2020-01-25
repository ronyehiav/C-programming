#include "hash.h"

int main(int argc, char * argv[])
{
	node * hash_table[MAX_NUMBER_VALUE - MIN_NUMBER_VALUE +1] = {NULL};
	int file_index;
	FILE * fd;	

	/* validate minimum number of arguments */
	if (argc < MIN_NUMBER_OF_ARGS)
	{
		fprintf(stderr, "ERROR - Number of command-line argument provided is: %d - Required is: %d\n", argc, MIN_NUMBER_OF_ARGS);
		return 1;
	}

	/* iterate over every argument - other than the command */	
	for (file_index = 1; file_index < argc; file_index++) 
	{
		/* open file - once at a time due to the iteration */
		if (!(fd = fopen(argv[file_index], "r")))
		{
			fprintf(stderr, "ERROR - Can't open the file: %s - %s\n", argv[file_index], strerror(errno));
			return 2;
		}

		read_file_values_into_hash_table(fd, argv[file_index], hash_table);

		/* close file */
		fclose(fd);
	}

	print_hash_table(hash_table);
	
	free_hash_table(hash_table);
	return 0;
}
