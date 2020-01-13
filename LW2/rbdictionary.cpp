#include "rbdictionary.hpp"
#include <queue>

template <typename TKey, typename TElement>
RBDictionary<TKey, TElement>::Node::Node(const TKey& key, const TElement& item) {
    left = right = parent = nullptr;
    this->color = RED;
    this->data = std::make_pair(key, item);
}

template <typename TKey, typename TELement>
typename RBDictionary<TKey, TELement>::Node* RBDictionary<TKey, TELement>::Node::find(Node* ptr, const TKey& key) {
    if (ptr != nullptr) {
        if (key < ptr->data.first)
            return find(ptr->left, key);
        else if (key > ptr->data.first)
            return find(ptr->right, key);
        else if (key == ptr->data.first)
            return ptr;
    }
    return nullptr;
}

template <typename TKey, typename TElement>
TElement& RBDictionary<TKey, TElement>::Node::getPair(const TKey& key) {
    if (this == nullptr) {
        exception_missingKey e;
        throw e;
    }
    if (key < this->data.first)
        return this->left->getPair(key);
    if (key > this->data.first)
        return this->right->getPair(key);
    return data.second;
}

template <typename TKey, typename TELement>
typename RBDictionary<TKey, TELement>::Node* RBDictionary<TKey, TELement>::Node::insertBST(Node*& root, Node*& ptr) {
    if (!root)
        return ptr;
    if (ptr->data.first < root->data.first) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    }
    else if (ptr->data.first > root->data.first) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }
    else if (ptr->data.first == root->data.first) {
    }
    return root;
}

template <typename TKey, typename TELement>
typename RBDictionary<TKey, TELement>::Node* RBDictionary<TKey, TELement>::Node::removeBST(Node*& ptr, const TKey& key) {
    if (!ptr) {
        exception_missingKey e;
        throw e;
    }
    if (key < ptr->data.first)
        return removeBST(ptr->left, key);
    if (key > ptr->data.first)
        return removeBST(ptr->right, key);
    if (!ptr->right || !ptr->left) {
        return ptr;
    }
    Node* successor = ptr->left;
    while (successor->right) {
        successor = successor->right;
    }
    std::swap(ptr->data, successor->data);
    return successor;
}

template <typename TKey, typename TElement>
int RBDictionary<TKey, TElement>::Node::getColor(Node* ptr) {
    if (ptr == nullptr)
        return BLACK;
    return ptr->color;
}

template <typename TKey, typename TElement>
void RBDictionary<TKey, TElement>::Node::setColor(Node*& ptr, const int& color) {
    if (ptr == nullptr)
        return;
    ptr->color = color;
}

template <typename TKey, typename TElement>
void RBDictionary<TKey, TElement>::Node::deleteNodes(Node*& ptr) {
    if (ptr != nullptr) {
        deleteNodes(ptr->left);
        deleteNodes(ptr->right);
        delete ptr;
        ptr = nullptr;
    }
}




template <typename TKey, typename TElement>
RBDictionary<TKey, TElement>::RBDictionary() {
    this->root = nullptr;
    IDictionary<TKey, TElement>::count = 0;
}

template <typename TKey, typename TElement>
RBDictionary<TKey, TElement>::RBDictionary(const RBDictionary& dictionary) {
    this->root = nullptr;
    IDictionary<TKey, TElement>::count = 0;
    Node* ptr = dictionary.root;
    std::queue<Node*> queue;
    queue.push(ptr);
    while (queue.size() != 0) {
        Node* next = queue.front();
        this->insert(next->data.first, next->data.second);
        queue.pop();
        if (next->left)
            queue.push(next->left);
        if (next->right)
            queue.push(next->right);
    }
}

template <typename TKey, typename TElement>
RBDictionary<TKey, TElement>& RBDictionary<TKey, TElement>::operator=(const RBDictionary& dictionary) {
    this->~RBDictionary();
    IDictionary<TKey, TElement>::count = 0;
    Node* ptr = dictionary.root;
    std::queue<Node*> queue;
    queue.push(ptr);
    while (queue.size() != 0) {
        Node* next = queue.front();
        this->insert(next->data.first, next->data.second);
        queue.pop();
        if (next->left)
            queue.push(next->left);
        if (next->right)
            queue.push(next->right);
    }
    return *this;
}

template <typename TKey, typename TElement>
TElement& RBDictionary<TKey, TElement>::operator[](const TKey& key) {
    return this->root->getPair(key);
}

template <typename TKey, typename TELement>
int RBDictionary<TKey, TELement>::getCount() const {
    return IDictionary<TKey, TELement>::count;
}

template <typename TKey, typename TELement>
TELement RBDictionary<TKey, TELement>::get(const TKey& key) const {
    Node* tmp = Node::find(this->root, key);
    if (!tmp) {
        exception_missingKey e;
        throw e;
    }
    return tmp->data.second;
}

