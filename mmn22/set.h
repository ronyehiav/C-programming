#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SET_SIZE_MAX 128
#define NUMBER_OF_SETS 6
#define MAX_NUMBER_OF_SETS 26 /* total of 26 alphateic capital letters (A-Z) - due to set name convention (SET<capital_letter>) */
#define SET_NAME_LENGTH 4
#define SET_NAME_PREFIX "SET"
#define MAX_COMMAND_LENGTH 30
#define COMMAND_PROMPT "(set_calculator) >>> "
#define NUMBER_OF_COMMANDS 9



/* set struct declaration */ 
typedef struct {
	char *set_name;
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
void initialize_commands();

/* command cmds[NUMBER_OF_COMMANDS]; * commands declaration */
set sets[NUMBER_OF_SETS <= MAX_NUMBER_OF_SETS ? NUMBER_OF_SETS : MAX_NUMBER_OF_SETS]; /* sets declaration */

command cmds[NUMBER_OF_COMMANDS] = {
		{"read_set", read_numbers_to_set_name, "Initialize and insert numbers to the given set.", "read_set <set_name>"},
		{"print_set", print_set, "Print the given set's content", "print_set <set_name>"},
		{"union_set", union_set, "Store into set_name_3 the result of union operation between set_name_1 and set_name_2", "union_set <set_name_1>, <set_name_2>, <set_name_3>"},
		{"intersect_set", intersection_set, "Store into set_name_3 the result of intersection operation between set_name_1 and set_name_2", "intersect_set <set_name_1>, <set_name_2>, <set_name_3>"},
		{"sub_set", substract_from_set, "Store into set_name_3 the result of substracting set_name_2 from set_name_1 ", "sub_set <set_name_1>, <set_name_2>, <set_name_3>"},
		{"symdiff_set", symetric_difference_set, "Store into set_name_3 the result of symetric difference operation between set_name_1 and set_name_2", "symdiff_set <set_name_1>, <set_name_2>, <set_name_3>"},
		{"stop", stop, "Stop the set calculator", "stop"},
		{"help", help, "Print the help documentation", "help"},
		{"not_valid", NULL, NULL, NULL}
	};
