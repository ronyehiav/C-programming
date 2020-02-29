#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "error.h"

#define MIN_NUMBER_OF_ARGS 2 /* includes the command itself */
#define MAX_MESSAGE_SIZE 50

/* function prototype */
void _message(char [],char []);
void _WARNING(char []);
void _ERROR(char []);
void _DEBUG(char []);
