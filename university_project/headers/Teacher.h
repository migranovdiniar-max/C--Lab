#ifndef TEACHER_H
#define TEACHER_H

#include "Base.h"
#include "Exception.h"
#include <iostream>
#include <vector>

class Teacher : public Base {
private:
    std::string fullName;
    std::string* groups;
    int groupsCount;
    std::string* subjects;
    int subjectsCount;

    void clearData();

public:
    Teacher();
    Teacher(const std::string& name, const std::vector<std::string>& grps, 
            const std::vector<std::string>& subjs);
    Teacher(const Teacher& other);
    ~Teacher() override;

    Teacher& operator=(const Teacher& other);

    void print() const override;
    void setData() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;

    // Setters
    void setFullName(const std::string& name);
    void setGroups(const std::vector<std::string>& grps);
    void setSubjects(const std::vector<std::string>& subjs);

    // Getters
    std::string getFullName() const;
    std::string* getGroups() const;
    int getGroupsCount() const;
    std::string* getSubjects() const;
    int getSubjectsCount() const;
};

#endif