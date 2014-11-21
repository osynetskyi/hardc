#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
	log_info("count is: %d", count);

	if(count > 10) {
		int count = 100; // BAD! BUGS!
		
		log_info("count in this scope is %d", count);
	}

	log_info("count is at exit: %d", count);

	count = 3000;

	log_info("count after assign: %d", count);
}

unsigned long long int recursive(int num, unsigned long long int cur)
{
	if(num == 0) return cur;
	else 
		return recursive(num - 1, cur + num);
}

int main(int argc, char *argv[])
{
	// test out THE_AGE accessors
	log_info("My names: %s, age: %d", MY_NAME, get_age());

	set_age(100);

	log_info("My age is now: %d", get_age());

	// test out THE_SIZE extern
	log_info("THE_SIZE is: %d", THE_SIZE);
	print_size();

	THE_SIZE = 9;

	log_info("THE_SIZE is now: %d", THE_SIZE);
	print_size();

	// test the ration function static
	log_info("Ratio at first: %f", update_ratio(2.0));
	log_info("Ratio again: %f", update_ratio(10.0));
	log_info("Ratio once more: %f", update_ratio(300.0));

	double *res = update_ratio_ptr(2.0);
	log_info("Ratio by pointer: %f\n", *res);
	*res = 100.0;
	res = update_ratio_ptr(15.0);
	log_info("Ratio by pointer: %f\n", *res);

	// test the scope demo
	int count = 4;
	scope_demo(count);
	scope_demo(count * 20);

	log_info("count after calling scope_demo: %d", count);

	log_info("Recursive result: %llu\n", recursive(100000, 0));

	return 0;
}
