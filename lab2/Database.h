#ifndef DATABASE_H
#define DATABASE_H

#include "SIGN.h"

class Database {
private:
    SIGN** records;    // Динамический массив указателей на SIGN
    int capacity;      // Вместимость массива
    int size;          // Текущее количество записей
    
    void resize();
    void swap(SIGN*& a, SIGN*& b);
    
public:
    Database();
    ~Database();
    
    void addRecord(const SIGN& record);
    void addRecordFromInput();
    void sortByBirthday();
    void searchBySurname(const char* surname) const;
    void displayAll() const;
    void displayMenu() const;
    
    // Новые методы для работы с файлами
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);
    
    int getSize() const;
};

#endif