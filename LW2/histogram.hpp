#ifndef histogram_hpp
#define histogram_hpp

#include "dictionaries.hpp"
#include "sequences.hpp"

template <typename TKey, typename TElement, typename F>
RBDictionary<TKey, TElement> reduce(const RBMultiDictionary<TKey, TElement>& dict, F prcssFunction);

template <typename T, typename TKey, typename TElement, typename F>
void map(ArraySequence<T>* elems, TKey range, RBMultiDictionary<TKey, TElement>& target, F prcssFunction);

template <typename T, typename F, typename C, typename ...E>
RBDictionary<std::pair<int, int>, int> buildHistogram(ArraySequence<T>* elems, F prcssFunction, C cmpFunction, const E&... fragmentation);

template <typename T, typename F, typename C>
RBDictionary<std::pair<int, int>, int> buildHistogram(ArraySequence<T>* elems, F prcssFunction, C cmpFunction, int begin, int end, int range);

template <typename T, typename F, typename C>
RBDictionary<std::pair<int, int>, int> buildHistogram(ArraySequence<T>* elems, F prcssFunction, C cmpFunction, ArraySequence<std::pair<int, int>>* ranges);

#endif
