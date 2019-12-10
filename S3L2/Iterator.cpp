#pragma once

template <typename K, typename T>
BPlus<K, T>::Iterator::Iterator(BPlus<K, T> &a)
{
    curr_node = a.StartIterator();
    curr_pos = 0;
}

template <typename K, typename T>
T &(BPlus<K, T>::Iterator::Get)() const
{
    return curr_node->GetI(curr_pos);
}

template <typename K, typename T>
K &(BPlus<K, T>::Iterator::GetKey)() const
{
    return curr_node->GetKey(curr_pos);
}

template <typename K, typename T>
bool BPlus<K, T>::Iterator::HasNext() const
{
    return curr_node->HasNext(curr_pos);
}

template <typename K, typename T>
bool BPlus<K, T>::Iterator::HasPrev() const
{
    return curr_node->HasPrev(curr_pos);
}

template <typename K, typename T>
void BPlus<K, T>::Iterator::ShiftLeft()
{
    curr_node = curr_node->ShiftLeft(curr_pos);
}

template <typename K, typename T>
void BPlus<K, T>::Iterator::ShiftRight()
{
    curr_node = curr_node->ShiftRight(curr_pos);
}