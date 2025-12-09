#ifndef SIGN_H
#define SIGN_H

#include <iostream>
#include <cstring>

class SIGN {
private:
    char* surname;
    char* name;
    char* zodiac;
    int birth[3]; // день, мес€ц, год

public:
    SIGN();  // default constructor
    SIGN(const char* s, const char* n, const char* z, int d, int m, int y); // param constructor
    SIGN(const SIGN& other); // copy constructor
    ~SIGN(); // destructor

    void setSurname(const char* s);
    void setName(const char* n);
    void setZodiac(const char* z);
    void setBirth(int d, int m, int y);

    const char* getSurname() const;
    const char* getName() const;
    const char* getZodiac() const;
    void getBirth(int& d, int& m, int& y) const;

    void show() const;

    friend std::ostream& operator<<(std::ostream& os, const SIGN& s);
    friend std::istream& operator>>(std::istream& is, SIGN& s);

    bool operator<(const SIGN& other) const;
};

#endif
