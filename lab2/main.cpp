#include <iostream>
#include "filehandler.h"

void menu() {
    std::cout << "\n====== MENU ======\n";
    std::cout << "1. Создать новый файл (перезаписать data.txt) — ввести N записей\n";
    std::cout << "2. Добавить записи (append, затем сортировка и сохранение)\n";
    std::cout << "3. Показать все записи из data.txt\n";
    std::cout << "4. Поиск по фамилии (читает из data.txt)\n";
    std::cout << "5. Удалить файл data.txt\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите опцию: ";
}

int main() {
    // Переключаем консоль на UTF-8
    SetConsoleCP(CP_UTF8);   // ввод
    SetConsoleOutputCP(CP_UTF8); // вывод

    // Для корректной работы cout/cin с UTF-8
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U8TEXT);
    
    bool running = true;
    while (running) {
        menu();
        int opt;
        if (!(std::cin >> opt)) {
            std::cin.clear(); std::cin.ignore(1000,'\n');
            std::cout << "Неверный ввод, попробуйте снова.\n";
            continue;
        }
        std::cin.ignore(1000,'\n');
        switch (opt) {
            case 1: createNewFile(); break;
            case 2: appendToFile(); break;
            case 3: showAll(); break;
            case 4: searchBySurname(); break;
            case 5: deleteDataFile(); break;
            case 0: running = false; break;
            default: std::cout << "Неизвестная опция.\n";
        }
    }
    std::cout << "Выход. До свидания.\n";
    return 0;
}
