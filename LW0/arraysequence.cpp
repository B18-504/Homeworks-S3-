#include "arraysequence.hpp"
#include "functions.hpp"

template <typename T>
ArraySequence<T>::ArraySequence() {
    Sequence<T>::length = 0;
    data = nullptr;
}

template <typename T>
ArraySequence<T>::ArraySequence(ArraySequence<T>* sequence) {
    Sequence<T>::length = sequence->getLength();
    data = (T*)malloc(sizeof(T) * Sequence<T>::length);
    for (int i = 0; i < Sequence<T>::length; i++) {
        *(data + i) = sequence->get(i);
    }
}

template <typename T>
ArraySequence<T>::ArraySequence(int n, int leftLimit, int rightLimit) {
    if (rightLimit < leftLimit) {
        exception_incorrectSelection e;
        throw e;
    }
    data = (T*)malloc(sizeof(T) * n);
    Sequence<T>::length = n;
    for (int i = 0; i < n; i++) {
        *(data + i) = randInt(leftLimit, rightLimit);
    }
}

template <typename T>
int ArraySequence<T>::getLength() const {
    return Sequence<T>::length;
}

template <typename T>
bool ArraySequence<T>::getIsEmpty() const {
    if (!Sequence<T>::length) {
        return true;
    }
    return false;
}

template <typename T>
T ArraySequence<T>::get(int index) const {
    if ((index >= Sequence<T>::length) || (index < 0)) {
        exception_outOfRange e;
        throw e;
    }
    return *(data + index);
}

template <typename T>
T ArraySequence<T>::getFirst() const {
    if (!Sequence<T>::length) {
        exception_sequenceIsEmpty e;
        throw e;
    }
    return *(data);
}

template <typename T>
T ArraySequence<T>::getLast() const {
    if (!Sequence<T>::length) {
        exception_sequenceIsEmpty e;
        throw e;
    }
    return *(data + Sequence<T>::length - 1);
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::getSubSequence(int startIndex, int endIndex) const {
    if (endIndex < startIndex) {
        exception_incorrectSelection e;
        throw e;
    }
    if (endIndex >= Sequence<T>::length) {
        exception_outOfRange e;
        throw e;
    }
    ArraySequence<T>* buff = new ArraySequence<T>;
    for (int i = startIndex; i <= endIndex; i++) {
        buff->append(this->get(i));
    }
    return buff;
}

template <typename T>
void ArraySequence<T>::append(T item) {
    Sequence<T>::length++;
    if (!(Sequence<T>::length - 1)) {
        data = (T*)malloc(sizeof(T));
    }
    else {
        data = (T*)realloc(data, sizeof(T) * Sequence<T>::length);
    }
    *(data + Sequence<T>::length - 1) = item;
}

template <typename T>
void ArraySequence<T>::prepend(T item) {
    Sequence<T>::length++;
    if (!(Sequence<T>::length - 1)) {
        data = (T*)malloc(sizeof(T));
    }
    else {
        data = (T*)realloc(data, sizeof(T) * Sequence<T>::length);
        for (int i = Sequence<T>::length - 1; i > 0; i--) {
            *(data + i) = *(data + i - 1);
        }
    }
    *(data) = item;
}

template <typename T>
void ArraySequence<T>::insertAt(int index, T item) {
    if (index > Sequence<T>::length) {
        exception_outOfRange e;
        throw e;
    }
    Sequence<T>::length++;
    if (!(Sequence<T>::length - 1)) {
        data = (T*)malloc(sizeof(T));
        *(data) = item;
    }
    else {
        data = (T*)realloc(data, sizeof(T) * Sequence<T>::length);
        for (int i = Sequence<T>::length - 1; i > index; i--) {
            *(data + i) = *(data + i - 1);
        }
        *(data + index) = item;
    }
}

template <typename T>
void ArraySequence<T>::remove(T item) {
    int index = -1;
    for (int i = 0; i < Sequence<T>::length; i++) {
        if (*(data + i) == item) {
            index = i;
            break;
        }
    }
    Sequence<T>::length--;
    for (int i = index; i < Sequence<T>::length; i++) {
        *(data + i) = *(data + i - 1);
    }
    data = (T*)realloc(data, sizeof(T) * Sequence<T>::length);
}

template <typename T>
ArraySequence<T>::~ArraySequence() {
    free(data);
    data = nullptr;
    Sequence<T>::length = 0;
}
