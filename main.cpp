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

	system("pause");
	return 0;
}

