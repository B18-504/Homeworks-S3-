#ifndef exceptions_hpp
#define exceptions_hpp

#include <exception>

class exception_incorrectSelection : public std::exception {
    const int code = 10;
    virtual const char* what() const throw() {
        return "Incorrect selection";
    }
};

class exception_outOfRange : public std::exception {
    const int code = 11;
    virtual const char* what() const throw() {
        return "Out of range";
    }
};

class exception_sequenceIsEmpty : public std::exception {
    const int code = 12;
    virtual const char* what() const throw() {
        return "Sequence is empty";
    }
};

#endif
