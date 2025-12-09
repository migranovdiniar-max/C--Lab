#ifndef ROSTER_H
#define ROSTER_H

#include "sign.h"

class Roster {
private:
    SIGN** arr;   // dynamic array of pointers
    int size;
    int capacity;

    void expand();

public:
    Roster();
    ~Roster();
    Roster(const Roster& other);

    int getSize() const;
    const SIGN* getAt(int idx) const;

    void add(const SIGN& s);      // add copy at end
    void sortByBirthday();
    SIGN* findBySurname(const char* surname) const;
    void clear();

    // read/write convenience
    void loadFromFile(const char* filename); // replaces current contents
    void saveToFile(const char* filename) const; // overwrite file
    void appendToFile(const char* filename) const; // append current array to file (in multi format)
};

#endif // ROSTER_H
