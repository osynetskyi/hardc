#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc < 2) {
		printf("ERROR: You need one or more arguments.\n");
		// this is how you abort a program
		return 1;
	}
	//printf("%c %d\n", 'A' + 32, 'Z');
	int j = 1;
	char **cur_arg = argv;

	for(j = 1; j < argc; j++) {

		int i = 0;
		for(i = -1; i++, *(*(cur_arg+j)+i) != '\0';) {
			char letter = *(*(cur_arg+j)+i);
	
			if((letter > 64) && (letter < 91)) {
				letter += 32;
			}
			
			switch(letter) {
				case 'a':
				//case 'A':
					printf("%d: 'A'\n", i);
					break;
	
				case 'e':
				//case 'E':
					printf("%d: 'E'\n", i);
					break;

				case 'i':
				//case 'I':
					printf("%d: 'I'\n", i);
					break;

				case 'o':
				//case 'O':
					printf("%d: 'O'\n", i);
					break;

				case 'u':
				//case 'U':
					printf("%d: 'U'\n", i);
					break;

				case 'y':
				//case 'Y':
					if(i > 2) {
						// it's only sometimes Y
						printf("%d: 'Y'\n", i);
						//break;
					}
					break;

				default:
					printf("%d: %c is not a vowel.\n", i, letter);
			}
		}
	}

	return 0;
}
