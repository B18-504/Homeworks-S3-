template <typename K, typename T>
BPlus<K, T>::EndNode::EndNode(int max_degree)
{
    Node::max_degree = max_degree;
    Node::used_keys = 0;

    left = 0;
    right = 0;

    Node::keys = (K**)malloc((Node::max_degree - 1) * sizeof(K*));
    values = (T**)malloc((Node::max_degree - 1) * sizeof(T*));
}

template <typename K, typename T>
BPlus<K, T>::EndNode::~EndNode()
{
    for(int i = 0; i < Node::used_keys; i++)
    {
        K **tmp = Node::keys;
        T **slots = values;

        delete *(Node::keys);
        delete *values;
        Node::keys++;
        values++;

        free(tmp);
        free(slots);
    }
}

template <typename K, typename T>
typename BPlus<K, T>::Node *(BPlus<K, T>::EndNode::Set)(K &key, T &value)
{
    if(Node::used_keys < (Node::max_degree - 1))
    {
        K **tmp = Node::keys;
        T **slot = values;
        int i = 0;
        bool found_pos = 0;

M:      if(i == Node::used_keys)                                   //forever cycle begins                
        {
            Node::used_keys++;
            *slot = &value;
            *tmp = &key;

            return 0;                                               //every key is less, so the new is the last
        }
        else if(**tmp == key)
        {
            *slot = &value;

            return 0;                                               //found the same key, replaced the value
        }
        else if(**tmp > key)
        {
            T *vbuff = *slot;
            K *kbuff = *tmp;
            *slot = &value;
            *tmp = &key;

            while(i < Node::used_keys)
            {
                slot++;
                tmp++;
                i++;
                swp(*slot, vbuff);
                swp(*tmp, kbuff);
            }

            Node::used_keys++;

            return 0;                                               //found greater keys, moved them forward
        }
        else
        {
            slot++;
            tmp++;
            i++;
            goto M;                                                 //going on
        }
    }
    else        //if used keys == max_degree - 1, aka node is full
    {
        int i = 0;
        K **tmp = Node::keys;
        T **slot = values;

        {
N:          if(i == Node::used_keys)                                   //forever cycle begins                
            {
                EndNode *new_node = new EndNode(Node::max_degree);
                int border = (Node::used_keys)/2;

                K **ksource = Node::keys + border + 1, **kdest = new_node->Node::keys;
                T **vsource = values + border + 1, **vdest = new_node->values;

                for(int i = border + 1; i < Node::used_keys; i++)      //transfering the elder half of pairs to the new node
                {
                    *kdest = *ksource;
                    *vdest = *vsource;

                    kdest++;
                    ksource++;
                    vdest++;
                    vsource++;
                }

                *kdest = &key;
                *vdest = &value;

                new_node->right = right;
                new_node->left = this;
                right = new_node;

                Node::used_keys = (Node::max_degree + 1)/2;
                new_node->Node::used_keys = Node::max_degree/2;

                return new_node;                                               //splited the node
            }
            else if(**tmp == key)
            {
                *slot = &value;

                return 0;                                               //found the same key, replaced the value
            }
            else if(**tmp > key)
            {
                EndNode *new_node = new EndNode(Node::max_degree);
                int border = Node::used_keys/2;

                K **kdest, **ksource;
                T **vdest, **vsource;

                if(i <= border)
                {
                    T *vbuff = *slot;
                    K *kbuff = *tmp;
                    *slot = &value;
                    *tmp = &key;

                    while(i < border)
                    {
                        slot++;
                        tmp++;
                        i++;
                        swp(*slot, vbuff);
                        swp(*tmp, kbuff);
                    }

                    new_node->Node::keys[0] = kbuff;
                    new_node->values[0] = vbuff;

                    kdest = new_node->Node::keys + 1;
                    ksource = tmp + 1;
                    vdest = new_node->values + 1;
                    vsource = slot + 1;
                }
                else
                {
                    ksource = Node::keys + border + 1;
                    kdest = new_node->Node::keys;
                    vsource = values + border + 1;
                    vdest = new_node->values;

                    for(int j = border + 1; j < i; j++)
                    {
                        *kdest = *ksource;
                        *vdest = *vsource;

                        kdest++;
                        ksource++;
                        vdest++;
                        vsource++;
                    }

                    *kdest = &key;
                    *vdest = &value;

                    kdest++;
                    vdest++;
                }

                while(i < Node::used_keys)
                {
                    *kdest = *ksource;
                    *vdest = *vsource;

                    kdest++;
                    ksource++;
                    vdest++;
                    vsource++;
                }

                Node::used_keys = (Node::max_degree + 1)/2;
                new_node->Node::used_keys = Node::max_degree/2;

                new_node->right = right;
                new_node->left = this;
                right = new_node;

                return new_node;                                         //found greater keys, moved them forward
            }
            else
            {
                slot++;
                tmp++;
                i++;
                goto N;                                                 //going on
            }
        }
    } 
}

