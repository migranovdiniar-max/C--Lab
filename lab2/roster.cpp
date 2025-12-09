#include "roster.h"
#include <cstring>
#include <iostream>
#include <fstream>

Roster::Roster(): arr(nullptr), size(0), capacity(0) {
    capacity = 4;
    arr = new SIGN*[capacity];
    for (int i=0;i<capacity;++i) arr[i]=nullptr;
}

Roster::~Roster() {
    for (int i=0;i<size;++i) delete arr[i];
    delete [] arr;
}

Roster::Roster(const Roster& other) {
    capacity = other.capacity;
    size = other.size;
    arr = new SIGN*[capacity];
    for (int i=0;i<size;++i) arr[i] = new SIGN(*other.arr[i]);
    for (int i=size;i<capacity;++i) arr[i]=nullptr;
}

int Roster::getSize() const { return size; }
const SIGN* Roster::getAt(int idx) const {
    if (idx<0 || idx>=size) return nullptr;
    return arr[idx];
}

void Roster::expand() {
    int newcap = capacity * 2;
    SIGN** newarr = new SIGN*[newcap];
    for (int i=0;i<size;++i) newarr[i]=arr[i];
    for (int i=size;i<newcap;++i) newarr[i]=nullptr;
    delete [] arr;
    arr = newarr;
    capacity = newcap;
}

void Roster::add(const SIGN& s) {
    if (size >= capacity) expand();
    arr[size++] = new SIGN(s); // copy
}

void Roster::sortByBirthday() {
    if (size < 2) return;
    for (int i=0;i<size-1;++i) {
        for (int j=0;j<size-1-i;++j) {
            if (arr[j+1]->earlierThan(*arr[j])) {
                SIGN* tmp = arr[j]; arr[j]=arr[j+1]; arr[j+1]=tmp;
            }
        }
    }
}

SIGN* Roster::findBySurname(const char* surname) const {
    for (int i=0;i<size;++i) {
        if (std::strcmp(arr[i]->getSurname(), surname)==0) return arr[i];
    }
    return nullptr;
}

void Roster::clear() {
    for (int i=0;i<size;++i) delete arr[i];
    size = 0;
}

void Roster::saveToFile(const char* filename) const {
    std::ofstream ofs(filename);
    if (!ofs) throw AppException("Cannot open file for writing");
    for (int i=0;i<size;++i) {
        arr[i]->writeMulti(ofs);
    }
    ofs.close();
}

void Roster::appendToFile(const char* filename) const {
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs) throw AppException("Cannot open file for appending");
    for (int i=0;i<size;++i) {
        arr[i]->writeMulti(ofs);
    }
    ofs.close();
}

void Roster::loadFromFile(const char* filename) {
    std::ifstream ifs(filename);
    if (!ifs) throw AppException("Cannot open file for reading");
    // clear existing
    clear();
    SIGN temp;
    while (SIGN::readMulti(ifs, temp)) {
        add(temp);
    }
    ifs.close();
}
