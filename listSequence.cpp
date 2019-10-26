#include "listSequence.h"
#include "exception.h"

template<typename Item>
Item listSequence<Item>::get(int index) {
	if (this->length == 0) throw containerIsEmpty();
	if (index < 0 || index >= this->length) throw outOfRange();
	Node* currentNode;
	currentNode = this->head;
	for (int i = 0; i < index; i++) {
		currentNode = currentNode->getNext();
	}
	return currentNode->getData();
};

template<typename Item>
Item listSequence<Item>::GetFirst() {
	if (this->length == 0) throw containerIsEmpty();
	return this->head->getData();
};


template<typename Item>
Item listSequence<Item>::GetLast() {
	if (this->length == 0) throw containerIsEmpty();
	return this->tail->getData();
};

template<typename Item>
listSequence<Item>* listSequence<Item>::GetSubsequence(int startIndex, int endIndex) {
	if (this->length == 0) throw containerIsEmpty();
	if (endIndex > this->length - 1 || startIndex < 0) throw outOfRange();
	listSequence<Item>* result = new listSequence<Item>;

	Node* currentNode;
	currentNode = this->head;
	for (int i = 0; i < startIndex; i++) {
		currentNode = currentNode->getNext();
	}

	for (int i = 0; i <= endIndex - startIndex; i++) {
		result->Append(currentNode->getData());
		currentNode = currentNode->getNext();
	}

	return result;
};

template<typename Item>
void listSequence<Item>::Append(Item item) {
	Node* new_node = new Node();
	new_node->setData(item);
	new_node->setPrevious(this->tail);
	if (this->head == nullptr) {
		this->head = new_node;
		this->tail = new_node;
		this->length++;
		return;
	}
	this->tail->setNext(new_node);
	this->tail = new_node;
	this->length++;
};

template<typename Item>
void listSequence<Item>::Prepend(Item item) {
	Node* new_node = new Node();
	new_node->setData(item);
	new_node->setNext(this->head);
	if (this->head == nullptr) {
		this->head = new_node;
		this->tail = new_node;
		this->length++;
		return;
	}
	this->head->setPrevious(new_node);
	this->head = new_node;
	this->length++;
};

template<typename Item>
void listSequence<Item>::InsertAt(int index, Item item) {
	if (index < 0 || index > this->length) throw outOfRange();
	if (index == 0) return this->Prepend(item);
	if (index == this->length) return this->Append(item);
	Node* currentNode;
	currentNode = this->head;
	for (int i = 0; i < index - 1; i++) {
		currentNode = currentNode->getNext();
	}

	Node* new_node = new Node();
	new_node->setData(item);
	new_node->setNext(currentNode->getNext());
	new_node->setPrevious(currentNode);
	if (currentNode->getNext() != nullptr) currentNode->getNext()->setPrevious(new_node);
	currentNode->setNext(new_node);
	this->length++;
};

template<typename Item>
void listSequence<Item>::Remove(Item item) {
	Node* currentNode;
	currentNode = this->head;
	if (currentNode->getData() == item) {
		currentNode->getNext()->setPrevious(nullptr);
		this->head = currentNode->getNext();
		this->length--;
		return;
	}

	while (currentNode != this->tail) {
		if (currentNode->getData() == item) {
			currentNode->getPrevious()->setNext(currentNode->getNext());
			currentNode->getNext()->setPrevious(currentNode->getPrevious());
			this->length--;
			return;
		}
		currentNode = currentNode->getNext();
	}

	if (currentNode->getData() == item) {
		currentNode->getPrevious()->setNext(currentNode->getNext());
		this->tail = currentNode->getPrevious();
		this->length--;
		return;
	}
};

template<typename Item>
int listSequence<Item>::GetLength() {
	return this->length;
};

template<typename Item>
bool listSequence<Item>::getIsEmpty() {
	if (this->length) return false;
	return true;
};