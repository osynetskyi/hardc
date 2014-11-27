/** WARNING: This code is fresh and potentially isn't correct yet. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
	*out_string = calloc(1, max_buffer + 1);
	check_mem(*out_string);

	int i = 0;
	int last = 0;
	char cur = 'a';
	while((i < max_buffer) && (cur != '\n')) {
		cur = fgetc(stdin);
		check(cur != EOF, "Symbol read error");
		*(*out_string + i) = cur;
		i++;
	}

	last = i;
	*(*out_string + last) = '\0';

	return 0;

error:
	if(*out_string) free(*out_string);
	*out_string = NULL;
	return -1;
}

int read_string_old(char **out_string, int max_buffer)
{
	*out_string = calloc(1, max_buffer + 1);
	//*out_string = malloc(sizeof(char) * (max_buffer + 1));
	check_mem(*out_string);

	char *result = fgets(*out_string, max_buffer, stdin);
	check(result != NULL, "Input error.");

	return 0;

error:
	if(*out_string) free(*out_string);
	*out_string = NULL;
	return -1;
}

int read_int(int *out_int)
{
	char *input = NULL;
	int rc = read_string(&input, MAX_DATA);
	check(rc == 0, "Failed to read number.");

	*out_int = atoi(input);

	free(input);
	return 0;

error:
	if(input) free(input);
	return -1;
}

int put_int(int out_int)
{
	char str[12];
	snprintf(str, 12, "%d", out_int);
	int rc = fputs(str, stdout);
	check(rc != EOF, "Failed to write int.");

	return 0;

error:
	return -1;
}

int read_scan(const char *fmt, ...)
{
	int i = 0;
	int rc = 0;
	int *out_int = NULL;
	char *out_char = NULL;
	char **out_string = NULL;
	int max_buffer = 0;

	va_list argp;
	va_start(argp, fmt);

	for(i = 0; fmt[i] != '\0'; i++) {
		if(fmt[i] == '%') {
			i++;
			switch(fmt[i]) {
				case '\0':
					sentinel("Invalid format, you ended with %%.");
					break;

				case 'd':
					out_int = va_arg(argp, int *);
					rc = read_int(out_int);
					check(rc == 0, "Failed to read int.");
					break;
		
				case 'c':
					out_char = va_arg(argp, char *);
					*out_char = fgetc(stdin);
					break;

				case 's':
					max_buffer = va_arg(argp, int);
					out_string = va_arg(argp, char **);
					rc = read_string(out_string, max_buffer);
					//rc = read_by_char(out_string, max_buffer);
					check(rc == 0, "Failed to read string.");
					break;

				default:
					sentinel("Invalid format.");
			}
		} else {
			fgetc(stdin);
		}
	
		check(!feof(stdin) && !ferror(stdin), "Input error.");
	}

	va_end(argp);
	return 0;

error:
	va_end(argp);
	return -1;
}

int print_put(const char *fmt, ...)
{
	int i = 0;
	int rc = 0;
	int out_int = 0;
	char out_char = '0';
	char *out_string = NULL;

	va_list argp;
	va_start(argp, fmt);

	for(i = 0; fmt[i] != '\0'; i++) {
		if(fmt[i] == '%') {
			i++;
			switch(fmt[i]) {
				case '\0':
					sentinel("Invalid format, you ended with %%.");
					break;

				case 'd':
					out_int = va_arg(argp, int);
					rc = put_int(out_int);
					check(rc == 0, "Failed to read int.");
					break;
		
				case 'c':
					out_char = va_arg(argp, int);
					rc = fputc(out_char, stdout);
					check(rc != EOF, "Failed to write char.");
					break;

				case 's':
					out_string = va_arg(argp, char *);
					rc = fputs(out_string, stdout);
					check(rc != EOF, "Failed to write string.");
					break;

				default:
					sentinel("Invalid format.");
			}
		} else {
			fputc(fmt[i], stdout);
		}
	}

	va_end(argp);
	return 0;

error:
	va_end(argp);
	return -1;
}

int main(int argc, char *argv[])
{
	char *first_name = NULL;
	char initial = ' ';
	char *last_name = NULL;
	int age = 0;

	print_put("What's your first name? ");
	int rc = read_scan("%s", MAX_DATA, &first_name);
	check(rc == 0, "Failed first name.");
	
	print_put("What's your initial? ");
	rc = read_scan("%c\n", &initial);
	check(rc == 0, "Failed initial.");

	print_put("What's your last name? ");
	rc = read_scan("%s", MAX_DATA, &last_name);
	check(rc == 0, "Failed last name.");

	print_put("How old are you? ");
	rc = read_scan("%d", &age);

	print_put("---- RESULTS ----\n");
	print_put("First Name: %s", first_name);
	print_put("Initial: '%c'\n", initial);
	print_put("Last Name: %s", last_name);
	print_put("Age: %d\n", age);

	print_put("res: %s", "abced");

	free(first_name);
	free(last_name);
	return 0;

error:
	return -1;
}
