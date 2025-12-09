#include "sign.h"
#include <cstring>

static char* allocCopy(const char* s) {
    char* p = new char[strlen(s) + 1];
    strcpy(p, s);
    return p;
}

SIGN::SIGN() {
    surname = nullptr;
    name = nullptr;
    zodiac = nullptr;
    birthday[0] = birthday[1] = birthday[2] = 0;
}

SIGN::SIGN(const char* s, const char* n, const char* z, int d, int m, int y) {
    surname = allocCopy(s);
    name = allocCopy(n);
    zodiac = allocCopy(z);

    birthday[0] = d;
    birthday[1] = m;
    birthday[2] = y;
}

SIGN::SIGN(const SIGN& other) {
    surname = allocCopy(other.surname);
    name = allocCopy(other.name);
    zodiac = allocCopy(other.zodiac);

    birthday[0] = other.birthday[0];
    birthday[1] = other.birthday[1];
    birthday[2] = other.birthday[2];
}

SIGN::~SIGN() {
    delete[] surname;
    delete[] name;
    delete[] zodiac;
}

void SIGN::setSurname(const char* s) {
    delete[] surname;
    surname = allocCopy(s);
}

void SIGN::setName(const char* s) {
    delete[] name;
    name = allocCopy(s);
}

void SIGN::setZodiac(const char* s) {
    delete[] zodiac;
    zodiac = allocCopy(s);
}

void SIGN::setBirthday(int d, int m, int y) {
    birthday[0] = d;
    birthday[1] = m;
    birthday[2] = y;
}

void SIGN::print() const {
    std::cout << surname << " " << name << " | "
              << "«нак: " << zodiac
              << " | ƒата: " << birthday[0] << "." << birthday[1] << "." << birthday[2]
              << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SIGN& s) {
    os << s.surname << " " << s.name << " "
       << s.zodiac << " "
       << s.birthday[0] << " " << s.birthday[1] << " " << s.birthday[2];
    return os;
}

std::istream& operator>>(std::istream& is, SIGN& s) {
    char tempS[100], tempN[100], tempZ[100];
    int d, m, y;

    std::cout << "¬ведите фамилию: ";
    is >> tempS;
    std::cout << "¬ведите им€: ";
    is >> tempN;
    std::cout << "¬ведите знак зодиака: ";
    is >> tempZ;
    std::cout << "¬ведите день, мес€ц, год рождени€: ";
    is >> d >> m >> y;

    s.setSurname(tempS);
    s.setName(tempN);
    s.setZodiac(tempZ);
    s.setBirthday(d, m, y);

    return is;
}
