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

char *prepare(char *src)
{
	size_t i = 0;
	size_t j = 0;
	for(i = 0, j = 0; (src[j] = src[i]); j += !isspace(src[i++]));
	return src;
}

char *stepread(int length)
{
	char *res = malloc(sizeof(char) * length);
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
	res = prepare(res);
	
	return res;
}

int main(int argc, char *argv[])
{
	Person you = {.age = 0};
	int i = 0;
	char *in = NULL;

	printf("What's your First Name? ");
	char name[MAX_DATA];
	//in = fgets(you.first_name, MAX_DATA-1, stdin);
	//in = fgets(name, MAX_DATA-1, stdin);
	strcpy(name, stepread(MAX_DATA));
	//in = fscanf(stdin, "%50s", you.first_name);
	//check(in != NULL, "Failed to read first name.");
	strcpy(you.first_name, prepare(name));

	printf("What's your Last Name? ");
	//in = fgets(you.last_name, MAX_DATA-1, stdin);
	in = fgets(name, MAX_DATA-1, stdin);
	//in = gets(you.last_name);
	check(in != NULL, "Failed to read last name.");
	strcpy(you.last_name, prepare(name));

	printf("How old are you? ");
	int rc = fscanf(stdin, "%d", &you.age);
	//int rc = scanf("%d", &you.age);
	//in = fgets(aux, 5, stdin);
	check(rc > 0, "You have to enter a number.");
	//check(in != NULL, "You have to enter a number.");
	//you.age = atoi(aux);

	printf("What color are your eyes:\n");
	for(i = 0; i <= OTHER_EYES; i++) {
		printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
	}
	printf("> ");

	int eyes = -1;
	rc = fscanf(stdin, "%d", &eyes);
	//rc = scanf("%d", &eyes);
	//in = fgets(aux, 3, stdin);
	check(rc > 0, "You have to enter a number.");
	//check(in != NULL, "You have to enter a number.");
	//eyes = atoi(aux);

	you.eyes = eyes - 1;
	check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

	printf("How much do you make an hour? ");
	rc = fscanf(stdin, "%f", &you.income);
	//rc = scanf("%f", &you.income);
	//in = fgets(aux, 12, stdin);
	check(rc > 0, "Enter a floating point number.");
	//check(in != NULL, "Enter a floating point number.");
	//you.income = atof(aux);

	printf("----- RESULTS -----\n");

	printf("First Name: %s\n", you.first_name);
	printf("Last Name: %s\n", you.last_name);
	printf("Age: %d\n", you.age);
	printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
	printf("Income: %f\n", you.income);
	
	return 0;
error:
	
	return -1;
}
