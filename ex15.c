#include <stdio.h>

void print2(char **name, int *age, int count)
{
	int i = 0;
	while(i < count) {
		printf("%s is %d years old.\n",
				name[i], age[i]);
		i++;
	}
}

int main(int argc, char *argv[])
{
	// create two arrays we care about
	int ages[] = {23, 43, 12, 89, 2};
	char *names[] = {
		"Alan", "Frank",
		"Mary", "John", "Lisa"
	};

	// safely get the size of ages
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	// setup the pointers to the start of the arrays
	//int *cur_age = &ages[count-1];
	int *cur_age = ages;
	//int *cur_age = (int *)names;
	//char **cur_name = &names[count-1];
	char **cur_name = names;

	// first way using indexing
	for(i = 0; i < count; i++) {
		printf("%s has %d years alive.\n",
				names[i], ages[i]);
	}

	printf("---\n");

	// second way using pointers
	/*for(i = 0; i < count; i++) {
		printf("%s is %d years old.\n",
				*(cur_name-i), *(cur_age-i));
	}*/
	print2(cur_name, cur_age, count);

	printf("---\n");

	//third way, pointers are just arrays
	for(i = 0; i < count; i++) {
		printf("%s id %d years old again.\n",
				cur_name[i], cur_age[i]);
	}

	printf("---\n");

	// fourth way with pointers in a stupid complex way
	for(cur_name = &names[count-1], cur_age = &ages[count-1];
			(cur_age - ages) > -1;
			//(ages - cur_age) < count;
			cur_name--, cur_age--)
	{
		printf("%s lived %d years so far.\n",
				*cur_name, *cur_age);
	}
	
	/*char bar[128];
	printf("%d\n", strlen(bar));
	//printf("%d\n", bar[1]);
	char *blah = "fizzbuzz";
	printf("%s\n", blah+4);
	printf("%d\n", strlen(blah));
	printf("%p\n", blah+4);

	char  bar[128];
	char  *baz = &bar[0];
	//baz[127] = 0;
	printf("%d\n", strlen(baz));*/
	
	/*cur_name = names;
	cur_age = ages;
	for(i = 0; i < count; i++) {
		printf("Ptr_name : %p\nPtr_age: %p\n",
				*(cur_name+i), *(cur_age+i));
	}*/

	return 0;
}
