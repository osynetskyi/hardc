#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE = 1000;

static int THE_AGE = 37;

int get_age()
{
	return THE_AGE;
}

void set_age(int age)
{
	THE_AGE = age;
}

double update_ratio(double new_ratio)
{
	static double x = 1.0;	
	static double *ratio = &x;

	double old_ratio = *ratio;
	*ratio = new_ratio;

	return old_ratio;
}

double *update_ratio_ptr(double new_ratio)
{
	static double x = 1.0;	
	static double *ratio = &x;

	log_info("Ratio was: %f\n", *ratio);
	*ratio = new_ratio;
	
	return ratio;
}

void print_size()
{
	log_info("I think the size is: %d", THE_SIZE);
}
