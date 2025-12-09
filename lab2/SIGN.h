#ifndef SIGN_H
#define SIGN_H

#include <iostream>

class SIGN {
private:
    char* surname;
    char* name;
    char* zodiac;
    int* birthday; // массив из трех чисел [день, месяц, год]
    
    void init(const char* sname, const char* n, const char* z, const int* bd);
    void copy(const SIGN& other);
    void cleanup();

public:
    // Конструкторы
    SIGN();
    SIGN(const char* sname, const char* n, const char* z, const int* bd);
    SIGN(const SIGN& other);
    
    // Деструктор
    ~SIGN();
    
    // Set методы
    void setSurname(const char* sname);
    void setName(const char* n);
    void setZodiac(const char* z);
    void setBirthday(const int* bd);
    
    // Get методы
    const char* getSurname() const;
    const char* getName() const;
    const char* getZodiac() const;
    const int* getBirthday() const;
    
    // Метод для сравнения дат рождения
    int compareBirthdays(const SIGN& other) const;
    
    // Перегрузка операторов
    SIGN& operator=(const SIGN& other);
    friend std::ostream& operator<<(std::ostream& os, const SIGN& sign);
    friend std::istream& operator>>(std::istream& is, SIGN& sign);
    
    // Метод для отображения информации
    void display() const;
};

#endif