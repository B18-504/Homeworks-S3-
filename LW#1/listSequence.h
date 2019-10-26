#pragma once
#ifndef listSequence_h
#define listSequence_h

#include "sequence.h"

template<typename Item>
class listSequence : public Sequence<Item> {
public:
	int GetLength() override;
	bool getIsEmpty() override;
	Item get(int index) override;
	Item GetFirst() override;
	Item GetLast() override;
	listSequence<Item>* GetSubsequence(int startIndex, int endIndex) override;
	void Append(Item item) override;
	void Prepend(Item item) override;
	void InsertAt(int index, Item item) override;
	void Remove(Item item) override;
private:
	class Node {
	public:
		Node* getNext() {
			return this->nextNode;
		}

		Node* getPrevious() {
			return this->previousNode;
		}

		Item getData() {
			return data;
		}

		void setNext(Node* next) {
			this->nextNode = next;
		}

		void setPrevious(Node* previous) {
			this->previousNode = previous;
		}

		void setData(Item data) {
			this->data = data;
		}
	private:
		Node* nextNode = nullptr;
		Node* previousNode = nullptr;
		Item data;
	};

	Node* head;
	Node* tail;
};

#endif

