#pragma once

template <typename T>
class ArraySequence : public Sequence<T>
{
private:
	int allocated_bytes = 0;
	T **body = 0;
	
	void extend();
	
	void ShiftPtrRight(void *&ptr, int &position) const override;
	void ShiftPtrLeft(void *&ptr, int &position) const override;
	T &GetVal(void *ptr) const override;
	void SetVal(T &val, void *ptr) const override;
	
public:
	
	ArraySequence() = default;
	
	T &operator[](int index) const override;
	T &GetFirst() const override;
	T &GetLast() const override;
	
	Sequence<T> *GetSubS(int start, int end) const override;
	
	void Append(T &value) override;
	void Prepend(T &value) override;
	void Insert(T &value, int index) override;
	void ForceLength(int length) override;
	
	void Remove(T &value) override;
	void Clear() override;
	
	void SetRandVals(T *(*generator)(), int length) override;
	
	typename Sequence<T>::Slider &InitSlider(int initpos) const override;
	
	~ArraySequence();
};

#include "ArraySequence.cpp"
