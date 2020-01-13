#ifndef rbdictionary_hpp
#define rbdictionary_hpp

#include <iostream>
#include "idictionary.hpp"
#include "exceptions.hpp"

template <typename TKey, typename TElement>
class RBDictionary : public IDictionary<TKey, TElement> {
private:
    struct Node {
        friend class RBDictionary;
        std::pair<TKey, TElement> data;
        int color;
        Node *left, *right, *parent;
        Node(const TKey& key, const TElement& item);
        static Node* find(Node* ptr, const TKey& key);
        TElement& getPair(const TKey& key);
        static Node* insertBST(Node*& root, Node*& ptr);
        static Node* removeBST(Node*& ptr, const TKey& key);
        static int getColor(Node* ptr);
        static void setColor(Node*& ptr, const int& color);
        static void deleteNodes(Node*& ptr);
    };
private:
    Node* root;
private:
    void fixInsert(Node*& ptr);
    void fixRemove(Node*& ptr);
    void rotateLeft(Node* ptr);
    void rotateRight(Node* ptr);
public:
    RBDictionary();
    RBDictionary(const RBDictionary& dictionary);
    RBDictionary& operator=(const RBDictionary& dictionary);
    TElement& operator[](const TKey& key);
    virtual int getCount() const override;
    TElement get(const TKey& key) const;
    virtual bool containsKey(const TKey& key) const override;
    virtual void insert(const TKey& key, const TElement& item) override;
    virtual void remove(const TKey& key) override;
    ~RBDictionary();
private:
    class DictionaryIterator : public std::iterator<std::forward_iterator_tag, std::pair<TKey, TElement>> {
        friend class RBDictionary;
        private:
            Node* pos;
            DictionaryIterator(Node* pos);
        public:
            DictionaryIterator(const DictionaryIterator &it);
            ~DictionaryIterator();
        public:
            DictionaryIterator& operator=(const DictionaryIterator& it);
            typename DictionaryIterator::reference operator*() const;
            typename DictionaryIterator::pointer operator->() const;
            volatile DictionaryIterator operator++(int);
            volatile DictionaryIterator& operator++();
            bool operator!=(const DictionaryIterator& it) const;
            bool operator==(const DictionaryIterator& it) const;
    };
public:
    typedef DictionaryIterator iterator;
    typedef DictionaryIterator const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};





#endif
