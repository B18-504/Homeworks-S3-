#pragma once
#include "Sequence.h"	
template <typename T>
class ArraySequence : public Sequence<T> 
{
private:
	T* array = nullptr;
	void Extend() //Function that rellocate memory for adding/deleting objects of an array
	{
		if (this->length++ == 0) 
			array = (T*)malloc(sizeof(T));
		else array = (T*)realloc(array, sizeof(T) * (this->length + 1));
	}
public:
	T& Get(int index); //Returns a reference to an object on index place of the array
	void Append(T item); //Adds an item to the end of the array
	void Prepend(T item); //Adds an item to the start of the array
	void InsertAt(int index, T item); //Adds an item to the index place of the array
	void Show(); //Shows the array 
	ArraySequence<T>* GetSubSequence(int startIndex, int endIndex); //Returns a new array which is a subarray of the extended array
	void Remove(T item); //Removes an objects which is equals to item
};
