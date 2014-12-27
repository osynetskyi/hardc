#include <stdio.h>
#include <ctype.h>
#include "dbg.h"

typedef int (*shiftchar)(int c);

int print_a_message(const char *msg)
{
	printf("A STRING: %s\n", msg);

	return 0;
}

int shiftcase(const char *msg,/* int length,*/ shiftchar func)
{
	int i = 0;
	
	for(i = 0; /*i < length*/msg[i] != '\0'; i++) {
		printf("%c", func(msg[i]));
	}

	printf("\n");

	return 0;
}

int uppercase(const char *msg/*, int length*/)
{
	return shiftcase(msg/*, length*/, toupper);
}

int lowercase(const char *msg/*, int length*/)
{
	return shiftcase(msg/*, length*/, tolower);
}

int fail_on_purpose(const char *msg)
{
	return 1;
}
