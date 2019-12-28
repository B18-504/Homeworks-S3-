#pragma once

template <typename T>
class ListSequence : public Sequence<T>
{
private:
	class Node
	{
	public:
		T *body;
		Node *next = 0;
		Node *prev = 0;
	
		Node() = default;
		Node(T *a, Node *n = 0, Node *p = 0)
		{
			body = a;
			next = n;
			prev = p;
		}
		
		~Node() = default;
	};
	
	Node *first = 0;
	Node *last = 0;
	
	void ShiftPtrRight(void *&ptr, int &position) const override;
	void ShiftPtrLeft(void *&ptr, int &position) const override;
	T &GetVal(void *ptr) const override;
	void SetVal(T &val, void *ptr) const override;
	
public:
	ListSequence() = default;
	
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
	
	~ListSequence();
};

#include "ListSequence.cpp"
