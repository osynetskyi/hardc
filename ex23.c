#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include <time.h>

#define mCP() *to++ = *from++

#define m7DUFF(start) case start:   mCP(); \
					  case start-1: mCP(); \
					  case start-2: mCP(); \
					  case start-3: mCP(); \
					  case start-4: mCP(); \
					  case start-5: mCP(); \
					  case start-6: mCP(); \

#define m32DUFF(start) 	mCP(); \
						m7DUFF(start-1); \
						case start-8: mCP(); \
						m7DUFF(start-9); \
						case start-16: mCP(); \
						m7DUFF(start-17); \
						case start-24: mCP(); \
						m7DUFF(start-25);


int normal_copy(char *from, char *to, int count)
{
	int i = 0;

	for(i = 0; i < count; i++) {
		to[i] = from[i];
	}

	return i;
}

int duffs_device(char *from, char *to, int count) 
{
	{
		int n = (count + 7) / 8;

		switch(count % 8) {
			case 0: do { *to++ = *from++;
						m7DUFF(7);
						/*case 7: *to++ = *from++;
						case 6: *to++ = *from++;
						case 5: *to++ = *from++;
						case 4: *to++ = *from++;
						case 3: *to++ = *from++;
						case 2: *to++ = *from++;
						case 1: *to++ = *from++;*/
					} while(--n > 0);
		}
	}
	
	return count;
}

int duff_32(char *from, char* to, int count)
{
	{
		int n = (count + 31) / 32;

		switch(count % 32) {
			case 0: do { 
						m32DUFF(32);
					} while(--n > 0);
		}
	}
	
	return count;
}

int zeds_device(char *from, char *to, int count)
{
	{
		int n = (count + 7) / 8;

		switch(count % 8) {
			case 0:
			again: *to++ = *from++;

			case 7: *to++ = *from++;
			case 6: *to++ = *from++;
			case 5: *to++ = *from++;
			case 4: *to++ = *from++;
			case 3: *to++ = *from++;
			case 2: *to++ = *from++;
			case 1: *to++ = *from++;
					if(--n > 0) goto again;
		}
	}

	return count;
}

int valid_copy(char *data, int count, char expects)
{
	int i = 0;
	for(i = 0; i < count; i++) {
		if(data[i] != expects) {
			log_err("[%d] %c != %c", i, data[i], expects);
			return 0;
		}	
	}

	return 1;
}

int main(int argc, char *argv[])
{
	char from[1000] = {'a'};
	char to[1000] = {'c'};
	int rc = 0;
	struct timespec start, end;

	// setup the from to have some stuff
	/*memset(from, 'y', 1000);
	clock_gettime(CLOCK_REALTIME, &start);	
	memmove(from, to, 1000);
	clock_gettime(CLOCK_REALTIME, &end); 
	printf("memcpy: %f\n", (double)(end.tv_nsec - start.tv_nsec));*/
	memset(from, 'x', 1000);
	// set it to a failure mode
	memset(to, 'y', 1000);
	check(valid_copy(to, 1000, 'y'), "Not initialized right.");

	// use normal copy to
	clock_gettime(CLOCK_REALTIME, &start); 
	rc = normal_copy(from, to, 1000);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("%f ", (double)(end.tv_nsec - start.tv_nsec));
	check(rc == 1000, "Normal copy failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Normal copy failed.");

	// reset
	memset(to, 'y', 1000);

	// duffs version
	clock_gettime(CLOCK_REALTIME, &start);
	rc = duffs_device(from, to, 1000);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("%f ", (double)(end.tv_nsec - start.tv_nsec));
	check(rc == 1000, "Duff's device failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Duff's device failed copy.");

	// duff_32 version
	clock_gettime(CLOCK_REALTIME, &start);
	rc = duff_32(from, to, 1000);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("%f ", (double)(end.tv_nsec - start.tv_nsec));
	check(rc == 1000, "Duff_32 failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Duff_32 failed copy.");

	// reset
	memset(to, 'y', 1000);

	// my version
	clock_gettime(CLOCK_REALTIME, &start);
	rc = zeds_device(from, to, 1000);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("%f\n", (double)(end.tv_nsec - start.tv_nsec));
	check(rc == 1000, "Zed's device failed: %d", rc);
	check(valid_copy(to, 1000, 'x'), "Zed's device failed copy.");

	return 0;
error:
	return 1;	
}
