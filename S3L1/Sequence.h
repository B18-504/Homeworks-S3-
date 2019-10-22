#pragma once
template <typename T>
class ArraySequence;

template <typename T>
class ListSequence;


//typedef unsigned int int;
//typedef unsigned long int ulint;

template <typename T>
class Sequence
{
protected:
	int len = 0;
	
	class SliderList;
	
	SliderList &SList = *new SliderList;
	
	virtual void ShiftPtrRight(void *&ptr, int &position) const = 0;			//Interface for Sliders
	virtual void ShiftPtrLeft(void *&ptr, int &position) const = 0;
	virtual T *GetVal(void *ptr) const = 0;
	virtual void SetVal(T *val, void *ptr) const = 0;
	
public:
	Sequence() = default;

	class Slider;

	int GetLen() const;
	bool IsEmpty() const;
	
	bool IsSorted(char comparison(T &a, T &b)) const;
	
public:
	virtual T *operator[](int index) const = 0;
	virtual T *GetFirst() const = 0;
	virtual T *GetLast() const = 0;
	
	virtual Sequence<T> *GetSubS(int start, int end) const = 0;
	
	virtual void Append(T *value) = 0;
	virtual void Prepend(T *value) = 0;
	virtual void Insert(T *value, int index) = 0;
	
	virtual void Remove(T *value) = 0;
	virtual void Clear() = 0;
	
	virtual void SetFromStr(char **values, int length) = 0;
	virtual void SetRandVals(T *(*generator)(), int length) = 0;
	
	virtual Slider &InitSlider(int initpos) const = 0;
	
	virtual ~Sequence();
	
	friend class Slider;
};

#include "Sequence.cpp"
#include "Slider.h"
#include "ListSequence.h"
#include "ArraySequence.h"
#include "Sorts.h"
