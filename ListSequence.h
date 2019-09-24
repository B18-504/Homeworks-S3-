#pragma once
#include "Sequence.h"

template <typename T>
class ListSequence : public Sequence<T> 
{
private:
	struct Node 
	{
		T data;
		Node* next;
	};
	Node* head = nullptr, *tail = nullptr;
public:
	T Get(int index) 
	{
		if (index > this->length)
			throw ("Out of list size");
		if (index < 0)
			throw ("Negative input index");
		Node* temp = head;
		for (int i = 0; i < index; i++)
			temp = temp->next;
		return temp->data;
	}
	void Append(T item)
	{
		if (this->length == 0)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data = item;
			tail = head;
		}
		else
		{
			tail->next = (Node*)malloc(sizeof(Node));
			tail = tail->next;
			tail->data = item;
		}
		this->length++;
	}
	void Prepend(T item)
	{
		if (this->length == 0)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data = item;
			tail = head;
		}
		else 
		{
			Node* temp = (Node*)malloc(sizeof(Node));
			temp->next = head;
			temp->data = item;
			head = temp;
			temp = nullptr;
		}
		this->length++;
	}
	void InsertAt(int index, T item) 
	{
		if (index > this->length)
			throw("Out of list size");
		if (this->length == 0)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data = item;
			tail = head;
		}
		else
		{
			Node* temp; //счетчик мест
			Node* temp1 = (Node*)malloc(sizeof(Node)); // память под новый элемент
			temp = head;
			for (int i = 1; i < index - 1; i++)
				temp = temp->next;
			temp1->next = temp->next;
			temp1->data = item;
			temp->next = temp1;
		}
		this->length++;
	}
	void Show()
	{
		Node* temp = head;
		int i = this->length;
		while (i-- != 0) 
		{
			std::cout << temp->data << " ";
			temp = temp->next;
		}
	}
	ListSequence<T>* GetSubSequence(int startIndex, int endIndex)
	{
		if (endIndex < startIndex)
			std::swap(endIndex, startIndex);
		if (endIndex >= this->length)
			throw("Out of list size");
		ListSequence<T>* newList = new ListSequence<T>;
		Node* temp = head;
		for (int i = 0; i < startIndex; i++)
			temp = temp->next;
		for (int i = startIndex; i <= endIndex; i++)
		{
			newList->Append(temp->data);
			temp = temp->next;
		}
		return newList;
	}
	void Remove(T item)
	{
		int i = 1, j = 1;
		Node* temp = head;
		while (j < this->length)
		{
			for (i; i < this->length; i++)
				if (Get(i) == item)
					break;
			j = i;
			if (i != this->length--)
			{
				for (i; i > 2; i--)
					temp = temp->next;
				temp->next = temp->next->next;
			}
			i = ++j;
		}
	}
};
