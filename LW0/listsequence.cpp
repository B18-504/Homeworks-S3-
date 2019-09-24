#include "listsequence.hpp"

template <typename T>
ListSequence<T>::ListSequence() {
    head = tail  = nullptr;
    Sequence<T>::length = 0;
}

template <typename T>
ListSequence<T>::ListSequence(Sequence<T>* sequence) {
    head = tail  = nullptr;
    Sequence<T>::length = 0;
    for (int i = 0; i < sequence->getLength(); i++) {
        this->append(sequence->get(i));
    }
}

template <typename T>
ListSequence<T>::ListSequence(int n, int leftLimit, int rightLimit) {
    if (rightLimit < leftLimit) {
        exception_incorrectSelection e;
        throw e;
    }
    head = tail  = nullptr;
    Sequence<T>::length = 0;
    for (int i = 0; i < n; i++) {
        this->append(rnd::randInt(leftLimit, rightLimit));
    }
}

template <typename T>
int ListSequence<T>::getLength() const {
    return Sequence<T>::length;
}

template <typename T>
bool ListSequence<T>::getIsEmpty() const {
    if (!Sequence<T>::length) {
        return true;
    }
    return false;
}

template <typename T>
T ListSequence<T>::get(int index) const {
    if ((index >= Sequence<T>::length) || (index < 0)) {
        exception_outOfRange e;
        throw e;
    }
    Node* tmp = nullptr;
    if (index < Sequence<T>::length/2) {
        tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
    }
    else {
        tmp = tail;
        for (int i = 0; i < Sequence<T>::length - index - 1; i++) {
            tmp = tmp->prev;
        }
    }
    return tmp->data;
}

template <typename T>
T ListSequence<T>::getFirst() const {
    if (!Sequence<T>::length) {
        exception_sequenceIsEmpty e;
        throw e;
    }
    return head->data;
}

template <typename T>
T ListSequence<T>::getLast() const {
    if (!Sequence<T>::length) {
        exception_sequenceIsEmpty e;
        throw e;
    }
    return tail->data;
}

template <typename T>
ListSequence<T>* ListSequence<T>::getSubSequence(int startIndex, int endIndex) const {
    if (endIndex < startIndex) {
        exception_incorrectSelection e;
        throw e;
    }
    if (endIndex >= Sequence<T>::length) {
        exception_outOfRange e;
        throw e;
    }
    ListSequence<T>* buff = new ListSequence<T>;
    for (int i = startIndex; i <= endIndex; i++) {
        buff->append(this->get(i));
    }
    return buff;
}

template <typename T>
void ListSequence<T>::append(T item) {
    Sequence<T>::length++;
    if (!(Sequence<T>::length - 1)) {
        head = new Node;
        head->next = nullptr;
        head->prev = nullptr;
        head->data = item;
        tail = head;
    }
    else {
        tail->next = new Node;
        tail->next->prev = tail;
        tail->next->next = nullptr;
        tail->next->data = item;
        tail = tail->next;
    }
}

template <typename T>
void ListSequence<T>::prepend(T item) {
    Sequence<T>::length++;
    if (!(Sequence<T>::length - 1)) {
        head = new Node;
        head->next = nullptr;
        head->prev = nullptr;
        head->data = item;
        tail = head;
    }
    else {
        head->prev = new Node;
        head->prev->next = head;
        head->prev->prev = nullptr;
        head->prev->data = item;
        head = head->prev;
    }
}

template <typename T>
void ListSequence<T>::insertAt(int index, T item) {
    if (index > Sequence<T>::length) {
        exception_outOfRange e;
        throw e;
    }
    Sequence<T>::length++;
    Node *tmp = nullptr;
    if (index < Sequence<T>::length/2) {
        tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
    }
    else {
        tmp = tail;
        for (int i = 0; i < Sequence<T>::length - index - 1; i++) {
            tmp = tmp->prev;
        }
    }
    Node *buff = new Node;
    buff->data = item;
    buff->next = tmp->next->prev;
    buff->prev = tmp;
    tmp->next->prev = buff;
    tmp->next = buff;
}

template <typename T>
void ListSequence<T>::remove(T item) {
    Node *tmp = head;
    while ((tmp != nullptr) && (tmp->data != item)) {
        tmp = tmp->next;
    }
    if (tmp != nullptr) {
        if (tmp == head) {
            head = tmp->next;
        }
        else if (tmp == tail) {
            tail = tmp->prev;
        }
        else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
        }
        delete tmp;
        Sequence<T>::length--;
    }
}

template <typename T>
void ListSequence<T>::replace(int index, T item) {
    if (index >= Sequence<T>::length) {
        exception_outOfRange e;
        throw e;
    }
    Node* tmp = nullptr;
    if (index < Sequence<T>::length/2) {
        tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
    }
    else {
        tmp = tail;
        for (int i = 0; i < Sequence<T>::length - index - 1; i++) {
            tmp = tmp->prev;
        }
    }
    tmp->data = item;
}

template <typename T>
ListSequence<T>::~ListSequence() {
    Node *tmp = nullptr;
    while (tmp != nullptr) {
        Node *next = tmp->next;
        delete tmp;
        tmp = next;
    }
    head = nullptr;
    tail = nullptr;
    Sequence<T>::length = 0;
}


