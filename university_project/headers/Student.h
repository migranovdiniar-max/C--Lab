#ifndef STUDENT_H
#define STUDENT_H

#include "Base.h"
#include "Exception.h"
#include <iostream>

class Student : public Base {
private:
    std::string fullName;
    std::string group;
    std::string specialty;
    int course;
    double averageScore;

public:
    Student();
    Student(const std::string& name, const std::string& grp, 
            const std::string& spec, int crs, double avg);
    Student(const Student& other);
    ~Student() override;

    Student& operator=(const Student& other);

    void print() const override;
    void setData() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;

    // Setters
    void setFullName(const std::string& name);
    void setGroup(const std::string& grp);
    void setSpecialty(const std::string& spec);
    void setCourse(int crs);
    void setAverageScore(double avg);

    // Getters
    std::string getFullName() const;
    std::string getGroup() const;
    std::string getSpecialty() const;
    int getCourse() const;
    double getAverageScore() const;
};

#endif