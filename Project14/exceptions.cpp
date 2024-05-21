#include <iostream>

class ReadFailException : public std::exception {
public:
    ReadFailException(char const* const _Message) throw() : std::exception(_Message)
    {
    }

    char const* what() const throw() {
        return exception::what();
    }
};

class WriteFailException : public std::exception {
public:
    WriteFailException(char const* const _Message) throw() : std::exception(_Message)
    {
    }

    char const* what() const throw() {
        return exception::what();
    }
};