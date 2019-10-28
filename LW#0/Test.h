#pragma once
#ifndef Test_h
#define Test_h

#include "exception.h"

struct Result
{
	int total;
	int passed;
};

void tell(Result& r)
{
	printf("Passed %u call tests of %u\nStatus: ", r.passed, r.total);
	if (r.passed == r.total)
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
}

#define REQUIRE(equation, result) result.total += 1; try{result.passed += (equation);} catch(int){throw errorInTest();}
#define REQUIRE_EXCEPTION(call, exception, result) result.total += 1; try{call;} catch(exception){result.passed += 1;}

#endif
