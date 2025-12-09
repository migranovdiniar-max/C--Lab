#include "Database.h"
#include <iostream>
#include <cstring>
#include <limits>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // Установка локали для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");
    
    Database db;
    int choice = 0;
    
    std::cout << "=== ПРОГРАММА ДЛЯ РАБОТЫ С БАЗОЙ ДАННЫХ ===" << std::endl;
    std::cout << "Автор: студент" << std::endl;
    
    do {
        try {
            db.displayMenu();
            
            if (!(std::cin >> choice)) {
                throw std::invalid_argument("Неверный ввод. Введите число от 1 до 7.");
            }
            
            clearInputBuffer();
            
            switch (choice) {
                case 1: {
                    std::cout << "\n=== ДОБАВЛЕНИЕ НОВОЙ ЗАПИСИ ===" << std::endl;
                    db.addRecordFromInput();
                    break;
                }
                    
                case 2: {
                    std::cout << "\n=== ВСЕ ЗАПИСИ ===" << std::endl;
                    db.displayAll();
                    break;
                }
                    
                case 3: {
                    if (db.getSize() == 0) {
                        std::cout << "База данных пуста. Нечего сортировать." << std::endl;
                    } else {
                        db.sortByBirthday();
                        std::cout << "\nРезультат сортировки:" << std::endl;
                        db.displayAll();
                    }
                    break;
                }
                    
                case 4: {
                    if (db.getSize() == 0) {
                        std::cout << "База данных пуста. Нечего искать." << std::endl;
                    } else {
                        char surname[100];
                        std::cout << "\n=== ПОИСК ПО ФАМИЛИИ ===" << std::endl;
                        std::cout << "Введите фамилию для поиска: ";
                        std::cin.getline(surname, 100);
                        
                        try {
                            db.searchBySurname(surname);
                        } catch (const std::exception& e) {
                            std::cout << "Ошибка: " << e.what() << std::endl;
                        }
                    }
                    break;
                }
                    
                case 5: {
                    if (db.getSize() == 0) {
                        std::cout << "База данных пуста. Нечего сохранять." << std::endl;
                    } else {
                        char filename[100];
                        std::cout << "\n=== СОХРАНЕНИЕ В ФАЙЛ ===" << std::endl;
                        std::cout << "Введите имя файла для сохранения (например: data.bin): ";
                        std::cin.getline(filename, 100);
                        
                        try {
                            db.saveToFile(filename);
                        } catch (const std::exception& e) {
                            std::cout << "Ошибка при сохранении: " << e.what() << std::endl;
                        }
                    }
                    break;
                }
                    
                case 6: {
                    char filename[100];
                    std::cout << "\n=== ЗАГРУЗКА ИЗ ФАЙЛА ===" << std::endl;
                    std::cout << "Внимание! Текущие данные будут удалены." << std::endl;
                    std::cout << "Введите имя файла для загрузки (например: data.bin): ";
                    std::cin.getline(filename, 100);
                    
                    try {
                        db.loadFromFile(filename);
                        std::cout << "\nЗагруженные данные:" << std::endl;
                        db.displayAll();
                    } catch (const std::exception& e) {
                        std::cout << "Ошибка при загрузке: " << e.what() << std::endl;
                    }
                    break;
                }
                    
                case 7: {
                    std::cout << "\nВыход из программы..." << std::endl;
                    break;
                }
                    
                default: {
                    std::cout << "Неверный выбор. Пожалуйста, выберите от 1 до 7." << std::endl;
                    break;
                }
            }
            
        } catch (const std::exception& e) {
            std::cout << "Произошла ошибка: " << e.what() << std::endl;
            clearInputBuffer();
        }
        
    } while (choice != 7);
    
    return 0;
}