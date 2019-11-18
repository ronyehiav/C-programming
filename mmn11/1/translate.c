#include <stdio.h>
#include <string.h>

#define arr_size sizeof(unsigned int) * 8

/* function prototypes */
void hex_dec_translate(char str[]);
unsigned int array_to_decimal(char str[]);
void print_base10_to_base2(unsigned int base10_number); 

int main()
{
	char str[arr_size];

	printf("Please insert a base 10 number to be converted into base 2:\n");
	scanf("%s", str);

	hex_dec_translate(str);

	return 0;
}

/* prints to stdout the translation of a given array of numerical characters to binary representation */
void hex_dec_translate(char str[])
{
	unsigned int base10_number;

	base10_number = array_to_decimal(str);
	print_base10_to_base2(base10_number);
}

/* return the decimal value of a given array of numerical character - positive only */
unsigned int array_to_decimal(char str[])
{
	unsigned int to_be_returned = 0, array_length = 0, factor = 1;
	int i;

	array_length = strlen(str) -1; 
	for (i = array_length ; i >= 0 ; i -= 1)
	{
		to_be_returned += (str[i]-'0') * factor;
		factor = factor * 10;
	}

	return to_be_returned;
}

/* print to stdout the binary representation of a base 10 number */
void print_base10_to_base2(unsigned int base10_number)
{
	unsigned int bit, count = 0;

	printf("The binary value of %u is : \n", base10_number); 
	for (bit = 1u << ((sizeof(unsigned int) * 8) - 1) ; bit != 0 ; bit = bit >> 1)
	{
		putchar((base10_number & bit) ? '1' : '0');
		count += 1;
		if (count % 8 == 0)
			putchar(' ');
	}
	putchar('\n');
}
