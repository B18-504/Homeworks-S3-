#pragma once
template <typename T>
class Array;

template <typename T>
class List;


typedef unsigned int uint;
typedef unsigned long int ulint;

template <typename T>
class Sequence
{
protected:
	uint len = 0;
	
	class SliderList;
	
	SliderList SList = *new SliderList;
	
	virtual void ShiftPtrRight(void *&ptr, uint &position) = 0;			//Интерфейс для Slider'ов
	virtual void ShiftPtrLeft(void *&ptr, uint &position) = 0;
	virtual T *GetVal(void *ptr) = 0;
	virtual void SetVal(T *val, void *ptr) = 0;
	
public:
	Sequence() = default;

	class Slider;

	uint GetLen();
	bool IsEmpty();
	
	bool IsSorted(char comparison(T &a, T &b));
	
public:
	virtual T *operator[](uint index) = 0;
	virtual T *GetFirst() = 0;
	virtual T *GetLast() = 0;
	
	virtual Sequence<T> *GetSubS(uint start, uint end) = 0;
	
	virtual void Append(T *value) = 0;
	virtual void Prepend(T *value) = 0;
	virtual void Insert(T *value, uint index) = 0;
	
	virtual void Remove(T *value) = 0;
	virtual void Clear() = 0;
	
	virtual void SetFromStr(char **values, uint length) = 0;
	
	virtual Slider &InitSlider(uint initpos) = 0;
	
	virtual ~Sequence();
	
	friend class Slider;
};

#include "Sequence.cpp"
#include "Slider.h"
#include "List.h"
#include "Array.h"
