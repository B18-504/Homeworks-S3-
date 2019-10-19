#pragma once
template <typename T>
class ArraySequence;

template <typename T>
class ListSequence;


typedef unsigned int uint;
typedef unsigned long int ulint;

template <typename T>
class Sequence
{
protected:
	uint len = 0;
	
	class SliderList;
	
	SliderList &SList = *new SliderList;
	
	virtual void ShiftPtrRight(void *&ptr, uint &position) const = 0;			//Interface for Sliders
	virtual void ShiftPtrLeft(void *&ptr, uint &position) const = 0;
	virtual T *GetVal(void *ptr) const = 0;
	virtual void SetVal(T *val, void *ptr) const = 0;
	
public:
	Sequence() = default;

	class Slider;

	uint GetLen() const;
	bool IsEmpty() const;
	
	bool IsSorted(char comparison(T &a, T &b)) const;
	
public:
	virtual T *operator[](uint index) const = 0;
	virtual T *GetFirst() const = 0;
	virtual T *GetLast() const = 0;
	
	virtual Sequence<T> *GetSubS(uint start, uint end) const = 0;
	
	virtual void Append(T *value) = 0;
	virtual void Prepend(T *value) = 0;
	virtual void Insert(T *value, uint index) = 0;
	
	virtual void Remove(T *value) = 0;
	virtual void Clear() = 0;
	
	virtual void SetFromStr(char **values, uint length) = 0;
	virtual void SetRandVals(T *(*generator)(), uint length) = 0;
	
	virtual Slider &InitSlider(uint initpos) const = 0;
	
	virtual ~Sequence();
	
	friend class Slider;
};

#include "Sequence.cpp"
#include "Slider.h"
#include "ListSequence.h"
#include "ArraySequence.h"
#include "Sorts.h"
