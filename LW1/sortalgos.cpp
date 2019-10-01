#include "sortalgos.hpp"

template <typename T>
template <typename C>
void Sort<T>::mergeSort(Sequence<T>* seq, int start, int end, C cmp) {
    if (start > end) {
        exception_incorrectSelection e;
        throw e;
    }
    if ((end >= seq->getLength()) || (start < 0)) {
        exception_outOfRange e;
        throw e;
    }
    if (start < end) {
        int middle = (start + end) / 2;
        mergeSort(seq, start, middle, cmp);
        mergeSort(seq, middle + 1, end, cmp);
        merge(seq, start, middle, end, cmp);
    }
}

template <typename T>
template <typename C>
void Sort<T>::merge(Sequence<T>* seq, int start, int middle, int end, C cmp) {
    int n1 = middle - start + 1;
    int n2 = end - middle;
    ArraySequence<T>* L = new ArraySequence<T>;
    ArraySequence<T>* R = new ArraySequence<T>;
    for (int i = 0; i < n1; i++) {
        L->append(seq->get(start + i));
    }
    for (int i = 0; i < n2; i++) {
        R->append(seq->get(middle + 1 + i));
    }
    
    int i = 0, j = 0, k = start;
    while (i < n1 && j < n2) {
        if (cmp(L->get(i), R->get(j))) {
            seq->replace(k, L->get(i));
            i++;
        }
        else {
            seq->replace(k, R->get(j));
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        seq->replace(k, L->get(i));
        i++;
        k++;
    }
    
    while (j < n2) {
        seq->replace(k, R->get(j));
        j++;
        k++;
    }
}

template <typename T>
template <typename C>
void Sort<T>::quickSort(Sequence<T>* seq, int start, int end, C cmp) {
    if (start > end) {
        exception_incorrectSelection e;
        throw e;
    }
    if ((end >= seq->getLength()) || (start < 0)) {
        exception_outOfRange e;
        throw e;
    }
    int i = start;
    int j = end;
    T pivot = seq->get((i + j) / 2);
    
    while (i <= j) {
        while (cmp(seq->get(i), pivot) && seq->get(i) != pivot) {
            i++;
        }
        while (!cmp(seq->get(j), pivot) && seq->get(j) != pivot) {
            j--;
        }
        if (i <= j) {
            T tmp = seq->get(i);
            seq->replace(i, seq->get(j));
            seq->replace(j, tmp);
            i++;
            j--;
        }
    }
    if (j > start) {
        quickSort(seq, start, j, cmp);
    }
    if (i < end) {
        quickSort(seq, i, end, cmp);
    }
}

template <typename T>
template <typename C>
void Sort<T>::bubbleSort(Sequence<T>* seq, int start, int end, C cmp) {
    if (start > end) {
        exception_incorrectSelection e;
        throw e;
    }
    if ((end >= seq->getLength()) || (start < 0)) {
        exception_outOfRange e;
        throw e;
    }
    for (int i = 0; i < end; i++) {
        for (int j = 0; j < end - i; j++) {
            if (cmp(seq->get(j + 1), seq->get(j))) {
                T tmp = seq->get(j);
                seq->replace(j, seq->get(j + 1));
                seq->replace(j + 1, tmp);
            }
        }
    }
}
