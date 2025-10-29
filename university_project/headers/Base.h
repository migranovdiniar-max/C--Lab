#ifndef BASE_H
#define BASE_H

#include <string>

class Base {
public:
    virtual ~Base() = default;
    virtual void print() const = 0;
    virtual void setData() = 0;
    virtual void saveToFile(std::ofstream& file) const = 0;
    virtual void loadFromFile(std::ifstream& file) = 0;
};

#endif