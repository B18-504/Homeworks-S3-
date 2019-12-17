template <typename K, typename T>
void StartBPlusDict(void ***argv)
{
    if(*(argv[0]))
    {
        delete (Dict<K, T>*)(*(argv[0]));
    }
    (*(argv[0])) = new BPlusDict<K, T>(*(int*)(argv[1]));
}

template <typename K, typename T>
void DictGetCount(void ***argv)
{
    if(*(argv[0]))
    {
        *(int*)(argv[1]) = ((Dict<K, T>*)(*(argv[0])))->GetCount();
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void DictCurrentCap(void ***argv)
{
    if(*(argv[0]))
    {
        *(int*)(argv[1]) = ((Dict<K, T>*)(*(argv[0])))->CurrentCap();
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void DictIsPresent(void ***argv)
{
    if(*(argv[0]))
    {
        *(int*)(argv[2]) = ((Dict<K, T>*)(*(argv[0])))->IsPresent(*(K*)(argv[1]));
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void DictGet(void ***argv)
{
    if(*(argv[0]))
    {
        *(T*)(argv[2]) = ((Dict<K, T>*)(*(argv[0])))->Get(*(K*)(argv[1]));
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void DictSet(void ***argv)
{
    if(*(argv[0]))
    {
        ((Dict<K, T>*)(*(argv[0])))->Set(*(K*)(argv[1]), *(T*)(argv[2]));
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void DictRemove(void ***argv)
{
    if(*(argv[0]))
    {
        ((Dict<K, T>*)(*(argv[0])))->Remove(*(K*)(argv[1]));
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void InputDict(void ***argv)
{
    if(*(argv[0]))
    {
        Input(*(Dict<K, T>*)*(argv[0]));
    }
    else
    {
        throw NPE();
    }
}

template <typename K, typename T>
void PrintDict(void ***argv)
{
    if(*(argv[0]))
    {
        Print(*(Dict<K, T>*)*(argv[0]));
    }
    else
    {
        throw NPE();
    }
}

void AlphaIndex(void ***argv)
{
    if(bool(*(argv[2])) * bool(*(argv[0])))
    {
        CreateAlphaIndex(*(Dict<String, int>*)(*(argv[0])), (FILE*)(*(argv[2])), *(int*)argv[1]);
    }
    else
    {
        throw NPE();
    }
}