#ifndef arraysequence_hpp
#define arraysequence_hpp

#include "isequence.hpp"

template <typename T>
class ArraySequence: public ISequence<T> {
private:
    T* data;
public:
    ArraySequence();
    ArraySequence(ISequence<T>* sequence);
    ArraySequence(int n, int leftLimit, int rightLimit);
    ArraySequence<T>& operator=(const ArraySequence<T>& sequence);
    ~ArraySequence();
public:
    virtual int getLength() const override;
    virtual bool getIsEmpty() const override;
public:
    virtual T get(const int& index) const override;
    virtual T getFirst() const override;
    virtual T getLast() const override;
    virtual ArraySequence<T>* getSubSequence(const int& startIndex, const int& endIndex) const override;
    virtual void append(const T& item) override;
    virtual void prepend(const T& item) override;
    virtual void insertAt(const int& index, const T& item) override;
    virtual void remove(const T& item) override;
    virtual void set(const int& index, const T& item) override;
    template <typename ...F>
    static ArraySequence<T>* arraySequenceOf(const F&... items);
private:
    class MyIterator: public std::iterator<std::random_access_iterator_tag, T> {
        friend class ArraySequence;
    private:
        T* pos;
        MyIterator(T* pos);
    public:
        MyIterator(const MyIterator &it);
        ~MyIterator();
    public:
        MyIterator& operator=(const MyIterator& it);
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
    typedef MyIterator const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};

#endif
