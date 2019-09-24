#include <iostream>
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
using namespace std;

int main() {

	ArraySequence<int> intArSeq;
	Sequence<int>* intSeq = &intArSeq;

	cout << "Length: " << intSeq->GetLength() << endl;

	intSeq->Append(23);

	cout << "Length: " << intSeq->GetLength() << endl;
	cout << "First element: " << intSeq->GetFirst() << endl;
	cout << "Last element: " << intSeq->GetLast() << endl;
	cout << "Element with index 0: " << intSeq->Get(0) << endl;
	//cout << "Element with index -1: " << intSeq->Get(-1) << endl;
	//cout << "Element with index 1: " << intSeq->Get(1) << endl;

	intSeq->Append(43);

	cout << "Length: " << intSeq->GetLength() << endl;
	cout << "First element: " << intSeq->GetFirst() << endl;
	cout << "Last element: " << intSeq->GetLast() << endl;
	cout << "Element with index 0: " << intSeq->Get(0) << endl;
	cout << "Element with index 1: " << intSeq->Get(1) << endl;
	//cout << "Element with index -1: " << intSeq->Get(-1) << endl;
	//cout << "Element with index 2: " << intSeq->Get(2) << endl;

	intSeq->Prepend(53);

	cout << "Length: " << intSeq->GetLength() << endl;
	cout << "First element: " << intSeq->GetFirst() << endl;
	cout << "Last element: " << intSeq->GetLast() << endl;
	cout << "Element with index 0: " << intSeq->Get(0) << endl;
	cout << "Element with index 1: " << intSeq->Get(1) << endl;
	//cout << "Element with index -1: " << intSeq->Get(-1) << endl;
	//cout << "Element with index 3: " << intSeq->Get(3) << endl;

	Sequence<int>* intSubSeq = intSeq->GetSubSequence(1,1);

	cout << "Length: " << intSubSeq->GetLength() << endl;
	cout << "First element: " << intSubSeq->GetFirst() << endl;
	cout << "Last element: " << intSubSeq->GetLast() << endl;

	//ArraySequence<int> iarray;
	//iarray.Append(1);
	//iarray.Append(2);
	//iarray.Append(3);
	//iarray.Append(4);
	//iarray.Prepend(0);
	//iarray.Prepend(-1);
	//iarray.InsertAt(2, 123);
	//iarray.InsertAt(5, 123);
	//iarray.Show();
	//cout << endl;
	//cout << iarray.Get(3) << endl;
	//cout << iarray.GetFirst() << endl;
	//cout << iarray.GetLast() << endl;
	//ArraySequence<int> iarray1 = iarray.GetSubSequence(2,6);
	//iarray1.Show();
	//cout << endl;
	//iarray.Remove(123);
	//iarray1.Remove(123);
	//iarray.Show();
	//cout << endl;
	//iarray1.Show();

	//ListSequence<int> ilist;
	//ilist.Append(1);
	//ilist.Append(2);
	//ilist.Append(3);
	//ilist.Append(4);
	//ilist.Prepend(0);
	//ilist.Prepend(-1);
	//ilist.InsertAt(5, 12);
	//ilist.InsertAt(1, 12);
	//ilist.Show();
	//cout << endl;
	////cout << ilist.GetFirst() << endl << ilist.GetLast() << endl;
	//ListSequence<int> ilist1 = ilist.GetSubSequence(1,6);
	//ilist.Remove(12);
	//ilist.Show();
	//cout << endl;
	//ilist1.Show();
	//ilist1.Remove(12);
	//cout << endl;
	//ilist1.Show();
	//cout << endl;
	//cout << ilist1.Get(2) << endl;
	//cout << ilist.GetLength() << endl << ilist1.GetLength() << endl;


	system("pause");
	return 0;
}

