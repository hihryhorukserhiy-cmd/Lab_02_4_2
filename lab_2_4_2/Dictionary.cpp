#include "Dictionary.h"

WordCard::WordCard() : foreignWord(""), translation("") {}

WordCard::WordCard(string fw, string tr) {
    if (!setForeignWord(fw)) foreignWord = "unknown";
    if (!setTranslation(tr)) translation = "невідомо";
}

WordCard::WordCard(const WordCard& other) {
    foreignWord = other.foreignWord;
    translation = other.translation;
}

string WordCard::getForeignWord() const { return foreignWord; }
string WordCard::getTranslation() const { return translation; }

bool WordCard::setForeignWord(string fw) {
    if (fw.empty()) {
        cerr << "Помилка: Іноземне слово не може бути порожнім!" << endl;
        return false;
    }
    foreignWord = fw;
    return true;
}

bool WordCard::setTranslation(string tr) {
    if (tr.empty()) {
        cerr << "Помилка: Переклад не може бути порожнім!" << endl;
        return false;
    }
    translation = tr;
    return true;
}

WordCard& WordCard::operator=(const WordCard& other) {
    if (this != &other) {
        foreignWord = other.foreignWord;
        translation = other.translation;
    }
    return *this;
}

WordCard::operator string() const {
    return foreignWord + " - " + translation;
}

bool operator==(const WordCard& c1, const WordCard& c2) {

    return c1.foreignWord == c2.foreignWord;
}

bool operator!=(const WordCard& c1, const WordCard& c2) {
    return !(c1 == c2);
}

ostream& operator<<(ostream& out, const WordCard& card) {
    out << string(card);
    return out;
}

istream& operator>>(istream& in, WordCard& card) {
    string fw, tr;
    cout << "  Іноземне слово: ";
    in >> fw;
    cout << "  Переклад: ";
    in >> tr;
    card.setForeignWord(fw);
    card.setTranslation(tr);
    return in;
}

Dictionary::Dictionary() {
    dictName = "Без назви";
    maxSize = MAX_SIZE;
    count = 0;
    cards = new WordCard[maxSize];
}

Dictionary::Dictionary(string name, int initialSize) {
    if (!setDictName(name)) {
        dictName = "Без назви";
    }
    if (initialSize > 0 && initialSize <= MAX_SIZE) {
        maxSize = initialSize;
    }
    else {
        maxSize = MAX_SIZE;
    }
    count = 0;
    cards = new WordCard[maxSize];
}

Dictionary::Dictionary(string name, int initialSize, const WordCard* arr, int arrCount) {
    if (!setDictName(name)) {
        dictName = "Без назви";
    }
    if (initialSize > 0 && initialSize <= MAX_SIZE) {
        maxSize = initialSize;
    }
    else {
        maxSize = MAX_SIZE;
    }
    count = 0;
    cards = new WordCard[maxSize];

    if (arr != nullptr && arrCount > 0) {
        for (int i = 0; i < arrCount && count < maxSize; ++i) {
            addCard(arr[i]); // Забезпечує перевірку на дублікати
        }
    }
}

Dictionary::Dictionary(const Dictionary& other) {
    dictName = other.dictName;
    maxSize = other.maxSize;
    count = other.count;
    cards = new WordCard[maxSize];
    for (int i = 0; i < count; ++i) {
        cards[i] = other.cards[i];
    }
}

Dictionary::~Dictionary() {
    delete[] cards;
}

string Dictionary::getDictName() const { return dictName; }
int Dictionary::size() const { return maxSize; }
int Dictionary::getSize() const { return maxSize; }
int Dictionary::getCount() const { return count; }

WordCard Dictionary::getCard(int index) const {
    if (index >= 0 && index < count) {
        return cards[index];
    }
    cerr << "Помилка: Індекс картки поза межами!" << endl;
    return WordCard();
}

bool Dictionary::setDictName(string name) {
    if (name.empty()) {
        cerr << "Помилка: Назва словника не може бути порожньою!" << endl;
        return false;
    }
    dictName = name;
    return true;
}

bool Dictionary::setSize(int newSize) {
    if (newSize <= 0 || newSize > MAX_SIZE) {
        cerr << "Помилка: Розмір має бути в межах від 1 до " << MAX_SIZE << "!" << endl;
        return false;
    }
    WordCard* temp = new WordCard[newSize];
    int newCount = (count < newSize) ? count : newSize;
    for (int i = 0; i < newCount; ++i) {
        temp[i] = cards[i];
    }
    delete[] cards;
    cards = temp;
    maxSize = newSize;
    count = newCount;
    return true;
}

bool Dictionary::setCount(int newCount) {
    if (newCount >= 0 && newCount <= maxSize) {
        count = newCount;
        return true;
    }
    cerr << "Помилка: Некоректна кількість елементів!" << endl;
    return false;
}

int Dictionary::findWordIndex(string foreignWord) const {
    for (int i = 0; i < count; ++i) {
        if (cards[i].foreignWord == foreignWord) {
            return i;
        }
    }
    return -1;
}

WordCard Dictionary::findWord(string foreignWord) const {
    int idx = findWordIndex(foreignWord);
    if (idx != -1) {
        return cards[idx];
    }
    cerr << "Слово '" << foreignWord << "' не знайдено у словнику!" << endl;
    return WordCard();
}

