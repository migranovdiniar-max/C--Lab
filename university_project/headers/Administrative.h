#ifndef ADMINISTRATIVE_H
#define ADMINISTRATIVE_H

#include "Base.h"
#include "Exception.h"
#include <iostream>

class Administrative : public Base {
private:
    std::string fullName;
    std::string position;
    std::string phone;
    std::string responsibility;

public:
    Administrative();
    Administrative(const std::string& name, const std::string& pos,
                   const std::string& ph, const std::string& resp);
    Administrative(const Administrative& other);
    ~Administrative() override;

    Administrative& operator=(const Administrative& other);

    void print() const override;
    void setData() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;

    // Setters
    void setFullName(const std::string& name);
    void setPosition(const std::string& pos);
    void setPhone(const std::string& ph);
    void setResponsibility(const std::string& resp);

    // Getters
    std::string getFullName() const;
    std::string getPosition() const;
    std::string getPhone() const;
    std::string getResponsibility() const;
};

#endif