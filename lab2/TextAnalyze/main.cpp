#include "TextAnalyzer.h"
#include <iostream>
#include <limits>

void displayMenu() {
    std::cout << "\n=== МЕНЮ АНАЛИЗАТОРА ТЕКСТА ===" << std::endl;
    std::cout << "1. Загрузить текст из файла" << std::endl;
    std::cout << "2. Ввести текст с клавиатуры" << std::endl;
    std::cout << "3. Показать результаты анализа" << std::endl;
    std::cout << "4. Показать все слова из текста" << std::endl;
    std::cout << "5. Создать копию анализатора" << std::endl;
    std::cout << "6. Выйти из программы" << std::endl;
    std::cout << "Выберите действие: ";
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // Установка локали для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");
    
    TextAnalyzer analyzer;
    TextAnalyzer* analyzerCopy = nullptr;
    
    std::cout << "=== ПРОГРАММА ДЛЯ АНАЛИЗА ТЕКСТА ===" << std::endl;
    std::cout << "Находит самое длинное слово и считает его вхождения" << std::endl;
    
    int choice = 0;
    
    do {
        try {
            displayMenu();
            
            if (!(std::cin >> choice)) {
                throw std::invalid_argument("Неверный ввод. Введите число от 1 до 6.");
            }
            
            clearInputBuffer();
            
            switch (choice) {
                case 1: {
                    std::string filename;
                    std::cout << "\n=== ЗАГРУЗКА ИЗ ФАЙЛА ===" << std::endl;
                    std::cout << "Введите имя файла (например: text.txt): ";
                    std::getline(std::cin, filename);
                    
                    try {
                        analyzer.loadFromFile(filename);
                        analyzer.displayResults();
                    } catch (const std::exception& e) {
                        std::cout << "Ошибка: " << e.what() << std::endl;
                    }
                    break;
                }
                    
                case 2: {
                    std::string text;
                    std::cout << "\n=== ВВОД ТЕКСТА С КЛАВИАТУРЫ ===" << std::endl;
                    std::cout << "Введите текст (для завершения ввода введите 'END' на отдельной строке):" << std::endl;
                    std::cout << "----------------------------------------" << std::endl;
                    
                    std::string line;
                    while (std::getline(std::cin, line)) {
                        if (line == "END") {
                            break;
                        }
                        text += line + "\n";
                    }
                    
                    if (text.empty()) {
                        std::cout << "Текст не был введен." << std::endl;
                    } else {
                        analyzer.analyzeText(text);
                        std::cout << "\nТекст успешно проанализирован!" << std::endl;
                        analyzer.displayResults();
                    }
                    break;
                }
                    
                case 3: {
                    analyzer.displayResults();
                    break;
                }
                    
                case 4: {
                    analyzer.displayAllWords();
                    break;
                }
                    
                case 5: {
                    if (analyzer.getWordCount() == 0) {
                        std::cout << "Анализатор пуст. Сначала загрузите текст." << std::endl;
                    } else {
                        // Очищаем предыдущую копию, если она существует
                        delete analyzerCopy;
                        
                        // Создаем новую копию
                        analyzerCopy = new TextAnalyzer(analyzer);
                        
                        std::cout << "\n=== КОПИЯ АНАЛИЗАТОРА СОЗДАНА ===" << std::endl;
                        std::cout << "Информация о копии:" << std::endl;
                        analyzerCopy->displayResults();
                    }
                    break;
                }
                    
                case 6: {
                    std::cout << "\nВыход из программы..." << std::endl;
                    break;
                }
                    
                default: {
                    std::cout << "Неверный выбор. Пожалуйста, выберите от 1 до 6." << std::endl;
                    break;
                }
            }
            
        } catch (const std::exception& e) {
            std::cout << "Произошла ошибка: " << e.what() << std::endl;
            clearInputBuffer();
        }
        
    } while (choice != 6);
    
    // Очищаем память, выделенную для копии
    delete analyzerCopy;
    
    return 0;
}