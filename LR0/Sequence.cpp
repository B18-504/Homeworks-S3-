#include <iostream>
#include "Sequence.h"
using namespace std;

//Returns length of the sequence
template <typename T>
int Sequence<T>::GetLength()
{
	return Sequence<T>::length;
}

//Checks if the sequence is empty
template <typename T>
void Sequence<T>::GetIsEmpty()
{
	if (Sequence<T>::length == 0)
		cout << "Empty sequence" << endl;
	else cout << "Not empty sequence" << endl;
};

//Returns first element of the sequence
template <typename T>
T Sequence<T>::GetFirst()
{
	if (Sequence<T>::length == 0)
		throw ("Error: The sequence is empty");
	return Get(0);
}

//Returns last element of the sequence
template <typename T>
T Sequence<T>::GetLast()
{
	if (Sequence<T>::length == 0)
		throw ("Error: The sequence is empty");
	return Get(Sequence<T>::length - 1);
}