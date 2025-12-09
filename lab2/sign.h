#ifndef SIGN_H
#define SIGN_H
#include <iostream>

class SIGN {
private:
    char* surname;
    char* name;
    char* zodiac;
    int birthday[3]; // day, month, year

public:
    // Конструкторы
    SIGN();
    SIGN(const char* s, const char* n, const char* z, int d, int m, int y);
    SIGN(const SIGN& other);

    // Деструктор
    ~SIGN();

    // set / get
    void setSurname(const char* s);
    void setName(const char* s);
    void setZodiac(const char* s);
    void setBirthday(int d, int m, int y);

    const char* getSurname() const { return surname; }
    const char* getName() const { return name; }
    const char* getZodiac() const { return zodiac; }
    const int* getBirthday() const { return birthday; }

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const SIGN& s);
    friend std::istream& operator>>(std::istream& is, SIGN& s);

    // Вывод
    void print() const;
};

#endif
