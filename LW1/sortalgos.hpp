#ifndef sortalgos_hpp
#define sortalgos_hpp
#include "arraysequence.hpp"
#include "arraysequence.cpp"
#include "listsequence.hpp"
#include "listsequence.cpp"

template <typename T>
class Sort {
public:
    template <typename C>
    static void mergeSort(Sequence<T>* seq, int start, int end, C cmp);
    template <typename C>
    static void quickSort(Sequence<T>* seq, int start, int end, C cmp);
    template <typename C>
    static void bubbleSort(Sequence<T>* seq, int start, int end, C cmp);
private:
    template <typename C>
    static void merge(Sequence<T>* seq, int start, int middle, int end, C cmp);
};




#endif
