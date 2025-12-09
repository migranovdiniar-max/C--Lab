#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "roster.h"

// filename fixed per requirement
extern const char* DATA_FILENAME;

// helpers for menu operations
void createNewFile();      // overwrite: ask N, input N items, save (sorted)
void appendToFile();       // ask M, input M items, append & sort
void showAll();            // read file and print all
void searchBySurname();    // read file and search by surname, print or message
void deleteDataFile();     // delete data.txt
#endif
