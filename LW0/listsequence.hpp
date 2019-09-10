#ifndef listsequence_hpp
#define listsequence_hpp

#include "sequence.hpp"

template <typename T>
class ListSequence : public Sequence<T> {
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
    ListSequence(); //default constructor
    ListSequence(ListSequence<T>* sequence); //copying constructor
    ListSequence(int n, int leftLimit, int rightLimit); //create sequence with n random int numbers in given selection
    ListSequence<T>& operator=(const ListSequence<T>& sequence) {
        Node *tmp = nullptr;
        while (tmp != nullptr) {
            Node *next = tmp->next;
            delete tmp;
            tmp = next;
        }
        head = nullptr;
        tail = nullptr;
        Sequence<T>::length = 0;
        for (int i = 0; i < sequence.getLength(); i++) {
            this->append(sequence.get(i));
        }
        return *this;
    }
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
};

#endif
