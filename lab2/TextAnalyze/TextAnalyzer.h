#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H

#include <string>

class TextAnalyzer {
private:
    std::string* words;           // Динамический массив слов
    int wordCount;                // Количество слов
    int capacity;                 // Вместимость массива
    std::string longestWord;      // Самое длинное слово
    int longestWordCount;         // Количество вхождений самого длинного слова
    
    void resize();
    void extractWordsFromText(const std::string& text);
    bool isDelimiter(char c) const;
    void findLongestWord();
    
public:
    // Конструкторы
    TextAnalyzer();
    explicit TextAnalyzer(const std::string& filename);
    TextAnalyzer(const TextAnalyzer& other);
    
    // Деструктор
    ~TextAnalyzer();
    
    // Основные методы
    void loadFromFile(const std::string& filename);
    void analyzeText(const std::string& text);
    
    // Get методы
    const std::string& getLongestWord() const;
    int getLongestWordCount() const;
    int getWordCount() const;
    
    // Вспомогательные методы
    void displayResults() const;
    void displayAllWords() const;
    
    // Перегрузка операторов
    TextAnalyzer& operator=(const TextAnalyzer& other);
    friend std::ostream& operator<<(std::ostream& os, const TextAnalyzer& analyzer);
};

#endif