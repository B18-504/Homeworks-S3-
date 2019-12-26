template <typename T>
void swp(T *&a, T *&b);

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
bool BPlus<K, T>::InterNode::PopFirst(K *&key, T *&value)
{
    if(Node::used_keys)
    {
        bool element_requested = nodes[0]->PopFirst(key, value);
        if(element_requested)
        {
            if(nodes[1]->Node::used_keys > (Node::max_degree - 1)/2)
            {
                nodes[0]->TakeValRight(nodes[1]->ShareValRight());
                nodes[0]->TakeKeyRight(*(Node::keys[0]));
                Node::keys[0] = &(nodes[1]->ShareKeyRight());

                return 0;
            }
            else
            {
                nodes[0]->Absorb(nodes[1]);
                
                for(int i = 1; i < (Node::used_keys - 1); i++)
                {
                    Node::keys[i] = Node::keys[i+1];
                    nodes[i] = nodes[i+1];
                }
                nodes[Node::used_keys - 1] = nodes[Node::used_keys];
                Node::used_keys--;
            }
        }
        else
        {
            return 0;
        }  
    }
    else
    {
        throw CIE();
    }
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
typename BPlus<K, T>::Node *(BPlus<K, T>::InterNode::Add)(K &key, T &value)
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
            new_node = (*slots)->Add(key, value);
            found = 1;
        }

        tmp++;
        slots++;
        i++;
    }
    if(!found)
    {
        new_node = (*slots)->Add(key, value);

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

                swp(*tmp, kbuff);
                swp(*slots, nbuff);
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
                tmp--;
                K *kbuff = *tmp;
                Node *nbuff = *slots;
                *tmp = &(new_node->GetLeastKey());
                *slots = new_node;

                while(i <= border)
                {
                    tmp++;
                    slots++;
                    i++;

                    swp(*tmp, kbuff);
                    swp(*slots, nbuff);
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


                Node::used_keys = border + 1;
                yet_another_node->Node::used_keys = Node::max_degree - Node::used_keys - 1;

                return yet_another_node;
            }
            else
            {
                int j = border + 2;
                K **ksource = Node::keys + border + 2, **kdest = yet_another_node->Node::keys;
                Node **nsource = nodes + border + 2, **ndest = yet_another_node->nodes;

                if(i == j)
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

                Node::used_keys = border + 1;
                yet_another_node->Node::used_keys = Node::max_degree - Node::used_keys - 1;

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

template <typename K, typename T>
K &(BPlus<K, T>::InterNode::ShareKeyRight)()
{
    K *result = Node::keys[0];
    for(int i = 0; i < (Node::used_keys - 1); i++)
    {
        Node::keys[i] = Node::keys[i+1];
    }
    Node::used_keys--;

    return *result;
}

template <typename K, typename T>
void *(BPlus<K, T>::InterNode::ShareValRight)()
{
    void *result = nodes[0];
    for(int i = 0; i < (Node::used_keys); i++)
    {
        nodes[i] = nodes[i+1];
    }

    return result;
}

template <typename K, typename T>
void BPlus<K, T>::InterNode::TakeValRight(void* node_ptr)
{
    nodes[Node::used_keys + 1] = node_ptr;
}

template <typename K, typename T>
bool BPlus<K, T>::InterNode::RootToBeRemoved() const
{
    return(Node::used_keys == 0);
}

template <typename K, typename T>
void BPlus<K, T>::InterNode::Absorb(Node *next)
{
    nodes[Node::used_keys+1] = ((InterNode*)next)->nodes[0];
    Node::keys[Node::used_keys] = &(nodes[Node::used_keys+1]->GetLeastKey());       //to be replaced
    Node::used_keys++;

    for(int i = Node::used_keys; i < (Node::used_keys + next->used_keys); i++)
    {
        Node::keys[i] = next->keys[i-Node::used_keys];
        nodes[i+1] = ((InterNode*)next)->nodes[i+1-Node::used_keys];
    }

    Node::used_keys += next->used_keys;
    
    next->used_keys = 0;
    delete next;
}