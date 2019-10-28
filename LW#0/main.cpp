#include <iostream>
#include "listSequence.cpp"
#include "arraySequence.cpp"
#include "Test.h"

int main()
{
	Result res;
	res.passed = 0;
	res.total = 0;

	Sequence<int>* arr = new arraySequence<int>;
	Sequence<int>* list = new listSequence<int>;

	REQUIRE(arr->GetLength() == 0, res); 
	REQUIRE(list->GetLength() == 0, res); 

	REQUIRE_EXCEPTION(arr->GetFirst(), containerIsEmpty, res);
	REQUIRE_EXCEPTION(arr->GetLast(), containerIsEmpty, res);

	REQUIRE_EXCEPTION(list->GetFirst(), containerIsEmpty, res);
	REQUIRE_EXCEPTION(list->GetLast(), containerIsEmpty, res);

	int a = 12;

	arr->Append(a);
	list->Append(a);

	REQUIRE(arr->GetLength() == 1, res);
	REQUIRE(list->GetLength() == 1, res);

	REQUIRE(arr->GetFirst() == 12, res);
	REQUIRE(arr->GetLast() == 12, res);

	REQUIRE(list->GetFirst() == 12, res);
	REQUIRE(list->GetLast() == 12, res);

	REQUIRE(list->get(0) == 12, res);
	REQUIRE(arr->get(0) == 12, res);

	REQUIRE_EXCEPTION(arr->get(-1), outOfRange, res);
	REQUIRE_EXCEPTION(arr->get(1), outOfRange, res);

	REQUIRE_EXCEPTION(list->get(-1), outOfRange, res);
	REQUIRE_EXCEPTION(list->get(1), outOfRange, res);

	a = 43;

	arr->Append(a);
	list->Append(a);

	REQUIRE(arr->GetLength() == 2, res); 
	REQUIRE(list->GetLength() == 2, res); 

	REQUIRE(arr->GetFirst() == 12, res); 
	REQUIRE(arr->GetLast() == 43, res);

	REQUIRE(list->GetFirst() == 12, res);
	REQUIRE(list->GetLast() == 43, res);

	REQUIRE(arr->get(0) == 12, res); 
	REQUIRE(arr->get(1) == 43, res);

	REQUIRE(list->get(0) == 12, res);
	REQUIRE(list->get(1) == 43, res);

	REQUIRE_EXCEPTION(arr->get(-1), outOfRange, res);
	REQUIRE_EXCEPTION(arr->get(2), outOfRange, res);

	REQUIRE_EXCEPTION(list->get(-1), outOfRange, res);
	REQUIRE_EXCEPTION(list->get(2), outOfRange, res);

	a = 53;

	arr->Prepend(a);
	list->Prepend(a);

	REQUIRE(arr->GetLength() == 3, res);
	REQUIRE(list->GetLength() == 3, res);

	REQUIRE(arr->GetFirst() == 53, res);
	REQUIRE(arr->GetLast() == 43, res);

	REQUIRE(list->GetFirst() == 53, res);
	REQUIRE(list->GetLast() == 43, res);

	REQUIRE(arr->get(0) == 53, res);
	REQUIRE(arr->get(1) == 12, res);

	REQUIRE(list->get(0) == 53, res);
	REQUIRE(list->get(1) == 12, res);

	REQUIRE_EXCEPTION(arr->get(-1), outOfRange, res);
	REQUIRE_EXCEPTION(arr->get(3), outOfRange, res);

	REQUIRE_EXCEPTION(list->get(-1), outOfRange, res);
	REQUIRE_EXCEPTION(list->get(3), outOfRange, res);

	Sequence<int>* a1 = arr->GetSubsequence(1, 1);
	Sequence<int>* l1 = list->GetSubsequence(1, 1);

	REQUIRE(a1->GetLength() == 1, res);
	REQUIRE(l1->GetLength() == 1, res);

	REQUIRE(a1->GetFirst() == 12, res);
	REQUIRE(a1->GetLast() == 12, res);

	REQUIRE(l1->GetFirst() == 12, res);
	REQUIRE(l1->GetLast() == 12, res);

	tell(res);

}