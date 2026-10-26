#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct WordCard {
    string foreignWord;
    string translation;

    WordCard();
    WordCard(string fw, string tr);
    WordCard(const WordCard& other);

    string getForeignWord() const;
    string getTranslation() const;
    bool setForeignWord(string fw);
    bool setTranslation(string tr);

    WordCard& operator=(const WordCard& other);
    operator string() const;

    friend bool operator==(const WordCard& c1, const WordCard& c2);
    friend bool operator!=(const WordCard& c1, const WordCard& c2);
    friend ostream& operator<<(ostream& out, const WordCard& card);
    friend istream& operator>>(istream& in, WordCard& card);
};

#pragma pack(push, 1)
struct DictionaryPack1 {
    string dictName;
    int maxSize;
    int count;
    WordCard* cards;
};
#pragma pack(pop)

class Dictionary {
private:
    static const int MAX_SIZE = 100;
    string dictName;
    int maxSize;
    int count;
    WordCard* cards;

public:
    Dictionary();
    Dictionary(string name, int initialSize = MAX_SIZE);
    Dictionary(string name, int initialSize, const WordCard* arr, int arrCount);
    Dictionary(const Dictionary& other);
    ~Dictionary();

    string getDictName() const;
    int size() const;
    int getSize() const;
    int getCount() const;
    WordCard getCard(int index) const;

    bool setDictName(string name);
    bool setSize(int newSize);
    bool setCount(int newCount);

    bool addCard(const WordCard& card);
    bool addCard(string foreignWord, string translation);
    bool removeCard(string foreignWord);
    int findWordIndex(string foreignWord) const;
    WordCard findWord(string foreignWord) const;

    Dictionary& operator=(const Dictionary& other);
    WordCard& operator[](string foreignWord);
    WordCard& operator[](int index);
    operator string() const;

    Dictionary& operator++();
    Dictionary operator++(int);
    Dictionary& operator--();
    Dictionary operator--(int);

    friend Dictionary operator+(const Dictionary& d1, const Dictionary& d2); // Об'єднання
    friend Dictionary operator*(const Dictionary& d1, const Dictionary& d2); // Перетин
    friend Dictionary operator-(const Dictionary& d1, const Dictionary& d2); // Різниця
    friend bool operator==(const Dictionary& d1, const Dictionary& d2);
    friend bool operator!=(const Dictionary& d1, const Dictionary& d2);

    friend ostream& operator<<(ostream& out, const Dictionary& d);
    friend istream& operator>>(istream& in, Dictionary& d);
};