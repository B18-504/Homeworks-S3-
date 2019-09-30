#ifndef arraysequence_hpp
#define arraysequence_hpp

#include "sequence.hpp"

template <typename T>
class ArraySequence : public Sequence<T> {
private:
    T* data;
public:
    ArraySequence(); //default constuctor
    ArraySequence(Sequence<T>* sequence); //copying constuctor
    ArraySequence(int n, int leftLimit, int rightLimit); //create sequence with n random int numbers in given selection
    ArraySequence<T>& operator=(const Sequence<T>& sequence) {
        free(this->data);
        this->data = nullptr;
        Sequence<T>::length = 0;
        for (int i = 0; i < sequence.getLength(); i++) {
            this->append(sequence.get(i));
        }
        return *this;
    }
    ~ArraySequence();
public:
    virtual int getLength() const override;
    virtual bool getIsEmpty() const override;
public:
    virtual T get(int index) const override;
    virtual T getFirst() const override;
    virtual T getLast() const override;
    virtual ArraySequence<T>* getSubSequence(int startIndex, int endIndex) const override;
    virtual void append(T item) override;
    virtual void prepend(T item) override;
    virtual void insertAt(int index, T item) override;
    virtual void remove(T item) override;
    virtual void replace(int index, T item) override;
    virtual void clear() override;
};

#endif
