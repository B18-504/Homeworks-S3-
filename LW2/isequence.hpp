#ifndef isequence_hpp
#define isequence_hpp

#include "exceptions.hpp"
#include "functions.hpp"

template <typename T>
class ISequence {
protected:
    int length; //length of sequence
public:
    virtual int getLength() const = 0; //get length of sequence
    virtual bool getIsEmpty() const = 0; //check if empty
public:
    virtual T get(const int& index) const = 0; //get item based on index
    virtual T getFirst() const = 0; //get first item
    virtual T getLast() const = 0; //get last item
    virtual ISequence<T>* getSubSequence(const int& startIndex, const int& endIndex) const = 0;
    virtual void append(const T& item) = 0; //add item to the end
    virtual void prepend(const T& item) = 0; //add item to the beginning
    virtual void insertAt(const int& index, const T& item) = 0; //insert item at a specific point
    virtual void remove(const T& item) = 0; //remove specific item
    virtual void set(const int& index, const T& item) = 0; //set an item
protected:
    class IIterator: public std::iterator<std::random_access_iterator_tag, T> { //virtual Iterator class
    };
public:
    typedef IIterator iterator;
    typedef IIterator const const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};

#endif
