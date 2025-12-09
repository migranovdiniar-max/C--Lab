#include "Database.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <fstream>

Database::Database() : records(nullptr), capacity(0), size(0) {
    std::cout << "Создана база данных" << std::endl;
}

Database::~Database() {
    for (int i = 0; i < size; i++) {
        delete records[i];
    }
    delete[] records;
    std::cout << "База данных уничтожена" << std::endl;
}

void Database::resize() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    SIGN** newRecords = new SIGN*[newCapacity];
    
    for (int i = 0; i < size; i++) {
        newRecords[i] = records[i];
    }
    
    delete[] records;
    records = newRecords;
    capacity = newCapacity;
}

void Database::swap(SIGN*& a, SIGN*& b) {
    SIGN* temp = a;
    a = b;
    b = temp;
}

void Database::addRecord(const SIGN& record) {
    if (size >= capacity) {
        resize();
    }
    records[size] = new SIGN(record);
    size++;
}

void Database::addRecordFromInput() {
    try {
        SIGN newRecord;
        std::cin >> newRecord;
        addRecord(newRecord);
        std::cout << "Запись успешно добавлена!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

void Database::sortByBirthday() {
    // Сортировка пузырьком по дате рождения
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (records[j]->compareBirthdays(*records[j + 1]) > 0) {
                swap(records[j], records[j + 1]);
            }
        }
    }
    std::cout << "Записи отсортированы по дате рождения!" << std::endl;
}

void Database::searchBySurname(const char* surname) const {
    if (surname == nullptr || strlen(surname) == 0) {
        throw std::invalid_argument("Фамилия не может быть пустой");
    }
    
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (strcmp(records[i]->getSurname(), surname) == 0) {
            std::cout << "\nНайдена запись:" << std::endl;
            std::cout << "================" << std::endl;
            records[i]->display();
            found = true;
        }
    }
    
    if (!found) {
        throw std::runtime_error("Запись с такой фамилией не найдена");
    }
}

void Database::displayAll() const {
    if (size == 0) {
        std::cout << "База данных пуста" << std::endl;
        return;
    }
    
    std::cout << "\nВсе записи в базе данных (" << size << " записей):" << std::endl;
    std::cout << "====================================" << std::endl;
    
    for (int i = 0; i < size; i++) {
        std::cout << "Запись #" << (i + 1) << ":" << std::endl;
        records[i]->display();
        if (i < size - 1) {
            std::cout << std::endl;
        }
    }
}

void Database::displayMenu() const {
    std::cout << "\n=== МЕНЮ БАЗЫ ДАННЫХ ===" << std::endl;
    std::cout << "1. Добавить новую запись" << std::endl;
    std::cout << "2. Показать все записи" << std::endl;
    std::cout << "3. Отсортировать записи по дате рождения" << std::endl;
    std::cout << "4. Найти запись по фамилии" << std::endl;
    std::cout << "5. Сохранить данные в файл" << std::endl;
    std::cout << "6. Загрузить данные из файла" << std::endl;
    std::cout << "7. Выйти из программы" << std::endl;
    std::cout << "Выберите действие: ";
}

// Новый метод: сохранение данных в файл
void Database::saveToFile(const char* filename) const {
    if (size == 0) {
        throw std::runtime_error("База данных пуста. Нечего сохранять.");
    }
    
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для записи");
    }
    
    // Сохраняем количество записей
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // Сохраняем каждую запись
    for (int i = 0; i < size; i++) {
        const char* surname = records[i]->getSurname();
        const char* name = records[i]->getName();
        const char* zodiac = records[i]->getZodiac();
        const int* birthday = records[i]->getBirthday();
        
        // Сохраняем длину фамилии и саму фамилию
        int surnameLen = strlen(surname) + 1;
        file.write(reinterpret_cast<const char*>(&surnameLen), sizeof(surnameLen));
        file.write(surname, surnameLen);
        
        // Сохраняем длину имени и само имя
        int nameLen = strlen(name) + 1;
        file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
        file.write(name, nameLen);
        
        // Сохраняем длину знака зодиака и сам знак
        int zodiacLen = strlen(zodiac) + 1;
        file.write(reinterpret_cast<const char*>(&zodiacLen), sizeof(zodiacLen));
        file.write(zodiac, zodiacLen);
        
        // Сохраняем дату рождения (3 int)
        file.write(reinterpret_cast<const char*>(birthday), 3 * sizeof(int));
    }
    
    file.close();
    std::cout << "Данные успешно сохранены в файл '" << filename << "' (" 
              << size << " записей)" << std::endl;
}

// Новый метод: загрузка данных из файла
void Database::loadFromFile(const char* filename) {
    // Очищаем текущие данные
    for (int i = 0; i < size; i++) {
        delete records[i];
    }
    delete[] records;
    
    records = nullptr;
    capacity = 0;
    size = 0;
    
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для чтения");
    }
    
    // Читаем количество записей
    int fileSize;
    file.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
    
    if (fileSize <= 0) {
        throw std::runtime_error("Файл поврежден или пуст");
    }
    
    std::cout << "Загрузка " << fileSize << " записей из файла..." << std::endl;
    
    // Читаем каждую запись
    for (int i = 0; i < fileSize; i++) {
        // Читаем фамилию
        int surnameLen;
        file.read(reinterpret_cast<char*>(&surnameLen), sizeof(surnameLen));
        char* surname = new char[surnameLen];
        file.read(surname, surnameLen);
        
        // Читаем имя
        int nameLen;
        file.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        char* name = new char[nameLen];
        file.read(name, nameLen);
        
        // Читаем знак зодиака
        int zodiacLen;
        file.read(reinterpret_cast<char*>(&zodiacLen), sizeof(zodiacLen));
        char* zodiac = new char[zodiacLen];
        file.read(zodiac, zodiacLen);
        
        // Читаем дату рождения
        int birthday[3];
        file.read(reinterpret_cast<char*>(birthday), 3 * sizeof(int));
        
        // Создаем и добавляем запись
        try {
            SIGN newRecord(surname, name, zodiac, birthday);
            addRecord(newRecord);
        } catch (const std::exception& e) {
            // Очищаем временные буферы
            delete[] surname;
            delete[] name;
            delete[] zodiac;
            throw std::runtime_error(std::string("Ошибка при загрузке записи: ") + e.what());
        }
        
        // Очищаем временные буферы
        delete[] surname;
        delete[] name;
        delete[] zodiac;
    }
    
    file.close();
    std::cout << "Данные успешно загружены из файла '" << filename << "'" << std::endl;
}

int Database::getSize() const {
    return size;
}