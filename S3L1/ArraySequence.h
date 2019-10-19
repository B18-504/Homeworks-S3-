#pragma once

template <typename T>
class ArraySequence : public Sequence<T>
{
private:
	uint allocated_bytes = 0;
	T **body = 0;
	
	void extend();
	
	void ShiftPtrRight(void *&ptr, uint &position) const override;
	void ShiftPtrLeft(void *&ptr, uint &position) const override;
	T *GetVal(void *ptr) const override;
	void SetVal(T *val, void *ptr) const override;
	
public:
	
	ArraySequence() = default;
	
	T *operator[](uint index) const override;
	T *GetFirst() const override;
	T *GetLast() const override;
	
	Sequence<T> *GetSubS(uint start, uint end) const override;
	
	void Append(T *value) override;
	void Prepend(T *value) override;
	void Insert(T *value, uint index) override;
	
	void Remove(T *value) override;
	void Clear() override;
	
	void SetFromStr(char **values, uint length) override;
	void SetRandVals(T *(*generator)(), uint length) override;
	
	typename Sequence<T>::Slider &InitSlider(uint initpos) const override;
	
	~ArraySequence();
};

#include "ArraySequence.cpp"
