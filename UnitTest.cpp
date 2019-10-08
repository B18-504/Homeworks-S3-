#include <iostream>
#include "Sequence.cpp"
#include "ArraySequence.cpp"
#include "ListSequence.cpp"
using namespace std;

inline void UnitTest()
{
	ArraySequence<int> intArSeq;
	Sequence<int>* intSeq = &intArSeq;

	cout << "Length: " << intSeq->GetLength() << endl;

	intSeq->Append(23);

	cout << "Length: " << intSeq->GetLength() << endl;
	cout << "First element: " << intSeq->GetFirst() << endl;
	cout << "Last element: " << intSeq->GetLast() << endl;
	cout << "Element with index 0: " << intSeq->Get(0) << endl;
	try
	{
		cout << "Element with index -1: ";
		cout << intSeq->Get(-1) << endl;
	}
	catch (const char e[])
	{
		cout << endl << e << endl;
	}
	try
	{
		cout << "Element with index 1: ";
		cout << intSeq->Get(1) << endl;
	}
	catch (const char e[])
	{
		cout << endl << e << endl;
	}
	

	intSeq->Append(43);

	cout << "Length: " << intSeq->GetLength() << endl;
	cout << "First element: " << intSeq->GetFirst() << endl;
	cout << "Last element: " << intSeq->GetLast() << endl;
	cout << "Element with index 0: " << intSeq->Get(0) << endl;
	cout << "Element with index 1: " << intSeq->Get(1) << endl;
	try
	{
		cout << "Element with index -1: ";
		cout << intSeq->Get(-1) << endl;
	}
	catch (const char e[])
	{
		cout << endl << e << endl;
	}
	try
	{
		cout << "Element with index 2: ";
		cout << intSeq->Get(2) << endl;
	}
	catch (const char e[])
	{
		cout << endl << e << endl;
	}


	intSeq->Prepend(53);

	cout << "Length: " << intSeq->GetLength() << endl;
	cout << "First element: " << intSeq->GetFirst() << endl;
	cout << "Last element: " << intSeq->GetLast() << endl;
	cout << "Element with index 0: " << intSeq->Get(0) << endl;
	cout << "Element with index 1: " << intSeq->Get(1) << endl;
	try
	{
		cout << "Element with index -1: ";
		cout << intSeq->Get(-1) << endl;
	}
	catch (const char e[])
	{
		cout << endl << e << endl;
	}
	try
	{
		cout << "Element with index 3: ";
		cout << intSeq->Get(3) << endl;
	}
	catch (const char e[])
	{
		cout << endl << e << endl;
	}


	Sequence<int>* intSubSeq = intSeq->GetSubSequence(1, 1);

	cout << "Length: " << intSubSeq->GetLength() << endl;
	cout << "First element: " << intSubSeq->GetFirst() << endl;
	cout << "Last element: " << intSubSeq->GetLast() << endl;
}