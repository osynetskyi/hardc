#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
void print_letters(char arg[], int len);

void print_arguments(int argc, char *argv[])
{
	int i = 0;
	char **cur_arg = argv;

	for(i = 0; i < argc; i++) {
		print_letters(*(cur_arg+i), strlen(cur_arg[i]));
	}
}

void print_letters(char arg[], int len)
{
	int i = 0;

	//for(i = 0; arg[i] != '\0'; i++) {
	for(i = 0; i < len; i++) {
		char ch = arg[i];

		if(isalpha(ch) || isblank(ch)) {
			printf("'%c' == %d ", ch, ch);
		}
	}

	printf("\n");
}

int main(int argc, char *argv[])
{
	print_arguments(argc, argv);
	return 0;
}
