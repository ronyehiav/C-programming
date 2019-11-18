#include <stdio.h>
#include <string.h>

/* STR_MAX_LENGTH includes last string character - \0 */
#define STR_MAX_LENGTH 128

/* function prototypes */
int suffix(char str[], char c);

int main()
{
	char str[STR_MAX_LENGTH];
	int c = 0;
	printf("Please insert a character: ");
	c = getchar();
	printf("\nThe inserted character is: %c\n", c);

	/*  clean buffer */
	while ((getchar()) != '\n'); 

	printf("Please insert a string: ");
	fgets(str, sizeof(str), stdin);

	/* removing the enter character */
	if(str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';

	printf("\nThe inserted string is:\n%s\n", str);

	printf("The number of suffix found in your string is: %d\n", suffix(str, c));

	return 0;
}

/* print all the possible character suffix of the given string */
int suffix(char str[], char c)
{	
	int i, str_length = strlen(str), to_be_returned = 0;
	for (i = 0 ; i < str_length ; i++)
	{
		if (str[i] == c)
		{
			/* print partial string - from the character found */
			printf("%s\n", str + i);
			to_be_returned += 1;
		}
	}
	return to_be_returned;
}
