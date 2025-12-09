#include "TextAnalyzer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <cctype>
#include <algorithm>  // Для std::max

// Конструкторы
TextAnalyzer::TextAnalyzer() : words(nullptr), wordCount(0), capacity(0), 
                               longestWord(""), longestWordCount(0) {
    std::cout << "Вызван конструктор без параметров для объекта по адресу: " 
              << this << std::endl;
}

TextAnalyzer::TextAnalyzer(const std::string& filename) : 
    words(nullptr), wordCount(0), capacity(0), longestWord(""), longestWordCount(0) {
    
    std::cout << "Вызван конструктор с параметрами для объекта по адресу: " 
              << this << std::endl;
    loadFromFile(filename);
}

TextAnalyzer::TextAnalyzer(const TextAnalyzer& other) : 
    wordCount(other.wordCount), capacity(other.capacity),
    longestWord(other.longestWord), longestWordCount(other.longestWordCount) {
    
    std::cout << "Вызван конструктор копирования для объекта по адресу: " 
              << this << std::endl;
    
    words = new std::string[capacity];
    for (int i = 0; i < wordCount; i++) {
        words[i] = other.words[i];
    }
}

// Деструктор
TextAnalyzer::~TextAnalyzer() {
    delete[] words;
    std::cout << "Вызван деструктор для объекта по адресу: " << this << std::endl;
}

// Вспомогательные методы
void TextAnalyzer::resize() {
    int newCapacity = (capacity == 0) ? 10 : capacity * 2;
    std::string* newWords = new std::string[newCapacity];
    
    for (int i = 0; i < wordCount; i++) {
        newWords[i] = words[i];
    }
    
    delete[] words;
    words = newWords;
    capacity = newCapacity;
}

bool TextAnalyzer::isDelimiter(char c) const {
    // Проверяем, является ли символ разделителем
    return std::ispunct(static_cast<unsigned char>(c)) || 
           std::isspace(static_cast<unsigned char>(c)) ||
           std::isdigit(static_cast<unsigned char>(c));
}

void TextAnalyzer::extractWordsFromText(const std::string& text) {
    // Очищаем текущие данные
    delete[] words;
    words = nullptr;
    wordCount = 0;
    capacity = 0;
    longestWord = "";
    longestWordCount = 0;
    
    if (text.empty()) {
        return;
    }
    
    std::istringstream iss(text);
    std::string word;
    
    while (iss >> word) {
        // Удаляем знаки препинания с начала и конца слова
        while (!word.empty() && isDelimiter(word.front())) {
            word.erase(0, 1);
        }
        while (!word.empty() && isDelimiter(word.back())) {
            word.pop_back();
        }
        
        // Если слово не пустое после очистки, добавляем его
        if (!word.empty()) {
            // Проверяем, нужно ли увеличить массив
            if (wordCount >= capacity) {
                resize();
            }
            
            // Сохраняем слово в нижнем регистре для корректного сравнения
            std::string lowerWord = word;
            for (size_t i = 0; i < lowerWord.length(); i++) {
                lowerWord[i] = std::tolower(static_cast<unsigned char>(lowerWord[i]));
            }
            
            words[wordCount] = lowerWord;
            wordCount++;
        }
    }
}

void TextAnalyzer::findLongestWord() {
    if (wordCount == 0) {
        longestWord = "";
        longestWordCount = 0;
        return;
    }
    
    size_t maxLength = 0;  // Изменено с int на size_t
    
    // Находим максимальную длину слова
    for (int i = 0; i < wordCount; i++) {
        size_t currentLength = words[i].length();  // Изменено с int на size_t
        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }
    
    // Ищем все слова с максимальной длиной
    std::string candidateWord = "";
    int candidateCount = 0;
    
    for (int i = 0; i < wordCount; i++) {
        if (words[i].length() == maxLength) {  // Теперь оба size_t
            if (candidateWord.empty()) {
                candidateWord = words[i];
                candidateCount = 1;
            } else if (words[i] == candidateWord) {
                candidateCount++;
            }
        }
    }
    
    // Подсчитываем общее количество вхождений самого длинного слова
    if (!candidateWord.empty()) {
        int totalCount = 0;
        for (int i = 0; i < wordCount; i++) {
            if (words[i] == candidateWord) {
                totalCount++;
            }
        }
        
        longestWord = candidateWord;
        longestWordCount = totalCount;
    }
}

// Основные методы
void TextAnalyzer::loadFromFile(const std::string& filename) {
    if (filename.empty()) {
        throw std::invalid_argument("Имя файла не может быть пустым");
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    // Читаем весь файл
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();
    
    file.close();
    
    if (text.empty()) {
        throw std::runtime_error("Файл пуст или не содержит текста");
    }
    
    analyzeText(text);
    std::cout << "Текст успешно загружен из файла: " << filename << std::endl;
}

void TextAnalyzer::analyzeText(const std::string& text) {
    extractWordsFromText(text);
    findLongestWord();
}

// Get методы
const std::string& TextAnalyzer::getLongestWord() const {
    return longestWord;
}

int TextAnalyzer::getLongestWordCount() const {
    return longestWordCount;
}

int TextAnalyzer::getWordCount() const {
    return wordCount;
}

// Вспомогательные методы
void TextAnalyzer::displayResults() const {
    if (wordCount == 0) {
        std::cout << "Текст не содержит слов или не был загружен." << std::endl;
        return;
    }
    
    std::cout << "\n=== РЕЗУЛЬТАТЫ АНАЛИЗА ===" << std::endl;
    std::cout << "Общее количество слов: " << wordCount << std::endl;
    
    if (!longestWord.empty()) {
        std::cout << "Самое длинное слово: \"" << longestWord 
                  << "\" (длина: " << longestWord.length() << " букв)" << std::endl;
        std::cout << "Количество вхождений: " << longestWordCount << std::endl;
    } else {
        std::cout << "Не удалось определить самое длинное слово." << std::endl;
    }
}

void TextAnalyzer::displayAllWords() const {
    if (wordCount == 0) {
        std::cout << "Нет слов для отображения." << std::endl;
        return;
    }
    
    std::cout << "\n=== ВСЕ СЛОВА В ТЕКСТЕ ===" << std::endl;
    std::cout << "Всего слов: " << wordCount << std::endl;
    
    for (int i = 0; i < wordCount; i++) {
        std::cout << i + 1 << ". " << words[i] 
                  << " (длина: " << words[i].length() << ")" << std::endl;
    }
}

// Перегрузка операторов
TextAnalyzer& TextAnalyzer::operator=(const TextAnalyzer& other) {
    std::cout << "Вызван оператор присваивания для объекта по адресу: " 
              << this << std::endl;
    
    if (this != &other) {
        delete[] words;
        
        wordCount = other.wordCount;
        capacity = other.capacity;
        longestWord = other.longestWord;
        longestWordCount = other.longestWordCount;
        
        words = new std::string[capacity];
        for (int i = 0; i < wordCount; i++) {
            words[i] = other.words[i];
        }
    }
    
    return *this;
}

std::ostream& operator<<(std::ostream& os, const TextAnalyzer& analyzer) {
    os << "=== ИНФОРМАЦИЯ ОБ АНАЛИЗАТОРЕ ===" << std::endl;
    os << "Количество слов: " << analyzer.wordCount << std::endl;
    os << "Самое длинное слово: " << analyzer.longestWord << std::endl;
    os << "Количество вхождений: " << analyzer.longestWordCount << std::endl;
    return os;
}