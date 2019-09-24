#pragma once
#include "Sequence.h"	

template <typename T>
class ArraySequence : public Sequence<T> 
{
private:
	T* array = nullptr;
	void Extend()
	{
		if (this->length++ == 0) 
			array = (T*)malloc(sizeof(T));
		else array = (T*)realloc(array, sizeof(T) * (this->length + 1));
	}
public:
	T Get(int index)  
	{
			if (index > this->length)
				throw "Out of array size";
			if (index < 0)
				throw "Negative input index";
		return array[index];
	}
	void Append(T item) 
	{
		Extend();
		array[this->length - 1] = item;
	}
	void Prepend(T item) 
	{
		Extend();
		for (int i = this->length; i > 0; i--)
			array[i] = array[i - 1];
		array[0] = item;
	}
	void InsertAt(int index, T item) 
	{
		Extend();
		if (index > this->length)
			throw("Out of array size");
		for (int i = this->length; i > index - 1; i--)
			array[i + 1] = array[i];
		array[index] = item;
	}
	void Show()
	{
		if (this->length == 0)
			std::cout << "Empty array" << endl;
		else
		{
			for (int i = 0; i < this->length; i++)
				std::cout << array[i] << " ";
		}
	}
	ArraySequence<T>* GetSubSequence(int startIndex, int endIndex)
	{
		if (endIndex < startIndex)
			std::swap(endIndex, startIndex);
		if (endIndex >= this->length)
			throw("Out of array size");
		ArraySequence<T>* newArray = new ArraySequence<T>;
		newArray->length = 0;
		for (int i = startIndex; i <= endIndex; i++)
			newArray->Append(this->Get(i));
		return newArray;
	}
	void Remove(T item)
	{
		int i = 0, j = 0;
		while (j < this->length)
		{
			for (i; i < this->length; i++)
				if (Get(i) == item)
					break;
			j = i;
			if (i < this->length)
			{
				for (i; i < this->length; i++)
					array[i] = array[i + 1];
				this->length--;
			}
			i = j;
		}
	}
};
