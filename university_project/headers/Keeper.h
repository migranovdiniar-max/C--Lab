#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include "Student.h"
#include "Teacher.h"
#include "Administrative.h"
#include "Exception.h"
#include <fstream>

class Keeper {
private:
    Base** data;
    int size;
    int capacity;

    void resize();
    int findIndex(Base* item) const;

public:
    Keeper();
    Keeper(int initialCapacity);
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);

    void add(Base* item);
    void remove(Base* item);
    void remove(int index);
    void printAll() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    int getSize() const;
    Base* get(int index) const;
};

#endif