typedef unsigned int uint;
typedef unsigned long int ulint;

template <typename T>
class Sequence
{
protected:
	uint len = 0;

public:
	uint GetLen();
	bool IsEmpty();

public:
	virtual T operator[](uint index) = 0;
	virtual T GetFirst() = 0;
	virtual T GetLast() = 0;
	virtual Sequence<T> *GetSubS(uint start, uint end) = 0;
	virtual void Append(T value) = 0;
	virtual void Prepend(T value) = 0;
	virtual void Insert(T value, uint index) = 0;
};

#include "Sequence.cpp"
#include "List.h"
#include "Array.h"
