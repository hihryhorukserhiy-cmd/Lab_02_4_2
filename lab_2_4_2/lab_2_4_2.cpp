#include <iostream>
#include "Dictionary.h"
#include "Windows.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Розмір Dictionary: " << sizeof(Dictionary) << " байт" << endl;
    cout << "Розмір Dictionary з #pragma pack(1): " << sizeof(DictionaryPack1) << " байт\n" << endl;

    Dictionary dictDefault;

    WordCard initCards[3] = {
        WordCard("apple", "яблуко"),
        WordCard("book", "книга"),
        WordCard("computer", "комп'ютер")
    };
    Dictionary dict1("Англо-Український базовий", 10, initCards, 3);
    Dictionary dict2("Англо-Український технічний", 10);

    dict2.setDictName("Англо-Український ІТ");
    dict2.addCard("computer", "комп'ютер");
    dict2.addCard("network", "мережа");
    dict2.addCard("database", "база даних");

    cout << dict1 << endl;
    cout << dict2 << endl;

    cout << "--- Перевірка захисту від дублікатів ---" << endl;
    dict1.addCard("apple", "інше яблуко");
    cout << endl;

    cout << "Пошук слова 'book' через метод findWord(): " << dict1.findWord("book") << endl;
    cout << "Доступ через оператор [\"apple\"]: " << dict1["apple"] << endl;

    dict1["apple"].setTranslation("зелене яблуко");
    cout << "Після редагування через [\"apple\"]: " << dict1["apple"] << "\n" << endl;

    Dictionary dictUnion = dict1 + dict2;
    cout << "[Об'єднання (dict1 + dict2)]:\n" << dictUnion << endl;

    Dictionary dictIntersection = dict1 * dict2;
    cout << "[Перетин (dict1 * dict2)]:\n" << dictIntersection << endl;

    Dictionary dictDifference = dict1 - dict2;
    cout << "[Різниця (dict1 - dict2)]:\n" << dictDifference << endl;

    cout << "Максимальний розмір dict1 до ++: " << dict1.size() << endl;
    ++dict1;
    cout << "Максимальний розмір dict1 після ++: " << dict1.size() << endl;

    dict1.removeCard("book");
    cout << "dict1 після видалення слова 'book':\n" << dict1 << endl;

    Dictionary dictArray[2] = {
        Dictionary("Словник 1", 5),
        Dictionary("Словник 2", 5)
    };
    dictArray[0].addCard("sun", "сонце");
    dictArray[1].addCard("moon", "місяць");

    for (int i = 0; i < 2; ++i) {
        cout << dictArray[i];
    }

    cin >> dictDefault;
    cout << "\nВведений словник:\n" << dictDefault << endl;

    return 0;
}