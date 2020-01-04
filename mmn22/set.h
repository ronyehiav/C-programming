#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SET_SIZE_MAX 128
#define NUMBER_OF_SETS 6
#define MAX_NUMBER_OF_SETS 26 /* total of 26 alphabeic capital letters (A-Z) - due to set name convention (SET<capital_letter>) */
#define SET_NAME_LENGTH 4
#define SET_NAME_PREFIX "SET"
#define MAX_COMMAND_LENGTH 60
#define BAR " =============== "
#define COMMAND_PROMPT "(set_calculator) >>> "
#define NUMBER_OF_COMMANDS 9



/* set struct declaration */ 
typedef struct {
	char set_name[SET_NAME_LENGTH];
	char set_values[SET_SIZE_MAX / sizeof(char)];
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
void union_set();
void intersection_set();
void substract_from_set();
void symetric_difference_set();
void stop();
void help();
void initialize_sets();

set sets[NUMBER_OF_SETS <= MAX_NUMBER_OF_SETS ? NUMBER_OF_SETS : MAX_NUMBER_OF_SETS]; /* sets declaration */
command cmds[NUMBER_OF_COMMANDS]; /* cmds declaration */ 

