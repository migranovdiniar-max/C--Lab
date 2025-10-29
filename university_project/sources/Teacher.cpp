#include "Teacher.h"
#include <fstream>
#include <sstream>

void Teacher::clearData() {
    delete[] groups;
    delete[] subjects;
    groups = nullptr;
    subjects = nullptr;
    groupsCount = 0;
    subjectsCount = 0;
}

Teacher::Teacher() : groups(nullptr), groupsCount(0), subjects(nullptr), subjectsCount(0) {
    std::cout << "Teacher default constructor called" << std::endl;
}

Teacher::Teacher(const std::string& name, const std::vector<std::string>& grps,
                 const std::vector<std::string>& subjs) : fullName(name) {
    groupsCount = grps.size();
    subjectsCount = subjs.size();
    
    groups = new std::string[groupsCount];
    subjects = new std::string[subjectsCount];
    
    for (int i = 0; i < groupsCount; ++i) groups[i] = grps[i];
    for (int i = 0; i < subjectsCount; ++i) subjects[i] = subjs[i];
    
    std::cout << "Teacher parameterized constructor called" << std::endl;
}

Teacher::Teacher(const Teacher& other) : fullName(other.fullName),
    groupsCount(other.groupsCount), subjectsCount(other.subjectsCount) {
    groups = new std::string[groupsCount];
    subjects = new std::string[subjectsCount];
    
    for (int i = 0; i < groupsCount; ++i) groups[i] = other.groups[i];
    for (int i = 0; i < subjectsCount; ++i) subjects[i] = other.subjects[i];
    
    std::cout << "Teacher copy constructor called" << std::endl;
}

Teacher::~Teacher() {
    clearData();
    std::cout << "Teacher destructor called" << std::endl;
}

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        clearData();
        fullName = other.fullName;
        groupsCount = other.groupsCount;
        subjectsCount = other.subjectsCount;
        
        groups = new std::string[groupsCount];
        subjects = new std::string[subjectsCount];
        
        for (int i = 0; i < groupsCount; ++i) groups[i] = other.groups[i];
        for (int i = 0; i < subjectsCount; ++i) subjects[i] = other.subjects[i];
    }
    std::cout << "Teacher assignment operator called" << std::endl;
    return *this;
}

void Teacher::print() const {
    std::cout << "Teacher: " << fullName << "\nGroups: ";
    for (int i = 0; i < groupsCount; ++i) {
        std::cout << groups[i];
        if (i < groupsCount - 1) std::cout << ", ";
    }
    std::cout << "\nSubjects: ";
    for (int i = 0; i < subjectsCount; ++i) {
        std::cout << subjects[i];
        if (i < subjectsCount - 1) std::cout << ", ";
    }
    std::cout << "\n\n";
}

void Teacher::setData() {
    std::cout << "Enter full name: ";
    std::getline(std::cin, fullName);

    std::cout << "Enter groups (comma separated): ";
    std::string groupsStr;
    std::getline(std::cin, groupsStr);
    
    std::vector<std::string> groupsVec;
    std::stringstream groupsStream(groupsStr);
    std::string group;
    while (std::getline(groupsStream, group, ',')) {
        groupsVec.push_back(group);
    }
    setGroups(groupsVec);

    std::cout << "Enter subjects (comma separated): ";
    std::string subjectsStr;
    std::getline(std::cin, subjectsStr);
    
    std::vector<std::string> subjectsVec;
    std::stringstream subjectsStream(subjectsStr);
    std::string subject;
    while (std::getline(subjectsStream, subject, ',')) {
        subjectsVec.push_back(subject);
    }
    setSubjects(subjectsVec);
}

void Teacher::saveToFile(std::ofstream& file) const {
    file << fullName << "\n" << groupsCount << "\n";
    for (int i = 0; i < groupsCount; ++i) file << groups[i] << "\n";
    file << subjectsCount << "\n";
    for (int i = 0; i < subjectsCount; ++i) file << subjects[i] << "\n";
}

void Teacher::loadFromFile(std::ifstream& file) {
    clearData();
    std::getline(file, fullName);
    
    file >> groupsCount;
    file.ignore();
    groups = new std::string[groupsCount];
    for (int i = 0; i < groupsCount; ++i) std::getline(file, groups[i]);
    
    file >> subjectsCount;
    file.ignore();
    subjects = new std::string[subjectsCount];
    for (int i = 0; i < subjectsCount; ++i) std::getline(file, subjects[i]);
}

// Setters
void Teacher::setFullName(const std::string& name) { fullName = name; }

void Teacher::setGroups(const std::vector<std::string>& grps) {
    delete[] groups;
    groupsCount = grps.size();
    groups = new std::string[groupsCount];
    for (int i = 0; i < groupsCount; ++i) groups[i] = grps[i];
}

void Teacher::setSubjects(const std::vector<std::string>& subjs) {
    delete[] subjects;
    subjectsCount = subjs.size();
    subjects = new std::string[subjectsCount];
    for (int i = 0; i < subjectsCount; ++i) subjects[i] = subjs[i];
}

// Getters
std::string Teacher::getFullName() const { return fullName; }
std::string* Teacher::getGroups() const { return groups; }
int Teacher::getGroupsCount() const { return groupsCount; }
std::string* Teacher::getSubjects() const { return subjects; }
int Teacher::getSubjectsCount() const { return subjectsCount; }