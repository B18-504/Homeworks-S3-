#pragma once
#include "Sequence.h"
template <typename T>
class ListSequence : public Sequence<T> 
{
private:
	struct Node 
	{
		T data;
		Node* next;
	};
	Node* head = nullptr, *tail = nullptr;
public:
	T& Get(int index); //Returns a reference to an object on index place of the list
	void Append(T item); //Adds an item to the end of the list
	void Prepend(T item); //Adds an item to the start of the list
	void InsertAt(int index, T item); //Adds an item to the index place of the list
	void Show(); //Shows the list 
	ListSequence<T>* GetSubSequence(int startIndex, int endIndex); //Returns a new list which is a sublist of the extended list
	void Remove(T item); //Removes an objects which is equals to item
};
