#pragma once
#ifndef sorts_h
#define sorts_h

#include "functions.h"

template<typename T>
bool comp(T a, T b) {
	return a >= b;
}

template<typename T>
Sequence<T>* quickSort(Sequence<T>* sequence, bool (*comp)(T, T)) {

	sortModule(&sequence, 0, sequence->GetLength() - 1, comp);

	return sequence;
}

template<typename T>
Sequence<T>* heapSort(Sequence<T>* sequence, bool (*comp)(T, T)) {
	Sequence<T>* result = buildHeap(sequence, comp);

	int heapLen = result->GetLength();
	
	while (heapLen > 1) {
		swap(&result, 0, heapLen - 1);
		heapLen--;
		shiftDown(result, heapLen, comp);
	}
	return result;
}

template<typename T>
Sequence<T>* binSort(Sequence<T>* sequence, bool (*comp)(T, T)) {
	Sequence<T>* result = sequence->GetSubsequence(0, 0);
	
	int l, r;

	for (int i = 1; i < sequence->GetLength(); i++) {

		l = 0;
		r = result->GetLength();

		T currentItem = sequence->get(i);

		while (l < r) {
			if (comp(currentItem, result->get((l + r) / 2))) {
				l = (l + r + 1) / 2;
			}
			else {
				r = (l + r) / 2;
			}
		}

		result->InsertAt(l, currentItem);
	}
	
	return result;
}

#endif // !sorts_h
