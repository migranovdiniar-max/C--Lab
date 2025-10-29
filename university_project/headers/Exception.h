#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception {
private:
    std::string message;
public:
    Exception(const std::string& msg) : message(msg) {}
    std::string what() const { return message; }
};

#endif