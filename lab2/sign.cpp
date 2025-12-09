#include "sign.h"
#include <cstring>
#include <iomanip>
#include <cctype>

char* SIGN::dup_cstr(const char* src) {
    if (!src) {
        char* p = new char[1];
        p[0] = '\0';
        return p;
    }
    size_t L = std::strlen(src);
    char* p = new char[L+1];
    std::strcpy(p, src);
    return p;
}

SIGN::SIGN() {
    surname = dup_cstr("");
    name = dup_cstr("");
    zodiac = dup_cstr("");
    birthday[0]=birthday[1]=birthday[2]=0;
    std::cout << "[SIGN] default constructor\n";
}

SIGN::SIGN(const char* s, const char* n, const char* z, int d, int m, int y) {
    if (!s || !n || !z) throw AppException("Null pointer to SIGN constructor");
    surname = dup_cstr(s);
    name = dup_cstr(n);
    zodiac = dup_cstr(z);
    birthday[0]=d; birthday[1]=m; birthday[2]=y;
    std::cout << "[SIGN] parameterized constructor for " << surname << " " << name << "\n";
}

SIGN::SIGN(const SIGN& other) {
    surname = dup_cstr(other.surname);
    name = dup_cstr(other.name);
    zodiac = dup_cstr(other.zodiac);
    birthday[0]=other.birthday[0];
    birthday[1]=other.birthday[1];
    birthday[2]=other.birthday[2];
    std::cout << "[SIGN] copy constructor for " << surname << " " << name << "\n";
}

SIGN::~SIGN() {
    std::cout << "[SIGN] destructor for " << (surname?surname:"(null)") << " " << (name?name:"(null)") << "\n";
    delete [] surname;
    delete [] name;
    delete [] zodiac;
}

void SIGN::setSurname(const char* s) {
    if (!s) throw AppException("Null in setSurname");
    delete [] surname;
    surname = dup_cstr(s);
}
void SIGN::setName(const char* n) {
    if (!n) throw AppException("Null in setName");
    delete [] name;
    name = dup_cstr(n);
}
void SIGN::setZodiac(const char* z) {
    if (!z) throw AppException("Null in setZodiac");
    delete [] zodiac;
    zodiac = dup_cstr(z);
}
void SIGN::setBirthday(int d,int m,int y) {
    if (d<1 || d>31 || m<1 || m>12) throw AppException("Invalid date");
    birthday[0]=d; birthday[1]=m; birthday[2]=y;
}

const char* SIGN::getSurname() const { return surname; }
const char* SIGN::getName() const { return name; }
const char* SIGN::getZodiac() const { return zodiac; }
void SIGN::getBirthday(int &d, int &m, int &y) const { d=birthday[0]; m=birthday[1]; y=birthday[2]; }

bool SIGN::earlierThan(const SIGN& other) const {
    if (birthday[2] != other.birthday[2]) return birthday[2] < other.birthday[2];
    if (birthday[1] != other.birthday[1]) return birthday[1] < other.birthday[1];
    return birthday[0] < other.birthday[0];
}

std::ostream& operator<<(std::ostream& os, const SIGN& s) {
    os << s.surname << " " << s.name << " (" << s.zodiac << ") "
       << s.birthday[0] << "." << s.birthday[1] << "." << s.birthday[2];
    return os;
}

std::istream& operator>>(std::istream& is, SIGN& s) {
    // interactive console input
    char buf[256];
    std::cout << "Введите фамилию: ";
    is >> std::ws;
    if (!is.getline(buf, 256)) { is.clear(); is >> buf; } // tolerate different input styles
    s.setSurname(buf);

    std::cout << "Введите имя: ";
    is.getline(buf, 256);
    s.setName(buf);

    std::cout << "Введите знак зодиака: ";
    is.getline(buf, 256);
    s.setZodiac(buf);

    int d,m,y;
    std::cout << "Введите день(число) месяц год через пробел: ";
    if (!(is >> d >> m >> y)) {
        throw AppException("Invalid birthday input");
    }
    s.setBirthday(d,m,y);
    // consume rest of line
    is.ignore(1000,'\n');
    return is;
}

void SIGN::writeMulti(std::ostream& os) const {
    // Variant B format
    os << "Surname: " << surname << "\n";
    os << "Name: " << name << "\n";
    os << "Zodiac: " << zodiac << "\n";
    os << "Birthday: " << birthday[0] << " " << birthday[1] << " " << birthday[2] << "\n";
    os << "---\n";
}

static inline void trim_right(std::string &s) {
    while(!s.empty() && (s.back()=='\n' || s.back()=='\r')) s.pop_back();
}

bool SIGN::readMulti(std::istream& is, SIGN& out) {
    // read 5 lines: Surname, Name, Zodiac, Birthday, separator (separator optional at EOF)
    std::string line;
    // read Surname:
    if (!std::getline(is, line)) return false;
    trim_right(line);
    if (line.size()==0) {
        // skip blank lines
        while (line.size()==0 && std::getline(is,line)) { trim_right(line); }
        if (line.size()==0) return false;
    }
    if (line.rfind("Surname:",0) != 0) return false;
    std::string surname = line.substr(8);
    if (!surname.empty() && surname[0]==' ') surname.erase(0,1);

    if (!std::getline(is, line)) return false; trim_right(line);
    if (line.rfind("Name:",0) != 0) return false;
    std::string name = line.substr(5);
    if (!name.empty() && name[0]==' ') name.erase(0,1);

    if (!std::getline(is, line)) return false; trim_right(line);
    if (line.rfind("Zodiac:",0) != 0) return false;
    std::string zodiac = line.substr(7);
    if (!zodiac.empty() && zodiac[0]==' ') zodiac.erase(0,1);

    if (!std::getline(is, line)) return false; trim_right(line);
    if (line.rfind("Birthday:",0) != 0) return false;
    std::string b = line.substr(9);
    if (!b.empty() && b[0]==' ') b.erase(0,1);
    int d=0,m=0,y=0;
    {
        // parse three ints from b
        std::sscanf(b.c_str(), "%d %d %d", &d,&m,&y);
    }

    // next line should be separator '---' but could be EOF
    std::string sep;
    std::streampos pos = is.tellg();
    if (std::getline(is, sep)) {
        trim_right(sep);
        if (sep != "---") {
            // not separator: could be start of next record; rewind to before this line
            is.seekg(pos);
        }
    }

    // assign to out
    out.setSurname(surname.c_str());
    out.setName(name.c_str());
    out.setZodiac(zodiac.c_str());
    out.setBirthday(d,m,y);
    return true;
}
