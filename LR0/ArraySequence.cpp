#include <iostream>
#include "ArraySequence.h"
using namespace std;

//Returns a reference to an object on index place of the array
template <typename T>
T& ArraySequence<T>::Get(int index)
{
	if (index >= ArraySequence<T>::length)
		throw "Error: Out of array size";
	if (index < 0) 
		throw "Error: Negative input index";
	return array[index];
}

//Adds an item to the end of the array
template <typename T>
void ArraySequence<T>::Append(T item)
{
	ArraySequence<T>::Extend();
	array[ArraySequence<T>::length - 1] = item;
}

//Adds an item to the start of the array
template <typename T>
void ArraySequence<T>::Prepend(T item)
{
	ArraySequence<T>::Extend();
	for (int i = ArraySequence<T>::length; i > 0; i--)
		array[i] = array[i - 1];
	array[0] = item;
}

//Adds an item to the index place of the array
template <typename T>
void ArraySequence<T>::InsertAt(int index, T item)
{
	ArraySequence<T>::Extend();
	if (index > ArraySequence<T>::length)
		throw "Error: Out of array size";
	for (int i = ArraySequence<T>::length; i > index - 1; i--)
		array[i + 1] = array[i];
	array[index] = item;
}

//Shows the array
template <typename T>
void ArraySequence<T>::Show()
{
	if (ArraySequence<T>::length == 0)
		cout << "Empty array" << endl;
	else
	{
		for (int i = 0; i < ArraySequence<T>::length; i++)
			cout << array[i] << " ";
	}
}

//Returns a new array which is a subarray of the extended array
template <typename T>
ArraySequence<T>* ArraySequence<T>::GetSubSequence(int startIndex, int endIndex)
{
	if (endIndex < startIndex)
		swap(endIndex, startIndex);
	if (endIndex >= ArraySequence<T>::length)
		throw "Error: Out of array size";
	ArraySequence<T>* newArray = new ArraySequence<T>;
	newArray->length = 0;
	for (int i = startIndex; i <= endIndex; i++)
		newArray->Append(Get(i));
	return newArray;
}

//Removes an objects which is equals to item
template <typename T>
void ArraySequence<T>::Remove(T item)
{
	int i = 0, j = 0;
	while (j < ArraySequence<T>::length)
	{
		for (i; i < ArraySequence<T>::length; i++)
			if (Get(i) == item)
				break;
		j = i;
		if (i < ArraySequence<T>::length)
		{
			for (i; i < ArraySequence<T>::length; i++)
				array[i] = array[i + 1];
			(ArraySequence<T>::length)--;
		}
		i = j;
	}
}
