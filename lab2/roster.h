#ifndef ROSTER_H
#define ROSTER_H
#include "sign.h"

class Roster {
private:
    SIGN* list;
    int size;
public:
    Roster();
    ~Roster();
    void add(const SIGN& s);
    void sortByBirth();
    void showAll() const;
    int getSize() const;
    SIGN& operator[](int index);
};

#endif
