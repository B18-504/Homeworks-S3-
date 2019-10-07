#pragma once

struct Result
{
	uint total;
	uint passed;
};

void tell(Result &r)
{
	printf("Passed %u call tests of %u\nStatus: ", r.passed, r.total);
	if(r.passed == r.total)
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
}

#define REQUIRE(equation, result) result.total += 1; try{result.passed += (equation);} catch(Exception E){}
#define REQUIRE_EXCEPTION(call, exc_code, result) result.total += 1; try{call;} catch(Exception E){result.passed += (E.code == exc_code);}
