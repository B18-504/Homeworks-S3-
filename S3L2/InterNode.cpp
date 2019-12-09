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
        i++;
    }

    if(new_node)
    {
        if(Node::used_keys < (Node::max_degree - 1))
        {
            tmp--;
            K *kbuff = *tmp;
            Node *nbuff = *slots;
            *tmp = *(new_node->keys);
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
            int border = Node::used_keys/2;

            if((i - 1) <= border)
            {
                
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