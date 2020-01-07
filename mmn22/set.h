#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define SET_SIZE_MAX 128
#define NUMBER_OF_SETS 6
#define MAX_NUMBER_OF_SETS 26 /* total of 26 alphabeic capital letters (A-Z) - due to set name convention (SET<capital_letter>) */
#define SET_NAME_LENGTH 4
#define SET_NAME_PREFIX "SET"
#define MAX_COMMAND_LENGTH 120
#define BAR " =============== "
#define COMMAND_PROMPT "(set_calculator) >>> "
#define NUMBER_OF_COMMANDS 10
#define BASE10 10
#define MAX_ELEMENT_VALUE 127
#define MIN_ELEMENT_VALUE 0



/* set struct declaration */ 
typedef struct {
	char set_name[SET_NAME_LENGTH +1];
	char set_values[SET_SIZE_MAX / (sizeof(char) * 8)];
	} set;

/* commands struct declaration */
typedef struct {
	char *command_name;
	void (*command_function) ();
	char *description;
	char *usage;
	} command ;

/* functions prototype */
void read_numbers_to_set_name();
void print_set();
void print_set_bin();
void union_set();
void intersection_set();
void substract_from_set();
void symetric_difference_set();
void stop();
void help();
void initialize_sets();
int str_is_numeric(char *);
int validate_list_of_elements(char *);
void remove_spaces(char *);
int get_set_index(char *);
void add_int_to_set(int, int);
void add_mask_to_set(char *, char);
char create_mask(int);


set sets[NUMBER_OF_SETS <= MAX_NUMBER_OF_SETS ? NUMBER_OF_SETS : MAX_NUMBER_OF_SETS]; /* sets declaration */
command cmds[NUMBER_OF_COMMANDS]; /* cmds declaration */ 

