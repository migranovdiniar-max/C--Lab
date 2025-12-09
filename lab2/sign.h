#ifndef SIGN_H
#define SIGN_H

#include <iostream>

struct AppException {
    const char* msg;
    AppException(const char* m): msg(m) {}
};

class SIGN {
private:
    char* surname;
    char* name;
    char* zodiac;
    int birthday[3]; // day, month, year

    static char* dup_cstr(const char* src);

public:
    // constructors / destructor
    SIGN();                                      // default
    SIGN(const char* s, const char* n, const char* z, int d, int m, int y); // params
    SIGN(const SIGN& other);                     // copy
    ~SIGN();

    // accessors (set/get)
    void setSurname(const char* s);
    void setName(const char* n);
    void setZodiac(const char* z);
    void setBirthday(int d, int m, int y);

    const char* getSurname() const;
    const char* getName() const;
    const char* getZodiac() const;
    void getBirthday(int &d, int &m, int &y) const;

    // comparison by date
    bool earlierThan(const SIGN& other) const;

    // stream operators (console and file-friendly)
    friend std::ostream& operator<<(std::ostream& os, const SIGN& s); // single-line but used for debug
    friend std::istream& operator>>(std::istream& is, SIGN& s); // interactive input (console)

    // write in the "variant B" multi-line format to an output stream
    void writeMulti(std::ostream& os) const;
    // read from multi-line block (expect lines starting with labels), returns true on success
    static bool readMulti(std::istream& is, SIGN& out);
};

#endif // SIGN_H
