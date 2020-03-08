#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include "error.h"

#define MIN_NUMBER_OF_ARGS 2 /* includes the command itself */
#define MAX_MESSAGE_SIZE 50
#define NUM_OF_OPCODE 16
#define MAX_SYMBOL_LENGTH 31
#define MAX_LINE_LENGTH 80
#define MAX_ADDRESS_SIZE 10
#define MAX_DATA_SIZE 13
#define IN_FILE_SUFFIX_SIZE 3
#define IN_FILE_SUFFIX ".as"
#define LINE_NUM_BUF_SIZE 6
#define ZERO 0
#define START_IC_VALUE 100
#define CODE_SIZE 2
#define DATA_DIRECTIVE_TEXT ".data"
#define STRING_DIRECTIVE_TEXT ".string"
#define ENTRY_DIRECTIVE_TEXT ".entry"
#define EXTERN_DIRECTIVE_TEXT ".extern"
#define LINE "--------------------------------------------------"

enum {YES, NO}; 
typedef enum {INSTRUCTION_TABLE_TYPE, DATA_TABLE_TYPE} image_type;
typedef enum {CODE, DATA, NONE=0} symbol_type;
typedef enum {ENTRY, EXTERNAL, UNKNOWN=0} symbol_location;


/* opcode struct definition */
typedef struct opcode {
	int value;
	char * name;
	int operand_number_required;
	} opcode;

/* symbol struct definition */
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
	short int code;
	struct image_entry * next;
	} image_entry;


/* function prototype */
void _message(char [],char []);
void _WARNING(int, ...);
void _ERROR(int, ...);
void _DEBUG(int, ...);
int add_to_symbol_table(char *, int, symbol_type, symbol_location);
void print_symbol_table();
void free_symbol_table();
void do_assembler(FILE *);
int add_to_image(image_type, int, short int);
void free_image(image_type);
int do_first_run(FILE *);
int is_data(char []);
int is_string(char []);
int is_entry(char []);
int is_extern(char []);
int is_directive(char []);
int is_a_symbol(char []);
int is_label(char []);
int is_valid_label(char []);
int is_a_register(char []);
int is_an_operation_name(char []);
int validate_list_of_elements(char []);
void remove_spaces(char *);
int count_instruction_words(char []);
void print_image(image_type);
int is_blank(char []);
int is_comment(char []);
void add_IC_to_data_symbol();
char * remove_leading_spaces(char *);


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

/* FILE descriptor an filename of inputed files */
FILE * fd_input;
char * current_filename;

/* will be used as a buffer for line number translation from int to array */
char line_number_buffer[LINE_NUM_BUF_SIZE];
