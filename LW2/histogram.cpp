#include "histogram.hpp"

template <typename TKey, typename TElement, typename F>
RBDictionary<TKey, TElement> reduce(const RBMultiDictionary<TKey, TElement>& dict, F prcssFunction) {
    RBDictionary<TKey, TElement> result;
    for (auto i : dict)
        result.insert(i.first, prcssFunction(i.second));
    return result;
}

template <typename T, typename TKey, typename TElement, typename F>
void map(ArraySequence<T>* elems, TKey range, RBMultiDictionary<TKey, TElement>& target, F prcssFunction) {
    for (auto i : *elems) {
        if (prcssFunction(range, i))
            target.insert(range, 1);
        else
            target.insert(range, 0);
    }
}

template <typename T, typename F, typename C>
RBDictionary<std::pair<int, int>, int> buildHistogram(ArraySequence<T>* elems, F prcssFunction, C cmpFunction, int begin, int end, int range) {
    RBMultiDictionary<std::pair<int, int>, int> buffer;
    
    for (int i = begin; i < end; i += range) {
        map(elems, std::make_pair(i, i + range), buffer, cmpFunction);
    }
    
    return reduce(buffer, prcssFunction);
}

template <typename T, typename F, typename C>
RBDictionary<std::pair<int, int>, int> buildHistogram(ArraySequence<T>* elems, F prcssFunction, C cmpFunction, ArraySequence<std::pair<int, int>>* ranges) {
    RBMultiDictionary<std::pair<int, int>, int> buffer;
    
    for (auto i : *ranges) {
        map(elems, i, buffer, cmpFunction);
    }
    
    return reduce(buffer, prcssFunction);
}
