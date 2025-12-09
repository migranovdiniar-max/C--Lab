#include "filehandler.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

const char* DATA_FILENAME="data.txt";

void createNewFile() {
    std::ofstream fout(DATA_FILENAME);
    if(!fout){ std::cout<<"Ошибка создания файла\n"; return; }

    int N; std::cout<<"Сколько записей создать? "; std::cin>>N; std::cin.ignore();
    for(int i=0;i<N;i++){
        std::cout<<"\nЗапись #"<<i+1<<":\n";
        SIGN s; std::cin>>s;
        fout << s << "\n"; // сохраняем в текстовом виде
    }
    std::cout<<"Файл создан.\n";
}

void appendToFile() {
    std::ofstream fout(DATA_FILENAME,std::ios::app);
    int M; std::cout<<"Сколько записей добавить? "; std::cin>>M; std::cin.ignore();
    for(int i=0;i<M;i++){
        std::cout<<"\nЗапись #"<<i+1<<":\n";
        SIGN s; std::cin>>s;
        fout << s << "\n";
    }
    std::cout<<"Файл обновлён.\n";
}

void showAll() {
    std::ifstream fin(DATA_FILENAME);
    if(!fin){ std::cout<<"Файл отсутствует.\n"; return; }
    std::string line;
    while(std::getline(fin,line)) std::cout << line << "\n";
}

void searchBySurname() {
    std::ifstream fin(DATA_FILENAME);
    if(!fin){ std::cout<<"Файл отсутствует.\n"; return; }

    std::cout<<"Введите фамилию для поиска: ";
    std::string target; std::getline(std::cin,target);
    bool found=false;

    std::string line;
    while(std::getline(fin,line)){
        if(line.find(target)==0){ // фамилия в начале строки
            std::cout << line << "\n";
            found=true;
        }
    }

    if(!found) std::cout<<"Пользователи с фамилией '"<<target<<"' не найдены.\n";
}

void deleteDataFile() {
    if(std::remove(DATA_FILENAME)==0) std::cout<<"Файл удалён.\n";
    else std::cout<<"Ошибка удаления или файл отсутствует.\n";
}
