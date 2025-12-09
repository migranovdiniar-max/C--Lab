#include "roster.h"
#include <iostream>

Roster::Roster() { list=nullptr; size=0; }
Roster::~Roster() { delete[] list; }

void Roster::add(const SIGN& s) {
    SIGN* newList=new SIGN[size+1];
    for(int i=0;i<size;i++) newList[i]=list[i];
    newList[size]=s;
    delete[] list;
    list=newList;
    size++;
}

void Roster::sortByBirth() {
    for(int i=0;i<size-1;i++)
        for(int j=i+1;j<size;j++)
            if(list[j]<list[i]){
                SIGN temp=list[i];
                list[i]=list[j];
                list[j]=temp;
            }
}

void Roster::showAll() const {
    for(int i=0;i<size;i++) list[i].show();
}

int Roster::getSize() const { return size; }
SIGN& Roster::operator[](int index){ return list[index]; }
