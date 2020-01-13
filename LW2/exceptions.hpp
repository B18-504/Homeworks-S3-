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

class exception_repeatedKey : public std::exception {
    const int code = 20;
    virtual const char* what() const throw() {
        return "Key is already in Dictionary";
    }
};

class exception_missingKey : public std::exception {
    const int code = 21;
    virtual const char* what() const throw() {
        return "Key is missing in the given Dictionary";
    }
};

class exception_wrongFragmentation : public std::exception {
    const int code = 30;
    virtual const char* what() const throw() {
        return "Incorrect fragmentation provided";
    }
};

class exception_wrongInputLine : public std::exception {
    const int code = 40;
    virtual const char* what() const throw() {
        return "Incorrect input line provided";
    }
};

#endif