bool Dictionary::addCard(const WordCard& card) {
    if (card.foreignWord.empty() || card.translation.empty()) {
        cerr << "Помилка: Неможливо додати порожню картку!" << endl;
        return false;
    }
    if (findWordIndex(card.foreignWord) != -1) {
        cerr << "Попередження: Слово '" << card.foreignWord << "' вже є у словнику (дублікати заборонені)!" << endl;
        return false;
    }
    if (count >= maxSize) {
        cerr << "Помилка: Словник переповнений!" << endl;
        return false;
    }
    cards[count] = card;
    count++;
    return true;
}

bool Dictionary::addCard(string foreignWord, string translation) {
    if (foreignWord.empty() || translation.empty()) {
        cerr << "Помилка: Слово та переклад не можуть бути порожніми!" << endl;
        return false;
    }
    return addCard(WordCard(foreignWord, translation));
}

bool Dictionary::removeCard(string foreignWord) {
    int idx = findWordIndex(foreignWord);
    if (idx == -1) {
        cerr << "Помилка видалення: Слово '" << foreignWord << "' не знайдено!" << endl;
        return false;
    }
    for (int i = idx; i < count - 1; ++i) {
        cards[i] = cards[i + 1];
    }
    count--;
    return true;
}

Dictionary& Dictionary::operator=(const Dictionary& other) {
    if (this != &other) {
        delete[] cards;
        dictName = other.dictName;
        maxSize = other.maxSize;
        count = other.count;
        cards = new WordCard[maxSize];
        for (int i = 0; i < count; ++i) {
            cards[i] = other.cards[i];
        }
    }
    return *this;
}

WordCard& Dictionary::operator[](string foreignWord) {
    int idx = findWordIndex(foreignWord);
    if (idx != -1) {
        return cards[idx];
    }
    cerr << "Помилка індексування: Слово '" << foreignWord << "' не знайдено!" << endl;
    static WordCard dummyCard;
    dummyCard = WordCard();
    return dummyCard;
}

WordCard& Dictionary::operator[](int index) {
    if (index >= 0 && index < count) {
        return cards[index];
    }
    cerr << "Помилка індексування: Індекс " << index << " поза межами!" << endl;
    static WordCard dummyCard;
    dummyCard = WordCard();
    return dummyCard;
}

Dictionary::operator string() const {
    stringstream ss;
    ss << "Словник: \"" << dictName << "\" (Слів: " << count << "/" << maxSize << ")\n";
    if (count == 0) {
        ss << "  [порожній]\n";
    }
    else {
        for (int i = 0; i < count; ++i) {
            ss << "  " << (i + 1) << ". " << string(cards[i]) << "\n";
        }
    }
    return ss.str();
}

Dictionary& Dictionary::operator++() {
    if (maxSize < MAX_SIZE) {
        setSize(maxSize + 1);
    }
    return *this;
}

Dictionary Dictionary::operator++(int) {
    Dictionary temp(*this);
    ++(*this);
    return temp;
}

Dictionary& Dictionary::operator--() {
    if (count > 0) {
        count--;
    }
    return *this;
}

Dictionary Dictionary::operator--(int) {
    Dictionary temp(*this);
    --(*this);
    return temp;
}

Dictionary operator+(const Dictionary& d1, const Dictionary& d2) {
    int newMax = d1.maxSize + d2.maxSize;
    if (newMax > Dictionary::MAX_SIZE) newMax = Dictionary::MAX_SIZE;

    Dictionary result(d1.dictName + " + " + d2.dictName, newMax);
    for (int i = 0; i < d1.count; ++i) {
        result.addCard(d1.cards[i]);
    }
    for (int i = 0; i < d2.count; ++i) {
        if (result.findWordIndex(d2.cards[i].foreignWord) == -1) {
            result.addCard(d2.cards[i]);
        }
    }
    return result;
}

Dictionary operator*(const Dictionary& d1, const Dictionary& d2) {
    int minMax = (d1.maxSize < d2.maxSize) ? d1.maxSize : d2.maxSize;
    Dictionary result(d1.dictName + " * " + d2.dictName, minMax);

    for (int i = 0; i < d1.count; ++i) {
        if (d2.findWordIndex(d1.cards[i].foreignWord) != -1) {
            result.addCard(d1.cards[i]);
        }
    }
    return result;
}

Dictionary operator-(const Dictionary& d1, const Dictionary& d2) {
    Dictionary result(d1.dictName + " - " + d2.dictName, d1.maxSize);

    for (int i = 0; i < d1.count; ++i) {
        if (d2.findWordIndex(d1.cards[i].foreignWord) == -1) {
            result.addCard(d1.cards[i]);
        }
    }
    return result;
}

bool operator==(const Dictionary& d1, const Dictionary& d2) {
    if (d1.count != d2.count) return false;
    for (int i = 0; i < d1.count; ++i) {
        int idx = d2.findWordIndex(d1.cards[i].foreignWord);
        if (idx == -1) return false;
        if (d1.cards[i].translation != d2.cards[idx].translation) return false;
    }
    return true;
}

bool operator!=(const Dictionary& d1, const Dictionary& d2) {
    return !(d1 == d2);
}

ostream& operator<<(ostream& out, const Dictionary& d) {
    out << string(d);
    return out;
}

istream& operator>>(istream& in, Dictionary& d) {
    cout << "Введіть назву словника: ";
    string name;
    in >> ws;
    getline(in, name);
    d.setDictName(name);

    cout << "Скільки слів бажаєте додати (макс. " << d.size() << ")? ";
    int n;
    in >> n;
    if (n < 0 || n > d.size()) {
        cerr << "Помилка: Некоректна кількість слів!" << endl;
        return in;
    }

    for (int i = 0; i < n; ++i) {
        cout << "Картка #" << (i + 1) << ":\n";
        WordCard wc;
        in >> wc;
        d.addCard(wc);
    }
    return in;
}