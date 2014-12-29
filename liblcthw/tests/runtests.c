#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include <string.h>

int getname(char *filename, char **name) {
	assert(filename != NULL);
	int start = strlen(filename) - 6;
	char *ptr = &filename[start];
	*name = malloc(sizeof(char) * 10);

	if(strcmp(ptr, "_tests") == 0) {
		sprintf(*name, "tests/%s", filename);	
	} else {
		*name = NULL;
	}

	return 0;
}

int dircount(char *dirname) {
	int file_count = 0;
	DIR *dirp;
	struct dirent *entry;

	dirp = opendir(dirname); /* There should be error handling after this */
	while ((entry = readdir(dirp)) != NULL) {
  	  if (entry->d_type == DT_REG) {
 	        file_count++;
	    }
	}
	closedir(dirp);

	return file_count;
}

int main(int argc, char *argv[]) {
	
	char directory[] = "tests/";
	char *res = NULL;
	char buf[50];
	printf("Running unit tests: \n");

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (directory)) != NULL) {
  		while ((ent = readdir (dir)) != NULL) {
			res = NULL;
			getname(ent->d_name, &res);
			if (res != NULL) {
				sprintf(buf, "valgrind ./%s 2>> tests/tests.log", res);
				int k = system(buf);
				if(k == 0) {
					printf("%s PASS\n", res);
				} else {
					printf("ERROR in test %s: here's tests/tests.log\n", res);
					printf("------\n");
					system("tail tests/tests.log");
				}
			}
  		}
  	closedir (dir);
	} else {
  		perror ("");
  		return -1;
	}

	free(res);
	return 0;
}
