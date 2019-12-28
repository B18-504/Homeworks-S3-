#pragma once

#include "CallStack.h"

template <typename T>
void QuickSort(Sequence<T> &seq, char comparison(T &a, T &b));			//Pass true -> 1, equals -> -1 and false 0!

template <typename T>
void InsertSort(Sequence<T> &seq, char comparison(T &a, T &b));         // --/--


#include "Sorts.cpp"