template <typename TKey, typename TELement>
bool RBDictionary<TKey, TELement>::containsKey(const TKey& key) const {
    Node* tmp = Node::find(this->root, key);
    return tmp ? true : false;
}

template <typename TKey, typename TELement>
void RBDictionary<TKey, TELement>::insert(const TKey& key, const TELement& item) {
    Node* ptr = new Node(key, item);
    this->root = Node::insertBST(root, ptr);
    this->fixInsert(ptr);
    IDictionary<TKey, TELement>::count++;
}

template <typename TKey, typename TELement>
void RBDictionary<TKey, TELement>::fixInsert(Node*& ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && Node::getColor(ptr) == RED && Node::getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (uncle != nullptr && Node::getColor(uncle) == RED) {
                grandparent->color = RED;
                uncle->color = BLACK;
                parent->color = BLACK;
                ptr = grandparent;
            }
            else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                std::swap(grandparent->color, parent->color);
                ptr = parent;
            }
        }
        else {
            Node *uncle = grandparent->left;
            if (uncle != nullptr && Node::getColor(uncle) == RED) {
                grandparent->color = RED;
                uncle->color = BLACK;
                parent->color = BLACK;
                ptr = grandparent;
            }
            else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                std::swap(grandparent->color, parent->color);
                ptr = parent;
            }
        }
    }
    Node::setColor(root, BLACK);
}

template <typename TKey, typename TELement>
void RBDictionary<TKey, TELement>::remove(const TKey& key) {
    Node* ptr = Node::removeBST(this->root, key);
    if (ptr != nullptr)
        this->fixRemove(ptr);
    IDictionary<TKey, TELement>::count--;
}

template <typename TKey, typename TELement>
void RBDictionary<TKey, TELement>::fixRemove(Node*& ptr) {
    if (ptr == this->root) {
        delete this->root;
        this->root = nullptr;
        return;
    }
    Node* v = ptr;
    Node* u = nullptr;
    if (v->left && !v->right)
        u = v->left;
    else
        u = v->right;
    if (v->parent->left == v)
        v->parent->left = u;
    else
        v->parent->right = u;
    if ((Node::getColor(v) == RED && Node::getColor(u) == BLACK) || (Node::getColor(v) == BLACK && Node::getColor(u) == RED)) {
        Node::setColor(u, BLACK);
        delete v;
        v = nullptr;
    }
    else if (Node::getColor(v) == BLACK && Node::getColor(u) == BLACK) {
        Node* w = nullptr;
        if (v->parent->left == u)
            w = v->parent->right;
        else
            w = v->parent->left;
        Node::setColor(u, DOUBLEBLACK);
        while (Node::getColor(u) == DOUBLEBLACK || u == v->left || u == v->right) {
            if (Node::getColor(w) == BLACK && (Node::getColor(w->left) == RED || Node::getColor(w->right) == RED)) {
                if (w->parent->left == w) {
                    if (Node::getColor(w->right) == RED && Node::getColor(w->left) == BLACK) {
                        rotateLeft(w->right);
                    }
                    rotateRight(w->parent);
                    Node::setColor(w->left, BLACK);
                    std::swap(w->color, w->right->color);
                }
                else if (w->parent->right == w) {
                    if (Node::getColor(w->left) == RED && Node::getColor(w->right) == BLACK) {
                        rotateRight(w->left);
                    }
                    rotateLeft(w->parent);
                    Node::setColor(w->right, BLACK);
                    std::swap(w->color, w->left->color);
                }
                Node::setColor(u, BLACK);
                break;
            }
            else if (Node::getColor(w) == BLACK && Node::getColor(w->left) == BLACK && Node::getColor(w->right) == BLACK) {
                Node::setColor(u, BLACK);
                Node::setColor(w, RED);
                if (Node::getColor(w->parent) == RED)
                    Node::setColor(w->parent, BLACK);
                else {
                    Node::setColor(w->parent, DOUBLEBLACK);
                    u = w->parent;
                    if (u->parent->left == u)
                        w = u->parent->right;
                    else
                        w = u->parent->left;
                }
            }
            else if (Node::getColor(w) == RED) {
                std::swap(w->parent->color, w->color);
                if (w->parent->left == w) {
                    rotateRight(w->parent);
                    w = w->right->left;
                }
                else {
                    rotateLeft(w->parent);
                    w = w->left->right;
                }
            }
        }
        delete v;
        v = nullptr;
    }
}

template <typename TKey, typename TELement>
void RBDictionary<TKey, TELement>::rotateLeft(Node* ptr) {
    if (ptr->right != nullptr) {
        Node* right_child = ptr->right;
        ptr->right = right_child->left;
        
        if (ptr->right != nullptr)
            ptr->right->parent = ptr;
        
        right_child->parent = ptr->parent;
        
        if (ptr->parent == nullptr)
            root = right_child;
        else if (ptr == ptr->parent->left) //левый потомок
            ptr->parent->left = right_child;
        else //правый потомок
            ptr->parent->right = right_child;
        
        right_child->left = ptr;
        ptr->parent = right_child;
    }
}

