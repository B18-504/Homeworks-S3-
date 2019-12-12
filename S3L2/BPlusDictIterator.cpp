#pragma once

template <typename K, typename T>
BPlusDict<K, T>::BPlusDictIterator::BPlusDictIterator(const BPlusDict<K, T> &a)
{
    body = new typename BPlus<K, T>::Iterator(*(a.body));
}

template <typename K, typename T>
BPlusDict<K, T>::BPlusDictIterator::~BPlusDictIterator()
{
    delete body;
}

template <typename K, typename T>
T &(BPlusDict<K, T>::BPlusDictIterator::Get)() const
{
    return body->Get();
}

template <typename K, typename T>
K &(BPlusDict<K, T>::BPlusDictIterator::GetKey)() const
{
    return body->GetKey();
}

template <typename K, typename T>
bool BPlusDict<K, T>::BPlusDictIterator::HasNext() const
{
    return body->HasNext();
}

template <typename K, typename T>
bool BPlusDict<K, T>::BPlusDictIterator::HasPrev() const
{
    return body->HasPrev();
}

template <typename K, typename T>
void BPlusDict<K, T>::BPlusDictIterator::ShiftLeft()
{
    return body->ShiftLeft();
}

template <typename K, typename T>
void BPlusDict<K, T>::BPlusDictIterator::ShiftRight()
{
    return body->ShiftRight();
}