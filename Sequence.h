#pragma once
using namespace std;
template <typename T>
class Sequence
{
protected:
	int length = 0;
public:
	int GetLength(); //Returns length of the sequence
	void GetIsEmpty(); //Checks if the sequence is empty
	virtual T& Get(int index) = 0; //Returns a reference to an object on index place of the sequence
	T GetFirst(); //Returns first element of the sequence
	T GetLast(); //Returns last element of the sequence
	virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) = 0; //Returns a new array which is a subarray of the extended sequence
	virtual void Append(T item) = 0; //Adds an item to the end of the sequence
	virtual void Prepend(T item) = 0; //Adds an item to the start of the sequence
	virtual void InsertAt(int index, T item) = 0; //Adds an item to the index place of the sequence
	virtual void Remove(T item) = 0; //Removes an objects which is equals to item
	virtual void Show() = 0; //Shows the sequence 
};