template <typename TKey, typename TELement>
void RBDictionary<TKey, TELement>::rotateRight(Node* ptr) {
    if (ptr->left != nullptr) {
        Node* left_child = ptr->left;
        ptr->left = left_child->right;
        
        if (ptr->left != nullptr)
            ptr->left->parent = ptr;
        
        left_child->parent = ptr->parent;
        
        if (ptr->parent == nullptr)
            root = left_child;
        else if (ptr == ptr->parent->left) //левый потомок
            ptr->parent->left = left_child;
        else //правый потомок
            ptr->parent->right = left_child;
        
        left_child->right = ptr;
        ptr->parent = left_child;
    }
}

template <typename TKey, typename TELement>
RBDictionary<TKey, TELement>::~RBDictionary() {
    Node::deleteNodes(this->root);
};






/* DICTIONARY ITERATOR REALISATION */

template <typename TKey, typename TElement>
RBDictionary<TKey, TElement>::DictionaryIterator::DictionaryIterator(Node* pos): pos(pos) {}

template <typename TKey, typename TElement>
RBDictionary<TKey, TElement>::DictionaryIterator::DictionaryIterator(const DictionaryIterator& it): pos(it.pos) {}

template <typename TKey, typename TElement>
typename RBDictionary<TKey, TElement>::DictionaryIterator& RBDictionary<TKey, TElement>::DictionaryIterator::operator=(const DictionaryIterator& it) {
    this->pos = it.pos;
    return *this;
}

template <typename TKey, typename TElement>
typename RBDictionary<TKey, TElement>::DictionaryIterator::reference RBDictionary<TKey, TElement>::DictionaryIterator::operator*() const {
    return this->pos->data;
}

template <typename TKey, typename TElement>
typename RBDictionary<TKey, TElement>::DictionaryIterator::pointer RBDictionary<TKey, TElement>::DictionaryIterator::operator->() const {
    return this->pos;
}

template <typename TKey, typename TElement>
volatile typename RBDictionary<TKey, TElement>::DictionaryIterator RBDictionary<TKey, TElement>::DictionaryIterator::operator++(int) {
    if (this->pos->right) {
        this->pos = this->pos->right;
        while (this->pos->left != nullptr) {
            this->pos = this->pos->left;
        }
    }
    else {
        while (this->pos->parent && this->pos->data.first > this->pos->parent->data.first)
            this->pos = this->pos->parent;
        if (!this->pos->parent)
            this->pos = nullptr;
        else
            this->pos = this->pos->parent;
    }
    return DictionaryIterator(this->pos);
}

template <typename TKey, typename TElement>
volatile typename RBDictionary<TKey, TElement>::DictionaryIterator& RBDictionary<TKey, TElement>::DictionaryIterator::operator++() {
    if (this->pos->right) {
        this->pos = this->pos->right;
        while (this->pos->left != nullptr) {
            this->pos = this->pos->left;
        }
    }
    else {
        while (this->pos->parent && this->pos->data.first > this->pos->parent->data.first)
            this->pos = this->pos->parent;
        if (!this->pos->parent)
            this->pos = nullptr;
        else
            this->pos = this->pos->parent;
    }
    return *this;
}

template <typename TKey, typename TElement>
bool RBDictionary<TKey, TElement>::DictionaryIterator::operator!=(const DictionaryIterator& it) const {
    return this->pos != it.pos;
}

template <typename TKey, typename TElement>
bool RBDictionary<TKey, TElement>::DictionaryIterator::operator==(const DictionaryIterator& it) const {
    return this->pos == it.pos;
}

template <typename TKey, typename TElement>
RBDictionary<TKey, TElement>::DictionaryIterator::~DictionaryIterator() {
    this->pos = nullptr;
}

/* DICTIONARY ITERATOR BEGIN//END REALISATION */

template <typename TKey, typename TElement>
typename RBDictionary<TKey, TElement>::iterator RBDictionary<TKey, TElement>::begin() {
    if (!this->root) return DictionaryIterator(nullptr);
    RBDictionary::Node* minNode = this->root;
    while (minNode->left)
        minNode = minNode->left;
    return DictionaryIterator(minNode);
}

template <typename TKey, typename TElement>
typename RBDictionary<TKey, TElement>::iterator RBDictionary<TKey, TElement>::end() {
    return DictionaryIterator(nullptr);
}

template <typename TKey, typename TElement>
typename RBDictionary<TKey, TElement>::const_iterator RBDictionary<TKey, TElement>::begin() const {
    if (!this->root) return DictionaryIterator(nullptr);
    RBDictionary::Node* minNode = this->root;
    while (minNode->left)
        minNode = minNode->left;
    return DictionaryIterator(minNode);
}

template <typename TKey, typename TElement>
typename RBDictionary<TKey, TElement>::const_iterator RBDictionary<TKey, TElement>::end() const {
    return DictionaryIterator(nullptr);
}
