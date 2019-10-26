#pragma once
#ifndef sequence_h
#define sequence_h

template <typename Item> class Sequence {
public:
	virtual int GetLength() = 0;
	virtual bool getIsEmpty() = 0;
	virtual Item GetFirst() = 0;
	virtual Item GetLast() = 0;
	virtual Item get(int index) = 0;
	virtual Sequence<Item>* GetSubsequence(int startIndex, int endIndex) = 0;
	virtual void Append(Item item) = 0;
	virtual void Prepend(Item item) = 0;
	virtual void InsertAt(int index, Item item) = 0;
	virtual void Remove(Item item) = 0;
protected:
	int length = 0;
};


#endif