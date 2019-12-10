void swp(void *a, void *b);

template <typename K, typename T>
BPlus<K, T>::InterNode::InterNode(int max_degree)
{
    Node::max_degree = max_degree;
    Node::used_keys = 0;

    left = 0;
    right = 0;

    Node::keys = (K**)malloc((Node::max_degree - 1) * sizeof(K*));
    nodes = (Node**)malloc(Node::max_degree * sizeof(Node*));
}

template <typename K, typename T>
BPlus<K, T>::InterNode::~InterNode()
{
    Node **slots = nodes;
    for(int i = 0; i <= Node::used_keys; i++)
    {
        delete *nodes;
        nodes++;
    }
    free(slots);
    free(Node::keys);
}

template <typename K, typename T>
T &(BPlus<K, T>::InterNode::Get)(const K &key) const
{
    K **tmp = Node::keys;
    Node **slots = nodes;
    for(int i = 0; i < Node::used_keys; i++)
    {
        if(key < **tmp)
        {
            return (*slots)->Get(key);
        }

        tmp++;
        slots++;
    }

    //else
    return (*slots)->Get(key);
}

template <typename K, typename T>
bool BPlus<K, T>::InterNode::IsPresent(const K& key) const
{
    K **tmp = Node::keys;
    Node **slots = nodes;
    for(int i = 0; i < Node::used_keys; i++)
    {
        if(key < **tmp)
        {
            return (*slots)->IsPresent(key);
        }

        tmp++;
        slots++;
    }

    //else
    return (*slots)->IsPresent(key);
}

template <typename K, typename T>
typename BPlus<K, T>::Node *(BPlus<K, T>::InterNode::Set)(K &key, T &value)
{
    K **tmp = Node::keys;
    Node **slots = nodes;
    Node *new_node;
    bool found = 0;
    int i = 0;

    while((i < Node::used_keys) * (!found))
    {
        if(key < **tmp)
        {
            new_node = (*slots)->Set(key, value);
            found = 1;
        }

        tmp++;
        slots++;
        i++;
    }
    if(!found)
    {
        new_node = (*slots)->Set(key, value);

        tmp++;
        slots++;
        i++;
    }

    if(new_node)
    {
        if(Node::used_keys < (Node::max_degree - 1))
        {
            tmp--;
            K *kbuff = *tmp;
            Node *nbuff = *slots;
            *tmp = &(new_node->GetLeastKey());
            *slots = new_node;

            while(i <= Node::used_keys)
            {
                tmp++;
                slots++;
                i++;

                swp(tmp, kbuff);
                swp(slots, nbuff);
            }

            Node::used_keys++;

            return 0;
        }
        else
        {
            InterNode *yet_another_node = new InterNode(Node::max_degree);
            int border = (Node::used_keys - 1)/2;

            if((i - 1) <= border)
            {
                K *kbuff = *tmp;
                Node *nbuff = *slots;
                *tmp = &(new_node->GetLeastKey());
                *slots = new_node;

                while(i <= border)
                {
                    tmp++;
                    slots++;
                    i++;

                    swp(tmp, kbuff);
                    swp(slots, nbuff);
                }

                K **ksource = tmp + 1, **kdest = yet_another_node->Node::keys;
                Node **nsource = slots + 1, **ndest = yet_another_node->nodes;

                *ndest = nbuff;
                ndest++;

                while(i < Node::used_keys)
                {
                    *kdest = *ksource;
                    *ndest = *nsource;

                    kdest++;
                    ksource++;
                    ndest++;
                    nsource++;
                    i++;
                }

                yet_another_node->Node::used_keys = Node::max_degree/2;
                Node::used_keys = border + 1;

                return yet_another_node;
            }
            else
            {
                int j = border + 2;
                K **ksource = Node::keys + border + 2, **kdest = yet_another_node->Node::keys;
                Node **nsource = nodes + border + 2, **ndest = yet_another_node->nodes;

                if((i - 1) == j)
                {
                    *ndest = new_node;
                    ndest++;
                    ksource--;
                    j--;
                }
                else
                {
                    *ndest = *nsource;
                    *nsource++;
                    ndest++;
                    
                    while(j < (i - 1))
                    {
                        *kdest = *ksource;
                        *ndest = *nsource;

                        kdest++;
                        ksource++;
                        ndest++;
                        nsource++;
                        j++;
                    }

                    *kdest = &(new_node->GetLeastKey());
                    *ndest = new_node;

                    kdest++;
                    ndest++;
                }

                while(j < Node::used_keys)
                {
                    *kdest = *ksource;
                    *ndest = *nsource;

                    kdest++;
                    ksource++;
                    ndest++;
                    nsource++;
                    j++;
                }

                yet_another_node->Node::used_keys = Node::max_degree/2;
                Node::used_keys = border + 1;

                return yet_another_node;
            }
        }
    }
    else
    {
        return 0;
    }
    
}

template <typename K, typename T>
bool BPlus<K, T>::InterNode::Remove(const K &key)
{
    
}

template <typename K, typename T>
K &(BPlus<K, T>::InterNode::GetLeastKey)() const
{
    if(Node::used_keys)
    {
        return nodes[0]->GetLeastKey();
    }
    else
    {
        throw CIE();
    }
}

template <typename K, typename T>
typename BPlus<K, T>::Node *(BPlus<K, T>::InterNode::StartIterator)() const
{
    if(Node::used_keys)
    {
        return nodes[0]->StartIterator();
    }
    else
    {
        throw CIE();
    }
    
}