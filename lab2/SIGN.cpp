#include "SIGN.h"
#include <cstring>
#include <stdexcept>

// Вспомогательные функции
namespace {
    bool isValidDate(int day, int month, int year) {
        if (year < 1900 || year > 2100) return false;
        if (month < 1 || month > 12) return false;
        
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Проверка високосного года
        if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (isLeap) daysInMonth[1] = 29;
        }
        
        return day >= 1 && day <= daysInMonth[month - 1];
    }
}

// Приватные методы
void SIGN::init(const char* sname, const char* n, const char* z, const int* bd) {
    surname = new char[strlen(sname) + 1];
    strcpy(surname, sname);
    
    name = new char[strlen(n) + 1];
    strcpy(name, n);
    
    zodiac = new char[strlen(z) + 1];
    strcpy(zodiac, z);
    
    birthday = new int[3];
    for (int i = 0; i < 3; i++) {
        birthday[i] = bd[i];
    }
}

void SIGN::copy(const SIGN& other) {
    init(other.surname, other.name, other.zodiac, other.birthday);
}

void SIGN::cleanup() {
    delete[] surname;
    delete[] name;
    delete[] zodiac;
    delete[] birthday;
}

// Конструкторы
SIGN::SIGN() : surname(nullptr), name(nullptr), zodiac(nullptr), birthday(nullptr) {
    std::cout << "Вызван конструктор без параметров для объекта по адресу: " << this << std::endl;
}

SIGN::SIGN(const char* sname, const char* n, const char* z, const int* bd) {
    if (!isValidDate(bd[0], bd[1], bd[2])) {
        throw std::invalid_argument("Неверная дата рождения");
    }
    
    init(sname, n, z, bd);
    std::cout << "Вызван конструктор с параметрами для объекта по адресу: " << this << std::endl;
}

SIGN::SIGN(const SIGN& other) {
    copy(other);
    std::cout << "Вызван конструктор копирования для объекта по адресу: " << this 
              << " (копирование из объекта " << &other << ")" << std::endl;
}

// Деструктор
SIGN::~SIGN() {
    cleanup();
    std::cout << "Вызван деструктор для объекта по адресу: " << this << std::endl;
}

// Set методы
void SIGN::setSurname(const char* sname) {
    delete[] surname;
    surname = new char[strlen(sname) + 1];
    strcpy(surname, sname);
}

void SIGN::setName(const char* n) {
    delete[] name;
    name = new char[strlen(n) + 1];
    strcpy(name, n);
}

void SIGN::setZodiac(const char* z) {
    delete[] zodiac;
    zodiac = new char[strlen(z) + 1];
    strcpy(zodiac, z);
}

void SIGN::setBirthday(const int* bd) {
    if (!isValidDate(bd[0], bd[1], bd[2])) {
        throw std::invalid_argument("Неверная дата рождения");
    }
    
    delete[] birthday;
    birthday = new int[3];
    for (int i = 0; i < 3; i++) {
        birthday[i] = bd[i];
    }
}

// Get методы
const char* SIGN::getSurname() const {
    return surname;
}

const char* SIGN::getName() const {
    return name;
}

const char* SIGN::getZodiac() const {
    return zodiac;
}

const int* SIGN::getBirthday() const {
    return birthday;
}

// Метод для сравнения дат рождения
int SIGN::compareBirthdays(const SIGN& other) const {
    // Сравниваем годы
    if (birthday[2] != other.birthday[2]) {
        return birthday[2] - other.birthday[2];
    }
    // Сравниваем месяцы
    if (birthday[1] != other.birthday[1]) {
        return birthday[1] - other.birthday[1];
    }
    // Сравниваем дни
    return birthday[0] - other.birthday[0];
}

// Перегрузка операторов
SIGN& SIGN::operator=(const SIGN& other) {
    std::cout << "Вызван оператор присваивания для объекта по адресу: " << this 
              << " (присваивание из объекта " << &other << ")" << std::endl;
    
    if (this != &other) {
        cleanup();
        copy(other);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const SIGN& sign) {
    os << "Фамилия: " << (sign.surname ? sign.surname : "не указана") << std::endl;
    os << "Имя: " << (sign.name ? sign.name : "не указано") << std::endl;
    os << "Знак зодиака: " << (sign.zodiac ? sign.zodiac : "не указан") << std::endl;
    if (sign.birthday) {
        os << "День рождения: " << sign.birthday[0] << "." 
           << sign.birthday[1] << "." << sign.birthday[2] << std::endl;
    } else {
        os << "День рождения: не указан" << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, SIGN& sign) {
    char buffer[100];
    int bd[3];
    
    std::cout << "Введите фамилию: ";
    is >> buffer;
    sign.setSurname(buffer);
    
    std::cout << "Введите имя: ";
    is >> buffer;
    sign.setName(buffer);
    
    std::cout << "Введите знак зодиака: ";
    is >> buffer;
    sign.setZodiac(buffer);
    
    std::cout << "Введите день рождения (день месяц год через пробел): ";
    is >> bd[0] >> bd[1] >> bd[2];
    
    if (!isValidDate(bd[0], bd[1], bd[2])) {
        throw std::invalid_argument("Неверная дата рождения");
    }
    
    sign.setBirthday(bd);
    return is;
}

// Метод для отображения информации
void SIGN::display() const {
    std::cout << *this;
}