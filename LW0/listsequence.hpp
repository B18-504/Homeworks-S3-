#ifndef listsequence_hpp
#define listsequence_hpp

#include "sequence.hpp"

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
    virtual T get(int index) const override;
    virtual T getFirst() const override;
    virtual T getLast() const override;
    virtual ListSequence<T>* getSubSequence(int startIndex, int endIndex) const override;
    virtual void append(T item) override;
    virtual void prepend(T item) override;
    virtual void insertAt(int index, T item) override;
    virtual void remove(T item) override;
    virtual void replace(int index, T item) override;
private:
    class MyIterator: public std::iterator<std::bidirectional_iterator_tag, T> {
        friend class ListSequence;
    private:
        ListSequence::Node* pos;
        MyIterator(ListSequence::Node* pos);
    public:
        MyIterator(const MyIterator &it);
        ~MyIterator();
    public:
        typename MyIterator::reference operator*() const;
        typename MyIterator::pointer operator->() const;
        typename MyIterator::reference operator[](const typename MyIterator::difference_type& n) const;
        typename MyIterator::difference_type operator-(const MyIterator& it) const;
        MyIterator operator++(int);
        MyIterator& operator++();
        MyIterator operator--(int);
        MyIterator& operator--();
        MyIterator operator+(const typename MyIterator::difference_type& n) const;
        MyIterator& operator+=(const typename MyIterator::difference_type& n);
        MyIterator operator-(const typename MyIterator::difference_type& n) const;
        MyIterator& operator-=(const typename MyIterator::difference_type& n);
        bool operator!=(const MyIterator& it) const;
        bool operator==(const MyIterator& it) const;
        bool operator<(const MyIterator& it) const;
        bool operator>(const MyIterator& it) const;
        bool operator<=(const MyIterator& it) const;
        bool operator>=(const MyIterator& it) const;
    };
public:
    typedef MyIterator iterator;
    typedef MyIterator const const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};

#endif
