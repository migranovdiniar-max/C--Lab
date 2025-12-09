#include "sign.h"
#include <iostream>
#include <limits>

SIGN::SIGN() {
    surname = new char[1]{'\0'};
    name = new char[1]{'\0'};
    zodiac = new char[1]{'\0'};
    birth[0] = birth[1] = birth[2] = 0;
    std::cout << "[SIGN] default constructor\n";
}

SIGN::SIGN(const char* s, const char* n, const char* z, int d, int m, int y) {
    surname = new char[strlen(s)+1]; strcpy(surname,s);
    name = new char[strlen(n)+1]; strcpy(name,n);
    zodiac = new char[strlen(z)+1]; strcpy(zodiac,z);
    birth[0]=d; birth[1]=m; birth[2]=y;
    std::cout << "[SIGN] parameterized constructor\n";
}

SIGN::SIGN(const SIGN& other) {
    surname = new char[strlen(other.surname)+1]; strcpy(surname,other.surname);
    name = new char[strlen(other.name)+1]; strcpy(name,other.name);
    zodiac = new char[strlen(other.zodiac)+1]; strcpy(zodiac,other.zodiac);
    birth[0]=other.birth[0]; birth[1]=other.birth[1]; birth[2]=other.birth[2];
    // std::cout << "[SIGN] copy constructor\n";
}

SIGN::~SIGN() {
    delete[] surname;
    delete[] name;
    delete[] zodiac;
    std::cout << "[SIGN] destructor\n";
}

void SIGN::setSurname(const char* s){ delete[] surname; surname=new char[strlen(s)+1]; strcpy(surname,s); }
void SIGN::setName(const char* n){ delete[] name; name=new char[strlen(n)+1]; strcpy(name,n); }
void SIGN::setZodiac(const char* z){ delete[] zodiac; zodiac=new char[strlen(z)+1]; strcpy(zodiac,z); }
void SIGN::setBirth(int d,int m,int y){ birth[0]=d; birth[1]=m; birth[2]=y; }

const char* SIGN::getSurname() const { return surname; }
const char* SIGN::getName() const { return name; }
const char* SIGN::getZodiac() const { return zodiac; }
void SIGN::getBirth(int &d,int &m,int &y) const { d=birth[0]; m=birth[1]; y=birth[2]; }

void SIGN::show() const {
    std::cout << surname << " " << name << ", " << zodiac
              << ", " << birth[0] << "." << birth[1] << "." << birth[2] << "\n";
}

std::ostream& operator<<(std::ostream& os,const SIGN& s) {
    os << s.surname << " " << s.name << " " << s.zodiac << " "
       << s.birth[0] << " " << s.birth[1] << " " << s.birth[2];
    return os;
}

std::istream& operator>>(std::istream& is, SIGN& s) {
    char buf[100];
    is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    std::cout << "Фамилия: "; is.getline(buf,100); s.setSurname(buf);
    std::cout << "Имя: "; is.getline(buf,100); s.setName(buf);
    std::cout << "Знак зодиака: "; is.getline(buf,100); s.setZodiac(buf);
    int d,m,y;
    std::cout << "Дата рождения (дд мм гггг): "; is >> d >> m >> y;
    s.setBirth(d,m,y);
    is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    return is;
}

bool SIGN::operator<(const SIGN& other) const {
    if(birth[2]!=other.birth[2]) return birth[2]<other.birth[2];
    if(birth[1]!=other.birth[1]) return birth[1]<other.birth[1];
    return birth[0]<other.birth[0];
}
