#include "filehandler.h"
#include <iostream>
#include <cstdio> // remove
#include <fstream>

// определяем глобальную переменную один раз
const char* DATA_FILENAME = "data.txt";

void createNewFile() {
    try {
        std::cout << "Сколько записей вы хотите ввести (N)? ";
        int N; if (!(std::cin >> N)) { std::cin.clear(); std::cin.ignore(1000,'\n'); throw AppException("Invalid N"); }
        std::cin.ignore(1000,'\n');
        Roster roster;
        for (int i=0;i<N;++i) {
            std::cout << "\nВвод записи #" << (i+1) << ":\n";
            SIGN s;
            std::cin >> s;
            roster.add(s);
        }
        roster.sortByBirthday();
        roster.saveToFile(DATA_FILENAME);
        std::cout << "Файл '" << DATA_FILENAME << "' сохранён (" << roster.getSize() << " записей).\n";
    } catch (const AppException& e) {
        std::cout << "Ошибка: " << e.msg << "\n";
    } catch (...) {
        std::cout << "Неизвестная ошибка при создании файла.\n";
    }
}

void appendToFile() {
    try {
        // load existing (if any) to keep consistent sorting after append
        Roster roster;
        // if file exists, load; if not, start empty
        std::ifstream test(DATA_FILENAME);
        if (test) {
            test.close();
            roster.loadFromFile(DATA_FILENAME);
        }
        std::cout << "Сколько записей добавить? ";
        int M; if (!(std::cin >> M)) { std::cin.clear(); std::cin.ignore(1000,'\n'); throw AppException("Invalid M"); }
        std::cin.ignore(1000,'\n');
        for (int i=0;i<M;++i) {
            std::cout << "\nВвод записи для добавления #" << (i+1) << ":\n";
            SIGN s; std::cin >> s;
            roster.add(s);
        }
        roster.sortByBirthday();
        roster.saveToFile(DATA_FILENAME); // overwrite with full sorted list
        std::cout << "Файл обновлён: " << roster.getSize() << " записей.\n";
    } catch (const AppException& e) {
        std::cout << "Ошибка: " << e.msg << "\n";
    } catch (...) {
        std::cout << "Неизвестная ошибка при добавлении.\n";
    }
}

void showAll() {
    try {
        Roster roster;
        roster.loadFromFile(DATA_FILENAME);
        int n = roster.getSize();
        if (n==0) { std::cout << "Файл пуст или не содержит записей.\n"; return; }
        std::cout << "Всего записей: " << n << "\n\n";
        for (int i=0;i<n;++i) {
            const SIGN* p = roster.getAt(i);
            int d,m,y; p->getBirthday(d,m,y);
            std::cout << (i+1) << ") " << p->getSurname() << " " << p->getName() << " | "
                      << p->getZodiac() << " | " << d << "." << m << "." << y << "\n";
        }
    } catch (const AppException& e) {
        std::cout << "Ошибка: " << e.msg << "\n";
    } catch (...) {
        std::cout << "Неизвестная ошибка при чтении файла.\n";
    }
}

void searchBySurname() {
    try {
        std::cout << "Введите фамилию для поиска: ";
        char buf[256]; std::cin >> std::ws; std::cin.getline(buf,256);
        Roster roster;
        roster.loadFromFile(DATA_FILENAME);
        SIGN* found = roster.findBySurname(buf);
        if (found) {
            int d,m,y; found->getBirthday(d,m,y);
            std::cout << "Найдена запись:\n";
            std::cout << "Surname: " << found->getSurname() << "\n";
            std::cout << "Name: " << found->getName() << "\n";
            std::cout << "Zodiac: " << found->getZodiac() << "\n";
            std::cout << "Birthday: " << d << " " << m << " " << y << "\n";
        } else {
            std::cout << "Запись с фамилией '" << buf << "' не найдена в файле.\n";
        }
    } catch (const AppException& e) {
        std::cout << "Ошибка: " << e.msg << "\n";
    } catch (...) {
        std::cout << "Неизвестная ошибка при поиске.\n";
    }
}

void deleteDataFile() {
    if (std::remove(DATA_FILENAME) == 0) {
        std::cout << "Файл '" << DATA_FILENAME << "' удалён.\n";
    } else {
        std::cout << "Не удалось удалить файл (возможно, его нет).\n";
    }
}
