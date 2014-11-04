#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// go throug each string in argv
	int i = argc;
	while(i > 0) {
		printf("arg %d: %s\n", i, argv[argc-i]);
		i--;
	}

	// let's make our own array of strings
	char *states[] = {
		"California", "Oregon",
		"Washington", "Texas"
	};

	int num_states = 4;
	/*i = 0;
	while((i < argc)&&(i < num_states)) {
		states[i] = argv[i];
		i++;
	}*/

	i = 0; // watch for this
	while(i < num_states) {
		if(states[i] == "Texas") {
			break;
		}
		printf("state %d: %s\n", i, states[i]);
		i++;
	}

	return 0;
}
