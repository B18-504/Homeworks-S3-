#pragma once

#include "TestMacro.h"

void TestSequence()
{
	Result res;
	res.passed = 0;
	res.total = 0;
	
	Sequence<int> *arr = new ArraySequence<int>;
	Sequence<int> *list = new ListSequence<int>;
	
	REQUIRE(arr->GetLen() == 0, res);//1
	REQUIRE(list->GetLen() == 0, res);//2

	arr->Append(*new int(23));
	list->Append(*new int(23));
	
	REQUIRE(arr->GetLen() == 1, res);//3
	REQUIRE(list->GetLen() == 1, res);//4
	
	REQUIRE(arr->GetFirst() == 23, res);//5
	REQUIRE(arr->GetLast() == 23, res);//6
	
	REQUIRE(list->GetFirst() == 23, res);//7
	REQUIRE(list->GetLast() == 23, res);//8
	
	REQUIRE((*arr)[0] == 23, res);//9
	REQUIRE((*list)[0] == 23, res);//10
	
	REQUIRE_EXCEPTION((*arr)[1], 0x12, res);//11
	REQUIRE_EXCEPTION((*list)[1], 0x12, res);//12

	arr->Append(*new int(43));
	list->Append(*new int(43));
	
	REQUIRE(arr->GetLen() == 2, res);//13
	REQUIRE(list->GetLen() == 2, res);//14
	
	REQUIRE(arr->GetFirst() == 23, res);//15
	REQUIRE(arr->GetLast() == 43, res);//16
	
	REQUIRE(list->GetFirst() == 23, res);//17
	REQUIRE(list->GetLast() == 43, res);//18
	
	REQUIRE((*arr)[0] == 23, res);//19
	REQUIRE((*list)[0] == 23, res);//20
	
	REQUIRE((*arr)[1] == 43, res);//21
	REQUIRE((*list)[1] == 43, res);//22
	
	REQUIRE_EXCEPTION((*arr)[2], 0x12, res);//23
	REQUIRE_EXCEPTION((*list)[2], 0x12, res);//24

	arr->Prepend(*new int(53));
	list->Prepend(*new int(53));
	
	REQUIRE(arr->GetLen() == 3, res);//25
	REQUIRE(list->GetLen() == 3, res);//26
	
	REQUIRE(arr->GetFirst() == 53, res);//27
	REQUIRE(arr->GetLast() == 43, res);//28
	
	REQUIRE(list->GetFirst() == 53, res);//29
	REQUIRE(list->GetLast() == 43, res);//30
	
	REQUIRE((((*arr)[0])) == 53, res);//31
	REQUIRE((((*list)[0])) == 53, res);//32
	
	REQUIRE((((*arr)[1])) == 23, res);//33
	REQUIRE((((*list)[1])) == 23, res);//34
	
	REQUIRE((((*arr)[2])) == 43, res);//35
	REQUIRE((((*list)[2])) == 43, res);//36
	
	REQUIRE_EXCEPTION((*arr)[3], 0x12, res);//37
	REQUIRE_EXCEPTION((*list)[3], 0x12, res);//38
	
	Sequence<int> *a1 = arr->GetSubS(1, 1);
	Sequence<int> *l1 = list->GetSubS(1, 1);
	
	REQUIRE(a1->GetLen() == 1, res);
	REQUIRE(l1->GetLen() == 1, res);
	
	REQUIRE(a1->GetFirst() == 23, res);//39
	REQUIRE(a1->GetLast() == 23, res);//40
	
	REQUIRE(l1->GetFirst() == 23, res);//41
	REQUIRE(l1->GetLast() == 23, res);//42
	
	tell(res);
}
