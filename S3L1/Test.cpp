#pragma once

#include "TestMacro.h"

void TestSequence()
{
	Result res;
	res.passed = 0;
	res.total = 0;
	
	Sequence<Number> *arr = new ArraySequence<Number>;
	Sequence<Number> *list = new ListSequence<Number>;
	
	REQUIRE(arr->GetLen() == 0, res);//1
	REQUIRE(list->GetLen() == 0, res);//2
	
	Int a = *new Int(23);
	
	arr->Append(&a);
	list->Append(&a);
	
	REQUIRE(arr->GetLen() == 1, res);//3
	REQUIRE(list->GetLen() == 1, res);//4
	
	REQUIRE(((Int*)(arr->GetFirst()))->body == 23, res);//5
	REQUIRE(((Int*)(arr->GetLast()))->body == 23, res);//6
	
	REQUIRE(((Int*)(list->GetFirst()))->body == 23, res);//7
	REQUIRE(((Int*)(list->GetLast()))->body == 23, res);//8
	
	REQUIRE(((Int*)((*arr)[0]))->body == 23, res);//9
	REQUIRE(((Int*)((*list)[0]))->body == 23, res);//10
	
	REQUIRE_EXCEPTION((*arr)[1], 0x12, res);//11
	REQUIRE_EXCEPTION((*list)[1], 0x12, res);//12
	
	a.body = 43;
	
	arr->Append(&a);
	list->Append(&a);
	
	REQUIRE(arr->GetLen() == 2, res);//13
	REQUIRE(list->GetLen() == 2, res);//14
	
	REQUIRE(((Int*)(arr->GetFirst()))->body == 23, res);//15
	REQUIRE(((Int*)(arr->GetLast()))->body == 43, res);//16
	
	REQUIRE(((Int*)(list->GetFirst()))->body == 23, res);//17
	REQUIRE(((Int*)(list->GetLast()))->body == 43, res);//18
	
	REQUIRE(((Int*)((*arr)[0]))->body == 23, res);//19
	REQUIRE(((Int*)((*list)[0]))->body == 23, res);//20
	
	REQUIRE(((Int*)((*arr)[1]))->body == 43, res);//21
	REQUIRE(((Int*)((*list)[1]))->body == 43, res);//22
	
	REQUIRE_EXCEPTION((*arr)[2], 0x12, res);//23
	REQUIRE_EXCEPTION((*list)[2], 0x12, res);//24
	
	a.body = 53;
	
	arr->Prepend(&a);
	list->Prepend(&a);
	
	REQUIRE(arr->GetLen() == 3, res);//25
	REQUIRE(list->GetLen() == 3, res);//26
	
	REQUIRE(((Int*)(arr->GetFirst()))->body == 53, res);//27
	REQUIRE(((Int*)(arr->GetLast()))->body == 43, res);//28
	
	REQUIRE(((Int*)(list->GetFirst()))->body == 53, res);//29
	REQUIRE(((Int*)(list->GetLast()))->body == 43, res);//30
	
	REQUIRE(((Int*)((*arr)[0]))->body == 53, res);//31
	REQUIRE(((Int*)((*list)[0]))->body == 53, res);//32
	
	REQUIRE(((Int*)((*arr)[1]))->body == 23, res);//33
	REQUIRE(((Int*)((*list)[1]))->body == 23, res);//34
	
	REQUIRE(((Int*)((*arr)[2]))->body == 43, res);//35
	REQUIRE(((Int*)((*list)[2]))->body == 43, res);//36
	
	REQUIRE_EXCEPTION((*arr)[3], 0x12, res);//37
	REQUIRE_EXCEPTION((*list)[3], 0x12, res);//38
	
	Sequence<Number> *a1 = arr->GetSubS(1, 1);
	Sequence<Number> *l1 = list->GetSubS(1, 1);
	
	REQUIRE(a1->GetLen() == 1, res);
	REQUIRE(l1->GetLen() == 1, res);
	
	REQUIRE(((Int*)(a1->GetFirst()))->body == 23, res);//39
	REQUIRE(((Int*)(a1->GetLast()))->body == 23, res);//40
	
	REQUIRE(((Int*)(l1->GetFirst()))->body == 23, res);//41
	REQUIRE(((Int*)(l1->GetLast()))->body == 23, res);//42
	
	tell(res);
}
