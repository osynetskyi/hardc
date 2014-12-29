#include <unistd.h>

int main(int argc, char *argv[])
{
	int i = 0;
	char *ptr = "assdfsdf";

	while(i < 100) {
		if(i > 3) {
			ptr[1] = 'v';
		}
		usleep(3000);
		i++;
	}

	return 0;
}
