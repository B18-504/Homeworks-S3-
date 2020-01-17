#include "arraySequence.h"
#include "exception.h"

template<typename Item>
Item arraySequence<Item>::get(int index) {
	if (this->length == 0) throw containerIsEmpty();
	if (index < 0 || index >= this->length) throw outOfRange();
	return this->array[index];
};

template<typename Item>
Item arraySequence<Item>::GetFirst() {
	if (this->length == 0) throw containerIsEmpty();
	return this->array[0];
};


template<typename Item>
Item arraySequence<Item>::GetLast() {
	if (this->length == 0) throw containerIsEmpty();
	return this->array[this->length - 1];
};

template<typename Item>
arraySequence<Item>* arraySequence<Item>::GetSubsequence(int startIndex, int endIndex) {
	if (this->length == 0) throw containerIsEmpty();
	if (endIndex > this->length - 1 || startIndex < 0) throw outOfRange();

	arraySequence<Item>* result = new arraySequence<Item>;

	for (int i = startIndex; i <= endIndex; i++) {
		result->Append(this->array[i]);
	}

	return result;
};

template<typename Item>
void arraySequence<Item>::Append(Item item) {
	if (this->length == marked) StrechArray();
	this->array[this->length] = item;
	this->length++;
};

template<typename Item>
void arraySequence<Item>::Prepend(Item item) {
	if (this->length == marked) StrechArray();
	MoveRight(0, this->length - 1);
	this->array[0] = item;
	this->length++;
};

template<typename Item>
void arraySequence<Item>::InsertAt(int index, Item item) {
	if (index < 0 || index > this->length) throw outOfRange();
	if (this->length == marked) StrechArray();
	MoveRight(index, this->length - 1);
	this->array[index] = item;
	this->length++;
};

template<typename Item>
void arraySequence<Item>::Remove(int index) {
	MoveLeft(index + 1, this->length - 1);
	this->length--;
};

template<typename Item>
int arraySequence<Item>::GetLength() {
	return this->length;
};

template<typename Item>
bool arraySequence<Item>::getIsEmpty() {
	if (this->length) return false;
	return true;
};

template<typename Item>
Item* arraySequence<Item>::GetPtr(int index) {
	return (this->array + index);
}

template<typename Item>
void arraySequence<Item>::set(int index, Item value) {
	this->array[index] = value;
}