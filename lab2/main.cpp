#include <iostream>
#include <windows.h>
#include <limits>
#include "filehandler.h"

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    do{
        std::cout<<"\n====== MENU ======\n";
        std::cout<<"1. Создать новый файл (data.txt) и ввести N записей\n";
        std::cout<<"2. Добавить записи к существующему файлу (append)\n";
        std::cout<<"3. Просмотреть все записи из data.txt\n";
        std::cout<<"4. Поиск человека по фамилии\n";
        std::cout<<"5. Удалить файл data.txt\n";
        std::cout<<"0. Выход\n";
        std::cout<<"Выберите пункт: ";
        std::cin>>choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        switch(choice){
            case 1: createNewFile(); break;
            case 2: appendToFile(); break;
            case 3: showAll(); break;
            case 4: searchBySurname(); break;
            case 5: deleteDataFile(); break;
            case 0: std::cout<<"Выход.\n"; break;
            default: std::cout<<"Неверный выбор.\n";
        }
    }while(choice!=0);
    return 0;
}
