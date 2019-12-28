#pragma once

#define uint unsigned int				//need investigation about it

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

#define REQUIRE(equation, result) result.total += 1; try{bool b = (equation); result.passed += b; printf("%d %d\n", result.total, b);} catch(Exception E){printf("%d 0\n", result.total);}
#define REQUIRE_EXCEPTION(call, exc_code, result) result.total += 1; try{call; printf("%d 0\n", result.total);} catch(Exception E){bool b = (E.code == exc_code); result.passed += b; printf("%d %d\n", result.total, b);}
