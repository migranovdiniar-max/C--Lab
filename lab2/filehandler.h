#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "roster.h"

extern const char* DATA_FILENAME;

void createNewFile();
void appendToFile();
void showAll();
void searchBySurname();
void deleteDataFile();

#endif
