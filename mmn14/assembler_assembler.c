#include "assembler.h"

/* do_assembler is assembling the assembly file parameter and is creating 3 output files
	*.ob
	*.int
	*.ext
*/
void do_assembler(FILE * fd_input)
{
	int error_counter = 0;

	/* images/table (re)initialization */
	instruction_image = NULL;
	data_image = NULL;
	symbol_table = NULL;

	/* counters (re)initialization */
	IC = 100; /* instruction counter */
	DC = 0; /* data counter */

	/* do run 1 run 2 */
	error_counter += do_first_run(fd_input);

	print_symbol_table();

	/* print into files */
	
	/* free images/table */
	free_image(INSTRUCTION_TABLE_TYPE);
	free_image(DATA_TABLE_TYPE);
	free_symbol_table();
}


/* first run is building the symbol table and calculate how many memory will be required
	the number of error found will be returned
	if no error - return 0 
*/
int do_first_run(FILE * fd_input)
{
	int error_counter = 0, i = 0;
	int in_error;
	int instruction_words = 0;
	char line[MAX_LINE_LENGTH];
	char * chunk_of_line;

	/* read the file line by line entil EOF */
	while(fgets(line, MAX_LINE_LENGTH, fd_input))
	{
		/* remove last character if it is new line */
		while(line[i] != '\0')
		{
			if (line[i] == '\n')
			{
				line[i] = '\0';
				break;
			}
			i++;
		}
 
		/* in_error allow us to know if doing anything with line or not */
		in_error = NO;

		/* the first word of the line in chunk_of_line */
		chunk_of_line = strtok(line, " ");

		/* label case */
		if (is_label(chunk_of_line)) /* in this case, chunk_of_line is the first word */
		{
			char * label_name;
			
			/* validate label validity or go to next line */
			if(!is_valid_label(chunk_of_line))
			{
				_ERROR(INVALID_LABEL_NAME);
				_ERROR("File ");
				_ERROR("Line ");
				error_counter++;
				in_error = YES;
			}

			/* keep the label name in label_name */
			label_name = chunk_of_line;

			/* the second word of the line in chunk_of_line */
			chunk_of_line = strtok(NULL, " ");

			/* label directive case */
			if (is_directive(chunk_of_line))
			{
				/* data directive label case */
				if (is_data(chunk_of_line))
				{
					int number_of_elements = 0;

					/* the rest of the line in chunk_of_line */
					chunk_of_line = strtok(NULL, "\0");
					
					/* remove spaces from the list */
					remove_spaces(chunk_of_line);

					if((number_of_elements = validate_list_of_elements(chunk_of_line)) <= ZERO)
					{	
						_ERROR(INVALID_LIST_DATA);
						_ERROR("File " );
						_ERROR("Line ");
						error_counter++;
						in_error = YES;
					}
					/* checking if error encountered - if yes, no need to move forward with symbol table and image table additions */
					if(in_error == NO)
					{
						if (add_to_image(DATA_TABLE_TYPE, DC, "code") == ZERO) /* NEED TO ADD SUPPORT FOR MULTIPLE DATA'S */
						{
							if (add_to_symbol_table(label_name, DC, NONE, UNKNOWN) == ZERO)
							{
								_DEBUG("New data symbol registred");
								DC += number_of_elements;
							}
							else
							{
								_ERROR(CANT_ADD_TO_SYMTABLE);
								_ERROR("File " );
								_ERROR("Line " );
								error_counter++;
							}
						}
						else
						{
							_ERROR(CANT_ADD_TO_DATA_IMAGE);
							_ERROR("File " );
							_ERROR("Line " );
							error_counter++;
						}
					}
				}
				/* string directive label case */
				else if (is_string(chunk_of_line))
				{
					int i;
					char * start_of_string = NULL, * end_of_string = NULL;

					/* the rest of the line in chunk_of_line */
					chunk_of_line = strtok(NULL, "\0");

					if (chunk_of_line[strlen(chunk_of_line) -1] == '\n')
						chunk_of_line[strlen(chunk_of_line) -1] = '\0';

					/* iterating over every character */
					for(i = 0 ; i < strlen(chunk_of_line) ; i++)
					{
						/* defining beginning and end of the string */
						if (chunk_of_line[i] == '"')
						{
							if (!start_of_string)
								start_of_string = &chunk_of_line[i];
							else
								end_of_string = &chunk_of_line[i];
						}
						
						/* what comes after the last double quote will be ignored */
						else if ((start_of_string) && (end_of_string))
						{
							_WARNING(1, TEXT_AFTER_END_OF_STR_NOT_RELEVANT);
							_WARNING(1, "File ");
							_WARNING(1, "Line ");
							break;
						}	
					}
					/* invalid line - cant find a string between double quotes */
					if ((!(start_of_string)) || (!(end_of_string))) 
					{
						_ERROR(CANT_FIND_STRING);
						_ERROR("File " );
						_ERROR("Line ");
						error_counter++;
						in_error = YES;
					}

					/* checking if error encountered - if yes, no need to move forward with symbol table and image table additions */
					if(in_error == NO)
					{
						if (add_to_image(DATA_TABLE_TYPE, DC, "code") == ZERO) /* NEED TO ADD SUPPORT FOR MULTIPLE DATA'S */
						{
							if (add_to_symbol_table(label_name, DC, NONE, UNKNOWN) == ZERO)
							{
								DC += (end_of_string - start_of_string +1 -2); /* +1 for the '\0' to be added AND -2 for the the 2 '"'*/
								_DEBUG("New data symbol registred");
							}
							else
							{
								_ERROR(CANT_ADD_TO_SYMTABLE);
								_ERROR("File " );
								_ERROR("Line " );
								error_counter++;
							}
						}
						else
						{
							_ERROR(CANT_ADD_TO_DATA_IMAGE);
							_ERROR("File " );
							_ERROR("Line " );
							error_counter++;
						}
					}
				}
				/* entry directive label case - need to warn the user (in second run) about not taking the label into consideration */
				else if (is_entry(chunk_of_line))
				{
					; /* nothing to do for first run, but need to take care of it in second run */
				}
				/* extern directive label case - need to warn the user (in second run) about not taking the label into consideration */
				else if (is_extern(chunk_of_line))
				{
					/* next word is label name */
					chunk_of_line = strtok(NULL, " ");

					if ((!(is_a_symbol(chunk_of_line))) && (is_valid_label(chunk_of_line)))
					{
						if (add_to_symbol_table(chunk_of_line, ZERO, NONE, EXTERNAL) == ZERO)
						{
							_DEBUG("New external symbol registered");
						}
					}
					else
					{
						_ERROR(ALREADY_INITIALIZED_LABEL);
						_ERROR("File ");
						_ERROR("Line ");
						error_counter++;
					}
				}
				/* invalid syntax */
				else
				{
					_ERROR(INVALID_LABEL_DIRECTIVE);
					_ERROR("File " );
					_ERROR("Line " );
					error_counter++;
				}
			}
			else /* label instruction case */
			{
				if((instruction_words = count_instruction_words(chunk_of_line)) < ZERO)
				{
					_ERROR(INVALID_INSTRUCTION);
					_ERROR("File " );
					_ERROR("Line " );
					error_counter++;
					in_error = YES;
				}
				/* checking if error encountered - if yes, no need to move forward with symbol table and image table additions */
				if(in_error == NO)
				{
					if (add_to_symbol_table(label_name, IC, CODE, UNKNOWN) == ZERO)
					{
						IC += instruction_words;
						_DEBUG("New data symbol registred");
					}
					else
					{
						_ERROR(CANT_ADD_TO_SYMTABLE);
						_ERROR("File " );
						_ERROR("Line " );
						error_counter++;
					}
				}
				
			}
		}
		else if (is_extern(chunk_of_line)) /* not a label - need to check if extern */
		{
			/* next word is label name */
			chunk_of_line = strtok(NULL, " ");

			if ((!(is_a_symbol(chunk_of_line))) && (is_valid_label(chunk_of_line)))
			{
				if (add_to_symbol_table(chunk_of_line, ZERO, NONE, EXTERNAL) == ZERO)
				{
					_DEBUG("New external symbol registered");
				}
			}
			else
			{
				_ERROR(ALREADY_INITIALIZED_LABEL);
				_ERROR("File ");
				_ERROR("Line ");
				error_counter++;
			}
		}
		else if ((instruction_words = count_instruction_words(chunk_of_line)) >= ZERO)
		{
			IC += instruction_words;
		}
		else /* not a valid start of line */
		{
			_ERROR(LINE_NOT_UNDERSTANDABLE);
			_ERROR("File ");
			_ERROR("Line ");
			error_counter++;
		}
	} /* end of while loop - line */
	return error_counter;
}
