#include <stdio.h>
#include <stdlib.h>
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

int main(int argc, char *argv[])
{
	Person you = {.age = 0};
	int i = 0;
	char *in = NULL;

	printf("What's your First Name? ");
	in = fgets(you.first_name, MAX_DATA-1, stdin);
	//in = fscanf(stdin, "%50s", you.first_name);
	check(in != NULL, "Failed to read first name.");

	printf("What's your Last Name? ");
	in = fgets(you.last_name, MAX_DATA-1, stdin);
	//in = gets(you.last_name);
	check(in != NULL, "Failed to read last name.");

	printf("How old are you? ");
	//int rc;
	//int rc = fscanf(stdin, "%d", &you.age);
	char aux[12] = {'0'};
	in = fgets(aux, 5, stdin);
	//check(rc > 0, "You have to enter a number.");
	check(in != NULL, "You have to enter a number.");
	you.age = atoi(aux);
	printf("%p", &you.age);

	printf("What color are your eyes:\n");
	for(i = 0; i <= OTHER_EYES; i++) {
		printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
	}
	printf("> ");

	int eyes = -1;
	//rc = fscanf(stdin, "%d", &eyes);
	//char aux2[1] = "0";
	in = fgets(aux, 3, stdin);
	//check(rc > 0, "You have to enter a number.");
	check(in != NULL, "You have to enter a number.");
	eyes = atoi(aux);

	you.eyes = eyes - 1;
	check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

	printf("How much do you make an hour? ");
	//rc = fscanf(stdin, "%f", &you.income);
	//char aux2[12] = {'0'};
	in = fgets(aux, 12, stdin);
	//check(rc > 0, "Enter a floating point number.");
	check(in != NULL, "Enter a floating point number.");
	you.income = atof(aux);
	printf("%p", &you.age);

	printf("----- RESULTS -----\n");

	printf("First Name: %s", you.first_name);
	printf("Last Name: %s", you.last_name);
	printf("Age: %d\n", you.age);
	printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
	printf("Income: %f\n", you.income);
	
	return 0;
error:
	
	return -1;
}
