#pragma once

template <typename T>
class Array : public Sequence<T>
{
private:
	uint allocated_bytes = 0;
	T **body = 0;
	
	void extend();
	
	void ShiftPtrRight(void *&ptr, uint &position) override;
	void ShiftPtrLeft(void *&ptr, uint &position) override;
	T *GetVal(void *ptr) override;
	void SetVal(T *val, void *ptr) override;
	
public:
	
	Array() = default;
	
	T *operator[](uint index) override;
	T *GetFirst() override;
	T *GetLast() override;
	
	Sequence<T> *GetSubS(uint start, uint end) override;
	
	void Append(T *value) override;
	void Prepend(T *value) override;
	void Insert(T *value, uint index) override;
	
	void Remove(T *value) override;
	void Clear() override;
	
	void SetFromStr(char **values, uint length) override;
	
	typename Sequence<T>::Slider &InitSlider(uint initpos) override;
	
	~Array();
};

#include "Array.cpp"
