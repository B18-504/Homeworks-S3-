#pragma once
using namespace std;
template <typename T>
class Sequence 
{
protected:
	int length = 0;
public:
	int GetLength() 
	{
		return length;
	} 
	void GetIsEmpty() 
	{
		if (length == 0)
			cout << "Empty sequence" << endl;
		else cout << "Not empty sequence" << endl;
	};
	virtual T Get(int index) = 0; 
	T GetFirst()
	{
		if (length == 0)
			throw ("Empty!");
		return Get(0);
	} 
	T GetLast() 
	{
		if (length == 0)
			throw ("Empty!");
		return Get(length - 1);
	}
	virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) = 0;
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(int index, T item) = 0;
	virtual void Remove(T item) = 0;
	virtual void Show() = 0;
};


