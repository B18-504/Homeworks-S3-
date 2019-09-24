#include "RealFunctions.cpp"

void dupi(void **argv)
{
	dup(*(int*)(*argv));
}

void dupd(void **argv)
{
	dup(*(double*)(*argv));
}

void inpi(void **argv)
{
	input(*(int*)(*argv));
}

void inpd(void **argv)
{
	input(*(double*)(*argv));
}

void printi(void **argv)
{
	print(*(int*)(*argv));
}

void printd(void **argv)
{
	print(*(double*)(*argv));
}
