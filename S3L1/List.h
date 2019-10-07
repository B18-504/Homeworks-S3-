#pragma once

template <typename T>
class List : public Sequence<T>
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
	
public:
	List() = default;
	
	T *operator[](uint index) override;
	T *GetFirst() override;
	T *GetLast() override;
	
	Sequence<T> *GetSubS(uint start, uint end) override;
	
	void Append(T *value) override;
	void Prepend(T *value) override;
	void Insert(T *value, uint index) override;
	void Remove(T *value) override;
	
	~List()
	{
		Node *tmp = first;
		Node *next = 0;
		while(tmp)
		{
			next = tmp->next;
			delete tmp;
			tmp = next;
		}
	}
};

#include "List.cpp"
