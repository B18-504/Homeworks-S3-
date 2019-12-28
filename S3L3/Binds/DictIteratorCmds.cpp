template <typename K, typename T>
void StartIterator(void ***argv)
{
    if(*(argv[0]))
    {
        if(*(argv[1]))
        {
            delete (typename Dict<K, T>::Iterator*)(*(argv[1]));
        }
        *(argv[1]) = &(((Dict<K, T>*)(*(argv[0])))->StartIterator());
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void IteratorGet(void ***argv)
{
    if(*(argv[0]))
    {
        *(T*)argv[1] = ((typename Dict<K, T>::Iterator*)(*(argv[0])))->Get();
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void IteratorGetKey(void ***argv)
{
    if(*(argv[0]))
    {
        *(K*)argv[1] = ((typename Dict<K, T>::Iterator*)(*(argv[0])))->GetKey();
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void IteratorSet(void ***argv)
{
    if(*(argv[0]))
    {
        ((typename Dict<K, T>::Iterator*)(*(argv[0])))->Set(*(T*)argv[1]);
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void IteratorHasNext(void ***argv)
{
    if(*(argv[0]))
    {
        *(T*)argv[1] = ((typename Dict<K, T>::Iterator*)(*(argv[0])))->HasNext();
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void IteratorHasPrev(void ***argv)
{
    if(*(argv[0]))
    {
        *(T*)argv[1] = ((typename Dict<K, T>::Iterator*)(*(argv[0])))->HasPrev();
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void IteratorShiftLeft(void ***argv)
{
    if(*(argv[0]))
    {
        ((typename Dict<K, T>::Iterator*)(*(argv[0])))->ShiftLeft();
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void IteratorShiftRight(void ***argv)
{
    if(*(argv[0]))
    {
        ((typename Dict<K, T>::Iterator*)(*(argv[0])))->ShiftRight();
    }
    else
    {
        throw NPE();
    }
}