#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MIN_NUMBER_VALUE 0
#define MAX_NUMBER_VALUE 28
#define MIN_NUMBER_OF_ARGS 2 /* includes the command itself */



/* node definition for the linked list */
typedef struct node 
{
	char * file_name;
	int count;
	struct node * next;
} node;

/* functions prototype */
void read_file_values_into_hash_table(FILE *, char *, node * []);
void print_hash_table(node * []);
void insert_value_to_list(char *, node **);
void free_hash_table(node * hash_table[]);
