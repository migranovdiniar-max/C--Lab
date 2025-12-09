#include "filehandler.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

const char* DATA_FILENAME="data.txt";

void createNewFile() {
    std::ofstream fout(DATA_FILENAME,std::ios::binary|std::ios::trunc);
    if(!fout){ std::cout<<"Ошибка создания файла\n"; return; }

    int N; std::cout<<"Сколько записей создать? "; std::cin>>N; std::cin.ignore();
    Roster roster;
    for(int i=0;i<N;i++){
        std::cout<<"\nЗапись #"<<i+1<<":\n";
        SIGN s; std::cin>>s;
        roster.add(s);
    }
    roster.sortByBirth();
    for(int i=0;i<roster.getSize();i++)
        fout.write(reinterpret_cast<char*>(&roster[i]),sizeof(SIGN));
    fout.close();
    std::cout<<"Файл создан.\n";
}

void appendToFile() {
    std::ifstream fin(DATA_FILENAME,std::ios::binary);
    Roster roster;
    if(fin){
        SIGN s;
        while(fin.read(reinterpret_cast<char*>(&s),sizeof(SIGN))) roster.add(s);
        fin.close();
    }
    int M; std::cout<<"Сколько записей добавить? "; std::cin>>M; std::cin.ignore();
    for(int i=0;i<M;i++){
        std::cout<<"\nЗапись #"<<i+1<<":\n";
        SIGN s; std::cin>>s;
        roster.add(s);
    }
    roster.sortByBirth();
    std::ofstream fout(DATA_FILENAME,std::ios::binary|std::ios::trunc);
    for(int i=0;i<roster.getSize();i++)
        fout.write(reinterpret_cast<char*>(&roster[i]),sizeof(SIGN));
    fout.close();
    std::cout<<"Файл обновлён.\n";
}

void showAll() {
    std::ifstream fin(DATA_FILENAME,std::ios::binary);
    if(!fin){ std::cout<<"Файл отсутствует.\n"; return; }
    SIGN s;
    while(fin.read(reinterpret_cast<char*>(&s),sizeof(SIGN))) s.show();
    fin.close();
}

void searchBySurname() {
    std::ifstream fin(DATA_FILENAME,std::ios::binary);
    if(!fin){ std::cout<<"Файл отсутствует.\n"; return; }
    std::cout<<"Введите фамилию для поиска: ";
    char target[50]; std::cin.getline(target,50);
    bool found=false;
    SIGN s;
    while(fin.read(reinterpret_cast<char*>(&s),sizeof(SIGN))){
        if(strcmp(s.getSurname(),target)==0){ s.show(); found=true; }
    }
    if(!found) std::cout<<"Пользователи с фамилией '"<<target<<"' не найдены.\n";
    fin.close();
}

void deleteDataFile() {
    if(std::remove(DATA_FILENAME)==0) std::cout<<"Файл удалён.\n";
    else std::cout<<"Ошибка удаления или файл отсутствует.\n";
}
