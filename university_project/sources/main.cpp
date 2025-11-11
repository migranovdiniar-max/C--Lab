#include "Keeper.h"
#include <iostream>
#include <limits>

// Глобальная переменная для имени файла по умолчанию
std::string currentFilename = "university_data.txt";

void displayMenu() {
    std::cout << "\n=== University Management System ===\n";
    std::cout << "Current file: " << currentFilename << std::endl;
    std::cout << "1. Add Student\n";
    std::cout << "2. Add Teacher\n";
    std::cout << "3. Add Administrative Staff\n";
    std::cout << "4. Remove Item\n";
    std::cout << "5. Print All\n";
    std::cout << "6. Save to File\n";
    std::cout << "7. Load from File\n";
    std::cout << "8. Edit Item\n";
    std::cout << "9. Change Filename\n";  // Новый пункт меню
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Keeper keeper;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: {
                    Student* student = new Student();
                    student->setData();
                    keeper.add(student);
                    std::cout << "Student added successfully!\n";
                    break;
                }
                case 2: {
                    Teacher* teacher = new Teacher();
                    teacher->setData();
                    keeper.add(teacher);
                    std::cout << "Teacher added successfully!\n";
                    break;
                }
                case 3: {
                    Administrative* admin = new Administrative();
                    admin->setData();
                    keeper.add(admin);
                    std::cout << "Administrative staff added successfully!\n";
                    break;
                }
                case 4: {
                    if (keeper.getSize() == 0) {
                        std::cout << "Keeper is empty!\n";
                        break;
                    }
                    std::cout << "Enter index to remove (1-" << keeper.getSize() << "): ";
                    int index;
                    std::cin >> index;
                    std::cin.ignore();
                    if (index < 1 || index > keeper.getSize()) {
                        std::cout << "Invalid index!\n";
                    } else {
                        keeper.remove(index - 1);
                        std::cout << "Item removed successfully!\n";
                    }
                    break;
                }
                case 5:
                    keeper.printAll();
                    break;
                case 6: {
                    std::cout << "Save to current file '" << currentFilename << "'? (y/n): ";
                    char confirm;
                    std::cin >> confirm;
                    std::cin.ignore();
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        keeper.saveToFile(currentFilename);
                        std::cout << "Data saved successfully to " << currentFilename << "!\n";
                    } else {
                        std::string filename;
                        std::cout << "Enter filename: ";
                        std::getline(std::cin, filename);
                        keeper.saveToFile(filename);
                        std::cout << "Data saved successfully to " << filename << "!\n";
                    }
                    break;
                }
                case 7: {
                    std::cout << "Load from current file '" << currentFilename << "'? (y/n): ";
                    char confirm;
                    std::cin >> confirm;
                    std::cin.ignore();
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        keeper.loadFromFile(currentFilename);
                        std::cout << "Data loaded successfully from " << currentFilename << "!\n";
                    } else {
                        std::string filename;
                        std::cout << "Enter filename: ";
                        std::getline(std::cin, filename);
                        keeper.loadFromFile(filename);
                        std::cout << "Data loaded successfully from " << filename << "!\n";
                    }
                    break;
                }
                case 8: {
                    if (keeper.getSize() == 0) {
                        std::cout << "Keeper is empty!\n";
                        break;
                    }
                    std::cout << "Enter index to edit (1-" << keeper.getSize() << "): ";
                    int index;
                    std::cin >> index;
                    std::cin.ignore();
                    if (index < 1 || index > keeper.getSize()) {
                        std::cout << "Invalid index!\n";
                    } else {
                        keeper.get(index - 1)->setData();
                        std::cout << "Item edited successfully!\n";
                    }
                    break;
                }
                case 9: {
                    std::cout << "Current filename: " << currentFilename << std::endl;
                    std::cout << "Enter new filename: ";
                    std::getline(std::cin, currentFilename);
                    std::cout << "Filename changed to: " << currentFilename << std::endl;
                    break;
                }
                case 0:
                    std::cout << "Exiting...\n";
                    break;
                default:
                    std::cout << "Invalid option!\n";
            }
        } catch (const Exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Unknown error occurred!\n";
        }
    } while (choice != 0);

    return 0;
}