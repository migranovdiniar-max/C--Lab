
#include "sign.h"
#include <cstring>
#include <iostream>
SIGN::SIGN(){
    surname=nullptr; name=nullptr;
    birthday[0]=birthday[1]=birthday[2]=0;
    std::cout<<"[SIGN] Default constructor\n";
}
SIGN::SIGN(const char* s,const char* n,int d,int m,int y){
    surname=new char[strlen(s)+1]; strcpy(surname,s);
    name=new char[strlen(n)+1]; strcpy(name,n);
    birthday[0]=d; birthday[1]=m; birthday[2]=y;
    std::cout<<"[SIGN] Constructor with params\n";
}
SIGN::SIGN(const SIGN& o){
    surname=new char[strlen(o.surname)+1]; strcpy(surname,o.surname);
    name=new char[strlen(o.name)+1]; strcpy(name,o.name);
    birthday[0]=o.birthday[0]; birthday[1]=o.birthday[1]; birthday[2]=o.birthday[2];
    std::cout<<"[SIGN] Copy constructor\n";
}
SIGN::~SIGN(){
    std::cout<<"[SIGN] Destructor\n";
    delete[] surname; delete[] name;
}
void SIGN::setSurname(const char* s){ delete[] surname; surname=new char[strlen(s)+1]; strcpy(s,surname);}
void SIGN::setName(const char* n){ delete[] name; name=new char[strlen(n)+1]; strcpy(name,n);}
void SIGN::setBirthday(int d,int m,int y){ birthday[0]=d; birthday[1]=m; birthday[2]=y;}
const char* SIGN::getSurname() const{return surname;}
const char* SIGN::getName() const{return name;}
void SIGN::getBirthday(int& d,int& m,int& y) const{ d=birthday[0]; m=birthday[1]; y=birthday[2]; }
std::ostream& operator<<(std::ostream& o,const SIGN& s){
    o<<s.surname<<" "<<s.name<<" "<<s.birthday[0]<<"."<<s.birthday[1]<<"."<<s.birthday[2];
    return o;
}
std::istream& operator>>(std::istream& in,SIGN& s){
    char buf1[100],buf2[100]; int d,m,y;
    in>>buf1>>buf2>>d>>m>>y;
    s.setSurname(buf1); s.setName(buf2); s.setBirthday(d,m,y);
    return in;
}
