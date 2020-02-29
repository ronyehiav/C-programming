#include "assembler.h"

/* do_assembler is assembling the assembly file parameter and is creating 3 output files
	*.ob
	*.int
	*.ext
*/
void do_assembler(FILE * fd_input)
{
	int error_counter = 0;

	/* images (re)initialization */
	 instruction_image = NULL;
	 data_image = NULL;

	/* counters (re)initialization */
	IC = 100; /* instruction counter */
	DC = 0; /* data counter */

	/* do run 1 run 2 */
	error_counter += do_first_run(fd_input);

	/* print into files */

	/* free images */
	free_image(INSTRUCTION_TABLE_TYPE);
	free_image(DATA_TABLE_TYPE);
}


/* first run is building the symbol table and calculate how many memory will be required
	the number of error found will be returned
	if no error - return 0 
*/
int do_first_run(FILE * fd_input)
{
	int error_counter = 0;
	char line[MAX_LINE_LENGTH];
	char chunk_of_line[MAX_LABEL_LENGTH +1]; /* +1 for the \0 value of the end of the array of chars */

	/* read the file line by line entil EOF */
	while(fgets(line, MAX_LINE_LENGTH, fd_input))
	{
		/* in_error allow us to know if doing anything with line or not */
		in_error = NO;

		/* the first word of the line in chunk_of_line */
		chunk_of_line = strtok(line, " ");

		/* label case */
		if (is_label(chunk_of_line))
		{
			char * label;
			
			/* keep the label name in label_name */
			label_name = chunk_of_line;

			/* the second word of the line in chunk_of_line */
			chunk_of_line = strtok(NULL, " ");

			/* label directive case */
			if (is_directive(line))
			{
				/* data directive label case */
				if (is_data(chunk_of_line))
				{

				}
				/* string directive label case */
				else if (is_string(chunk_of_line))
				{
					int i;
					char * start_of_string = NULL, * end_of_string = NULL;

					/* the rest of the line in chunk_of_line */
					chunk_of_line = strtok(NULL, NULL);

					/* iterating over every character */
					for(i = 0 ; i < strlen(chunk_of_line) ; i++)
					{
						/* defining beginning and end of the string */
						if (chunk_of_line[i] == '"')
							if (!start_of_string)
								start_of_string = chunk_of_line[i];
							else
								end_of_string = chunk_of_line[i];
						
						/* invalid line - cant find a string between double quotes */
						if ((!(start_of_string)) || (!(end_of_string))) 
						{
							_ERROR(CANT_FIND_STRING);
							_ERROR("File " );
							_ERROR("Line ");
							_ERROR(line)
							error_counter++;
							in_error = YES;
							break;
						}
						
						/* what comes after the last double quote will be ignored */
						if ((start_of_string) && (end_of_string))
						{
							_WARNING(TEXT_AFTER_END_OF_STR_NOT_RELEVANT);
							_WARNING("File ");
							_WARNING("Line ");
							break;
						}	
					}

					if(in_error == NO)
						add_to_symbol_tabledd(label_name, ????, NONE, NONE);
						

				}
				/* entry directive label case */
				else if (is_entry(chunk_of_line))
				{
					; /* nothing to do for now */
				}
				/* extern directive label case */
				else if (is_extern(chunk_of_line))
				{
					add_to_symbol_table(label_name, ????, NONE, EXTERNAL);	
				}
				/* invalid syntax */
				else
				{

				}
			}
			else /* label instruction case */
			{

			}
	}
	
	return error_counter;
}
