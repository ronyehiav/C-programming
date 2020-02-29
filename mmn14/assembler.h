#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "error.h"

#define MIN_NUMBER_OF_ARGS 2 /* includes the command itself */
#define MAX_MESSAGE_SIZE 50
#define NUM_OF_OPCODE 16


/* opcode structrure definition */
typedef struct opcode {
	int value;
	char * name;
	} opcode;



/* function prototype */
void _message(char [],char []);
void _WARNING(char []);
void _ERROR(char []);
void _DEBUG(char []);


/* opcodes_table declaration */
opcode opcodes_table[NUM_OF_OPCODE];
