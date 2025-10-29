#include "Student.h"
#include <fstream>

Student::Student() : course(1), averageScore(0.0) {
    std::cout << "Student default constructor called" << std::endl;
}

Student::Student(const std::string& name, const std::string& grp,
                 const std::string& spec, int crs, double avg)
    : fullName(name), group(grp), specialty(spec), course(crs), averageScore(avg) {
    std::cout << "Student parameterized constructor called" << std::endl;
}

Student::Student(const Student& other)
    : fullName(other.fullName), group(other.group), 
      specialty(other.specialty), course(other.course), 
      averageScore(other.averageScore) {
    std::cout << "Student copy constructor called" << std::endl;
}

Student::~Student() {
    std::cout << "Student destructor called" << std::endl;
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        fullName = other.fullName;
        group = other.group;
        specialty = other.specialty;
        course = other.course;
        averageScore = other.averageScore;
    }
    std::cout << "Student assignment operator called" << std::endl;
    return *this;
}

void Student::print() const {
    std::cout << "Student: " << fullName << "\nGroup: " << group
              << "\nSpecialty: " << specialty << "\nCourse: " << course
              << "\nAverage Score: " << averageScore << "\n\n";
}

void Student::setData() {
    std::cout << "Enter full name: ";
    std::getline(std::cin, fullName);
    
    std::cout << "Enter group: ";
    std::getline(std::cin, group);
    
    std::cout << "Enter specialty: ";
    std::getline(std::cin, specialty);
    
    std::cout << "Enter course: ";
    std::cin >> course;
    if (course < 1 || course > 6) {
        throw Exception("Invalid course! Must be between 1-6");
    }
    
    std::cout << "Enter average score: ";
    std::cin >> averageScore;
    if (averageScore < 0 || averageScore > 100) {
        throw Exception("Invalid average score! Must be between 0-100");
    }
    std::cin.ignore();
}

void Student::saveToFile(std::ofstream& file) const {
    file << fullName << "\n" << group << "\n" << specialty << "\n"
         << course << "\n" << averageScore << "\n";
}

void Student::loadFromFile(std::ifstream& file) {
    std::getline(file, fullName);
    std::getline(file, group);
    std::getline(file, specialty);
    file >> course;
    file >> averageScore;
    file.ignore();
}

// Setters
void Student::setFullName(const std::string& name) { fullName = name; }
void Student::setGroup(const std::string& grp) { group = grp; }
void Student::setSpecialty(const std::string& spec) { specialty = spec; }
void Student::setCourse(int crs) { 
    if (crs < 1 || crs > 6) throw Exception("Invalid course");
    course = crs; 
}
void Student::setAverageScore(double avg) { 
    if (avg < 0 || avg > 100) throw Exception("Invalid average score");
    averageScore = avg; 
}

// Getters
std::string Student::getFullName() const { return fullName; }
std::string Student::getGroup() const { return group; }
std::string Student::getSpecialty() const { return specialty; }
int Student::getCourse() const { return course; }
double Student::getAverageScore() const { return averageScore; }