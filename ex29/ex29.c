#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>
#include <stdlib.h>

typedef int (*lib_function)(const char *data);
typedef int (*lib_function_cnt)(const char *data, int length);

int main(int argc, char *argv[])
{
	int rc = 0;
	check(((argc == 4) || (argc == 5)), "USAGE: ex29 libex29.so function params");

	char *lib_file = argv[1];
	char *func_to_run = argv[2];
	char *data = argv[3];
	int count = 0;
	lib_function func = NULL;
	lib_function_cnt func_cnt = NULL;

	// TODO: determine count from data, if possible
	if (argc == 5) {
		count = atoi(argv[4]);
	}

	void *lib = dlopen(lib_file, RTLD_NOW);
	check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());
	
	if(count) {
		func_cnt = dlsym(lib, func_to_run);
	} else {
		func = dlsym(lib, func_to_run);
	}

	check(((func != NULL) || (func_cnt != NULL)), "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

	rc = count ? func_cnt(data, count) : func(data);

	check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

	rc = dlclose(lib);
	check(rc == 0, "Failed to close %s", lib_file);

	return 0;

error:
	return 1;
}
