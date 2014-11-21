#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <wchar.h>
#include <wctype.h>

#ifndef __CONCAT
#define __CONCATenate(left, right) left ## right
#define __CONCAT(left, right) __CONCATenate(left, right)
#endif

int main(int argc, char *argv[])
{
	printf("Size of int32_t: %d\n", sizeof(int32_t));
	printf("Size of uint32_t: %d\n", sizeof(uint32_t));
	printf("Size of short int : %d\n", sizeof(short int));
	printf("Size of long: %d\n", sizeof(long));
	printf("Size of long long: %d\n", sizeof(long long));
	printf("Size of int64_t: %d\n", sizeof(int64_t));
	printf("Size of intptr_t: %d\n", sizeof(intptr_t));
	printf("Size of int_least16_t: %d\n", sizeof(int_least16_t));
	printf("Size of int_fast64_t: %d\n", sizeof(int_fast64_t));
	printf("Size of wchar_t: %d\n", sizeof(wchar_t));
	printf("Size of wint_t: %d\n", sizeof(wint_t));
	printf("Max int (intmax_t): %d\n", sizeof(intmax_t));
	printf("Max int (sig_atomic_t): %d\n", sizeof(sig_atomic_t));
	printf("Max intptr_max: %d\n", INTPTR_MAX);
	printf("Max int64_max: %lld\n", INT64_MAX);
	printf("Min int64_min: %lld\n", INT64_MIN);
	printf("Max uint32_max: %u\n", UINT32_MAX);
	printf("Max uint64_max: %llu\n", UINT64_MAX);
	printf("Largest number ever: %llu\n", UINTMAX_MAX);
	printf("Smallest number ever: %lld\n", INTMAX_MIN);

	return 0;
}
