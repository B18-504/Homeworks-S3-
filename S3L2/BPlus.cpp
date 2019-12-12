template <typename T>
inline void swp(T *&a, T *&b)
{
    T *c = a;
    a = b;
    b = c;
}

template <typename K, typename T>
BPlus<K, T>::BPlus(int max_degree)
{
    this->max_degree = max_degree;
    head = new EndNode(max_degree);
    count = 0;
}

template <typename K, typename T>
BPlus<K, T>::~BPlus()
{
    delete head;
}

template <typename K, typename T>
T &(BPlus<K, T>::Get)(const K &key) const
{
    return head->Get(key);
}

template <typename K, typename T>
bool (BPlus<K, T>::IsPresent)(const K &key) const
{
    return head->IsPresent(key);
}

template <typename K, typename T>
int BPlus<K, T>::GetCount() const
{
    return count;
}

template <typename K, typename T>
void BPlus<K, T>::Set(const K &key, const T &value)
{
    if(!IsPresent(key))                             //to be removed
    {
        count++;
    }


    Node *new_node = head->Set(*new K(key), *new T(value));
    if(new_node)
    {
        InterNode *new_head = new InterNode(max_degree);
        new_head->Node::keys[0] = &(new_node->GetLeastKey());
        new_head->nodes[0] = head;
        new_head->nodes[1] = new_node;
        head = new_head;
        head->used_keys = 1;
    }
}

template <typename K, typename T>
void BPlus<K, T>::Remove(const K &key)
{
    bool need_merging = head->Remove(key);
}

template <typename K, typename T>
typename BPlus<K, T>::Node *(BPlus<K, T>::StartIterator)() const
{
    return head->StartIterator();
}