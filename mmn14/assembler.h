#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "error.h"

#define MIN_NUMBER_OF_ARGS 2 /* includes the command itself */
#define MAX_MESSAGE_SIZE 50
#define NUM_OF_OPCODE 16
#define MAX_SYMBOL_LENGTH 31
#define MAX_LINE_LENGTH 80
#define ZERO 0
#define LINE "--------------------------------------------------"

typedef enum {INSTRUCTION_TABLE_TYPE, DATA_TABLE_TYPE} image_type;
typedef enum {CODE, DATA, NONE=0} symbol_type;
typedef enum {ENTRY, EXTERNAL, NONE=0} symbol_location;


/* opcode struct definition */
typedef struct opcode {
	int value;
	char * name;
	} opcode;

/* symbot struct definition */
typedef struct symbol {
	char * name;
	int value;
	symbol_type type;
	symbol_location location;
	struct symbol * next;
	} symbol;

/* image entry struct definition */
typedef struct image_entry
{
	int address;
	char * code;
	struct image_entry * next;
	} image_entry;


/* function prototype */
void _message(char [],char []);
void _WARNING(char []);
void _ERROR(char []);
void _DEBUG(char []);
int add_to_symbol_table(char *, int, symbol_type, symbol_location);
void print_symbol_table();
void free_symbol_table();
void do_assembler(FILE *);
int add_to_image(image_type, int, char *);
void free_image(image_type);
int do_first_run(FILE *);
int is_data(char []);
int is_string(char []);
int is_entry(char []);
int is_extern(char []);
int is_directive(char []);
int is_label(char []);
int is_valid_label(char []);
int is_a_register(char []);
int is_an_operation_name(char []);
int validate_list_of_elements(char []);


/* opcodes_table declaration */
opcode opcodes_table[NUM_OF_OPCODE];

/* symbol table declaration */
symbol * symbol_table;

/* instruction image declaration */
image_entry * instruction_image;

/* data image declaration */
image_entry * data_image;

/* counters declaration */
int IC; /* instruction counter */
int DC; /* data counter */