template <typename K, typename T>
T &(BPlus<K, T>::EndNode::Get)(const K &key) const
{
    int i = 0;
    K **tmp = Node::keys;
    T **slot = values;

    while(1)
    {
        if(i == Node::used_keys)
        {
            throw KNF();
        }
        else if(**tmp == key)
        {
            return **slot;
        }
        else
        {
            slot++;
            tmp++;
            i++;
        }
    }
}

template <typename K, typename T>
bool (BPlus<K, T>::EndNode::IsPresent)(const K &key) const
{
    int i = 0;
    K **tmp = Node::keys;

    while(1)
    {
        if(i == Node::used_keys)
        {
            return 0;
        }
        else if(**tmp == key)
        {
            return 1;
        }
        else
        {
            tmp++;
            i++;
        }
    }
}

template <typename K, typename T>
bool BPlus<K, T>::EndNode::Remove(const K &key)
{
    K **tmp = Node::keys;
    T **slots = values;
    int i = 0;

M:  if(i == Node::used_keys)
    {
        return 0;
    }
    else if(**tmp == key)
    {
        delete *slots;
        delete *tmp;
        i++;

        while(i < Node::used_keys)
        {
            *slots = *(slots + 1);
            *tmp = *(tmp + 1);
            
            slots++;
            tmp++;
            i++;
        }

        Node::used_keys--;

        if(Node::used_keys < ((Node::max_degree - 1)/2))
        {
            return 1;
        }
    }
    else
    {
        tmp++;
        slots++;
        i++;
        goto M;
    }   
}

template <typename K, typename T>
K &(BPlus<K, T>::EndNode::GetLeastKey)() const
{
    if(Node::used_keys)
    {
        return *(Node::keys[0]);
    }
    else
    {
        throw CIE();
    }
}

template <typename K, typename T>
typename BPlus<K, T>::Node *(BPlus<K, T>::EndNode::StartIterator)() const
{
    return this;
}

template <typename K, typename T>
typename BPlus<K, T>::EndNode *(BPlus<K, T>::EndNode::ShiftLeft)(int &pos) const
{
    if(pos > 0)
    {
        pos--;
        return this;
    }
    else if(left)
    {
        pos = left->Node::used_keys - 1;
        return left;
    }
    else
    {
        throw OoR();
    }
}

template <typename K, typename T>
typename BPlus<K, T>::EndNode *(BPlus<K, T>::EndNode::ShiftRight)(int &pos) const
{
    if(pos < (Node::used_keys - 1))
    {
        pos++;
        return this;
    }
    else if(right)
    {
        pos = 0;
        return right;
    }
    else
    {
        throw OoR();
    }
}

template <typename K, typename T>
bool BPlus<K, T>::EndNode::HasPrev(int pos) const
{
    return((pos > 0) + bool(left));
}

template <typename K, typename T>
bool BPlus<K, T>::EndNode::HasNext(int pos) const
{
    return((pos < (Node::used_keys - 1)) + bool(right));
}

template <typename K, typename T>
T &(BPlus<K, T>::EndNode::GetI)(int pos) const
{
    return(*(values[pos]));
}

template <typename K, typename T>
K &(BPlus<K, T>::EndNode::GetKey)(int pos) const
{
    return(*(Node::keys[pos]));
}