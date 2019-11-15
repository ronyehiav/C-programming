#include <stdio.h>
#include <string.h>

#define arr_size sizeof(unsigned int)

/* function prototypes */
void hex_dec_translate(char str[]);
int array_to_decimal(char str[]);
void print_base10_to_base2(int base10_number); 

int main()
{
	char str[arr_size];
	printf("Please insert a base 10 number to be converted into base 2:\n");
	scanf("%s", str);
	hex_dec_translate(str);
	return 0;
}

void hex_dec_translate(char str[])
{
	int base10_number;
	base10_number = array_to_decimal(str);
	printf("%d\n", base10_number);
	print_base10_to_base2(base10_number);
}

int array_to_decimal(char str[])
{
	int i, to_be_returned = 0, array_length = 0, factor = 1;
	array_length = strlen(str) -1; 
	printf("DEBUG - arr_size=%ld\n", arr_size);
	printf("DEBUG - String Length is %d\n", array_length+1);
	for (i = array_length ; i >= 0 ; i -= 1)
	{
		printf("DEBUG - to_be_returned = %d\n", to_be_returned);
		to_be_returned += (str[i]-'0') * factor;
		printf("DEBUG - to_be_returned = %d, (int)(str[i]) = %c, factor = %d ,  (str[i]-'0')= %d\n", to_be_returned, (int)(str[i]), factor ,  (str[i]-'0'));
		factor = factor * 10;
	}
	return to_be_returned;
}

void print_base10_to_base2(int base10_number)
{
	return;
}
 
