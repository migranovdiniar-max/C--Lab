
#ifndef SIGN_H
#define SIGN_H
#include <iostream>
class SignException: public std::exception{
    const char* msg;
public:
    SignException(const char* m): msg(m){}
    const char* what() const noexcept override { return msg; }
};
class SIGN {
    char* surname;
    char* name;
    int birthday[3];
public:
    SIGN();
    SIGN(const char* s, const char* n, int d, int m, int y);
    SIGN(const SIGN& other);
    ~SIGN();
    void setSurname(const char* s);
    void setName(const char* n);
    void setBirthday(int d, int m, int y);
    const char* getSurname() const;
    const char* getName() const;
    void getBirthday(int& d,int& m,int& y) const;
    friend std::ostream& operator<<(std::ostream&, const SIGN&);
    friend std::istream& operator>>(std::istream&, SIGN&);
};
#endif
