#include "Administrative.h"
#include <fstream>

Administrative::Administrative() {
    std::cout << "Administrative default constructor called" << std::endl;
}

Administrative::Administrative(const std::string& name, const std::string& pos,
                               const std::string& ph, const std::string& resp)
    : fullName(name), position(pos), phone(ph), responsibility(resp) {
    std::cout << "Administrative parameterized constructor called" << std::endl;
}

Administrative::Administrative(const Administrative& other)
    : fullName(other.fullName), position(other.position),
      phone(other.phone), responsibility(other.responsibility) {
    std::cout << "Administrative copy constructor called" << std::endl;
}

Administrative::~Administrative() {
    std::cout << "Administrative destructor called" << std::endl;
}

Administrative& Administrative::operator=(const Administrative& other) {
    if (this != &other) {
        fullName = other.fullName;
        position = other.position;
        phone = other.phone;
        responsibility = other.responsibility;
    }
    std::cout << "Administrative assignment operator called" << std::endl;
    return *this;
}

void Administrative::print() const {
    std::cout << "Administrative: " << fullName << "\nPosition: " << position
              << "\nPhone: " << phone << "\nResponsibility: " << responsibility << "\n\n";
}

void Administrative::setData() {
    std::cout << "Enter full name: ";
    std::getline(std::cin, fullName);
    
    std::cout << "Enter position: ";
    std::getline(std::cin, position);
    
    std::cout << "Enter phone: ";
    std::getline(std::cin, phone);
    
    std::cout << "Enter responsibility: ";
    std::getline(std::cin, responsibility);
}

void Administrative::saveToFile(std::ofstream& file) const {
    file << fullName << "\n" << position << "\n" << phone << "\n" << responsibility << "\n";
}

void Administrative::loadFromFile(std::ifstream& file) {
    std::getline(file, fullName);
    std::getline(file, position);
    std::getline(file, phone);
    std::getline(file, responsibility);
}

// Setters
void Administrative::setFullName(const std::string& name) { fullName = name; }
void Administrative::setPosition(const std::string& pos) { position = pos; }
void Administrative::setPhone(const std::string& ph) { phone = ph; }
void Administrative::setResponsibility(const std::string& resp) { responsibility = resp; }

// Getters
std::string Administrative::getFullName() const { return fullName; }
std::string Administrative::getPosition() const { return position; }
std::string Administrative::getPhone() const { return phone; }
std::string Administrative::getResponsibility() const { return responsibility; }