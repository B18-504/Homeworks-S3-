#pragma once
#ifndef functions_h
#define functions_h

#include <ctime>
#include <stdlib.h>
#include "arraySequence.h"
#include "listSequence.h"

template<typename T>
void swap(Sequence<T>** sequence, int pos1, int pos2) {
	T item1 = (*sequence)->get(pos1);
	T item2 = (*sequence)->get(pos2);

	int len = (*sequence)->GetLength();
	for (int i = 0; i < len; i++) {
		if (i == pos1) {
			(*sequence)->Append(item2);
			continue;
		}
		if (i == pos2) {
			(*sequence)->Append(item1);
			continue;
		}
		(*sequence)->Append((*sequence)->get(i));
	}

	for (int i = 0; i < len; i++) {
		(*sequence)->Remove(0);
	}
}

template<typename T>
void del(Sequence<T>** sequence, int index) {
	int len = (*sequence)->GetLength();
	for (int i = 0; i < len; i++) {
		if (i == index) continue;
		(*sequence)->Append((*sequence)->get(i));
	}

	for (int i = 0; i < len; i++) {
		(*sequence)->Remove(0);
	}
}

template<typename T>
void fill(Sequence<T>* sequence, int n, int from, int to) {
	srand(time(0));
	for (int i = 0; i < n; i++) {
		sequence->Append(from + rand() % to);
	}
}

template<typename T>
void sortModule(Sequence<T>** sequence, int begin, int end, bool (*comp)(T a, T b)) {
	//std::cout << begin << " " << end << std::endl;
	if (end - begin < 1) return;
	if (end - begin == 1) {
		if (comp((*sequence)->get(begin), (*sequence)->get(end))) swap(sequence, begin, end);
	}
	int middle = (begin + end) / 2;
	int i = begin, j = end;
	T middleValue = (*sequence)->get(middle);
	while (true) {
		while (comp(middleValue, (*sequence)->get(i)) && i < middle) i++;
		while (comp((*sequence)->get(j), middleValue) && j > middle) j--;

		if (i >= j) break;
		bool J = true;
		if (j == middle) J = false;

		if (i != middle) {
			(*sequence)->InsertAt(middle + 1, (*sequence)->get(i));
			del(sequence, i);
			middle--;
		}

		if (J) {
			(*sequence)->InsertAt(middle, (*sequence)->get(j));
			del(sequence, j + 1);
			middle++;
		}
	}

	sortModule(sequence, begin, middle - 1, comp);
	sortModule(sequence, middle + 1, end, comp);
}

template<typename T>
Sequence<T>* buildHeap(Sequence<T>* sequence, bool (*comp)(T a, T b)) {
	Sequence<T>* result = sequence->GetSubsequence(0, 0);
	result->Remove(0);

	for (int i = 0; i < sequence->GetLength(); i++) {
		result->Prepend(sequence->get(i));
		shiftDown(result, result->GetLength(), comp);
	}

	return result;
}

template<typename T>
void shiftDown(Sequence<T>* sequence, int len, bool (*comp)(T a, T b)) {

	int currentNode = 0;

	while (true) {
		if (currentNode * 2 + 1 < len && currentNode * 2 + 2 < len) {
			if (comp(sequence->get(currentNode * 2 + 1), sequence->get(currentNode * 2 + 2))) {
				if (sequence->get(currentNode * 2 + 1) > sequence->get(currentNode)) {
					swap(&sequence, currentNode * 2 + 1, currentNode);
					currentNode = currentNode * 2 + 1;
					continue;
				}
			}
			else {
				if (comp(sequence->get(currentNode * 2 + 2), sequence->get(currentNode))) {
					swap(&sequence, currentNode * 2 + 2, currentNode);
					currentNode = currentNode * 2 + 2;
					continue;
				}
			}
		}

		if (currentNode * 2 + 1 < len) {
			if (comp(sequence->get(currentNode * 2 + 1), sequence->get(currentNode))) {
				swap(&sequence, currentNode * 2 + 1, currentNode);
				currentNode = currentNode * 2 + 1;
				continue;
			}
		}

		break;
	}
}

#endif // !functions_h
