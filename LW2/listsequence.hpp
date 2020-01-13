#ifndef listsequence_hpp
#define listsequence_hpp

#include "isequence.hpp"

template <typename T>
class ListSequence: public ISequence<T> {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
public:
    ListSequence();
    ListSequence(ISequence<T>* sequence);
    ListSequence(int n, int leftLimit, int rightLimit);
    ListSequence<T>& operator=(const ListSequence<T>& sequence);
    ~ListSequence(); 
public:
    virtual int getLength() const override;
    virtual bool getIsEmpty() const override;
public:
    virtual T get(const int& index) const override;
    virtual T getFirst() const override;
    virtual T getLast() const override;
    virtual ListSequence<T>* getSubSequence(const int& startIndex, const int& endIndex) const override;
    virtual void append(const T& item) override;
    virtual void prepend(const T& item) override;
    virtual void insertAt(const int& index, const T& item) override;
    virtual void remove(const T& item) override;
    virtual void set(const int& index, const T& item) override;
    template <typename ...F>
    static ListSequence<T>* listSequenceOf(const F&... items);
private:
    class MyIterator: public std::iterator<std::forward_iterator_tag, T> {
        friend class ListSequence;
    private:
        Node* pos;
        MyIterator(Node* pos);
    public:
        MyIterator(const MyIterator &it);
        ~MyIterator();
    public:
        MyIterator& operator=(const MyIterator& it);
        typename MyIterator::reference operator*() const;
        typename MyIterator::pointer operator->() const;
        MyIterator operator++(int);
        MyIterator& operator++();
        bool operator!=(const MyIterator& it) const;
        bool operator==(const MyIterator& it) const;
    };
public:
    typedef MyIterator iterator;
    typedef MyIterator const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};

#endif
