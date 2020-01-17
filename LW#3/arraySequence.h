#pragma once
#ifndef arraySequence_h
#define arraySequence_h

#include "sequence.h"

template<typename Item>
class arraySequence: public Sequence<Item> {
public:
	int GetLength() override;
	bool getIsEmpty() override;
	Item get(int index) override;
	Item GetFirst() override;
	Item GetLast() override;
	arraySequence<Item>* GetSubsequence(int startIndex, int endIndex) override;
	void Append(Item item) override;
	void Prepend(Item item) override;
	void InsertAt(int index, Item item) override;
	void Remove(int index) override;
	Item* GetPtr(int index) override;
	void set(int index, Item value) override;
private:
	int marked = 5;
	Item* array = new Item[5];
	void StrechArray() {
		const int len = this->length + this->length / 2;
		Item* new_array = new Item[len];
		for (int i = 0; i < this->length; i++) {
			new_array[i] = this->array[i];
		};
		this->array = new_array;
		this->marked = len;
	};

	void MoveLeft(int startIndex, int endIndex) {
		for (int i = startIndex; i <= endIndex; i++) {
			this->array[i - 1] = this->array[i];
		}
	}

	void MoveRight(int startIndex, int endIndex) {
		for (int i = endIndex; i >= startIndex; i--) {
			this->array[i + 1] = this->array[i];
		}
	}
};

#endif
