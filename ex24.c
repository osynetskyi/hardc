#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
	BLUE_EYES, GREEN_EYES, BROWN_EYES,
	BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
	"Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
	int age;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;
} Person;

int prepare(char *src)
{
	check_mem(src != NULL);
	size_t i = 0;
	size_t j = 0;
	for(i = 0, j = 0; (src[j] = src[i]); j += !isspace(src[i++]));
	return 0;

error:
	return -1;
}

int stepread(char *res, int length)
{
	check(length > 0, "Invalid length parameter.");
	check_mem(res != NULL);
	int i = 0;
	int last = 0;
	char cur = 'a';
	while((i < length) && (cur != '\n')) {
		scanf("%c", &cur);		
		res[i++] = cur;
	}
	if(i == length) {
		last = length - 1;
	} else {
		last = i;
	}

	res[last] = '\0';
	return 0;

error:
	return -1;
}

int main(int argc, char *argv[])
{
	Person you = {.age = 0};
	int i = 0;

	printf("What's your First Name? ");
	char *name = malloc(sizeof(char) * MAX_DATA);
	check_mem(name != NULL);
	stepread(name, MAX_DATA);
	prepare(name);
	check(name != NULL, "Failed to read first name.");
	strcpy(you.first_name, name);

	printf("What's your Last Name? ");
	stepread(name, MAX_DATA);
	prepare(name);
	check(name != NULL, "Failed to read last name.");
	strcpy(you.last_name, name);

	printf("How old are you? ");
	char *aux = malloc(sizeof(int));
	check_mem(aux != NULL);
	stepread(aux, MAX_DATA);
	check(aux != NULL, "You have to enter a number.");
	you.age = atoi(aux);

	printf("What color are your eyes:\n");
	for(i = 0; i <= OTHER_EYES; i++) {
		printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
	}
	printf("> ");

	stepread(aux, MAX_DATA);
	check(aux != NULL, "You have to enter a number.");
	you.eyes = atoi(aux) - 1;
	check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

	printf("How much do you make an hour? ");
	char *fee = malloc(sizeof(double));
	check_mem(fee);
	stepread(fee, MAX_DATA);
	check(fee != NULL, "Enter a floating point number.");
	you.income = atof(fee);

	printf("----- RESULTS -----\n");

	printf("First Name: %s\n", you.first_name);
	printf("Last Name: %s\n", you.last_name);
	printf("Age: %d\n", you.age);
	printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
	printf("Income: %f\n", you.income);

	if(name) free(name);
	if(aux) free(aux);
	if(fee) free(fee);
	
	return 0;
error:
	
	if(name) free(name);
	if(aux) free(aux);
	if(fee) free(fee);
	return -1;
}
