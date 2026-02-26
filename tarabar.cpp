#include "tarabar.h"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

map<char, char> TarabarEng = {
    {'B', 'A'}, {'A', 'B'}, {'C', 'E'}, {'E', 'C'}, {'D', 'I'}, {'I', 'D'},
    {'F', 'O'}, {'O', 'F'}, {'G', 'U'}, {'U', 'G'}, {'H', 'Y'}, {'Y', 'H'},
    {'J', 'Z'}, {'Z', 'J'}, {'K', 'X'}, {'X', 'K'}, {'L', 'W'}, {'W', 'L'},
    {'M', 'V'}, {'V', 'M'}, {'N', 'T'}, {'T', 'N'}, {'P', 'S'}, {'S', 'P'},
    {'Q', 'R'}, {'R', 'Q'}, {' ', '#'}, {'\n', '\n'}, // Добавлена обработка перевода строки

    // Строчные английские
    {'b', 'a'}, {'a', 'b'}, {'c', 'e'}, {'e', 'c'}, {'d', 'i'}, {'i', 'd'},
    {'f', 'o'}, {'o', 'f'}, {'g', 'u'}, {'u', 'g'}, {'h', 'y'}, {'y', 'h'},
    {'j', 'z'}, {'z', 'j'}, {'k', 'x'}, {'x', 'k'}, {'l', 'w'}, {'w', 'l'},
    {'m', 'v'}, {'v', 'm'}, {'n', 't'}, {'t', 'n'}, {'p', 's'}, {'s', 'p'},
    {'q', 'r'}, {'r', 'q'},

    // Русские буквы
    {'Б', 'Щ'}, {'Щ', 'Б'}, {'В', 'Ш'}, {'Ш', 'В'}, {'Г', 'Ч'}, {'Ч', 'Г'},
    {'Д', 'Ц'}, {'Ц', 'Д'}, {'Ж', 'Х'}, {'Х', 'Ж'}, {'З', 'Ф'}, {'Ф', 'З'},
    {'К', 'Т'}, {'Т', 'К'}, {'Л', 'С'}, {'С', 'Л'}, {'М', 'Р'}, {'Р', 'М'},
    {'Н', 'П'}, {'П', 'Н'}, {'б', 'щ'}, {'щ', 'б'}, {'в', 'ш'}, {'ш', 'в'},
    {'г', 'ч'}, {'ч', 'г'}, {'д', 'ц'}, {'ц', 'д'}, {'ж', 'х'}, {'х', 'ж'},
    {'з', 'ф'}, {'ф', 'з'}, {'к', 'т'}, {'т', 'к'}, {'л', 'с'}, {'с', 'л'},
    {'м', 'р'}, {'р', 'м'}, {'н', 'п'}, {'п', 'н'}, {' ', '#'}, {'\n', '\n'}
};

string readFileToString2(const string& fileName) {
    ifstream file(fileName, ios::binary); // Открываем в бинарном режиме
    if (!file.is_open()) {
        throw runtime_error("Файл не найден");
    }

    string content;
    char ch;
    while (file.get(ch)) { // Читаем посимвольно, включая \n
        content += ch;
    }

    if (content.empty()) {
        throw runtime_error("Файл пуст");
    }

    return content;
}

string encryptTarabar(const string& text, map<char, char>& Gramota) {
    string encrypted;
    for (char c : text) {
        if (Gramota.count(c)) {
            encrypted += Gramota[c];
        } else {
            encrypted += c; // Сохраняем символы, не найденные в словаре
        }
    }
    return encrypted;
}

string decryptTarabar(const string& text, map<char, char>& Gramota) {
    string decrypted;
    for (char c : text) {
        bool found = false;
        for (auto& pair : Gramota) {
            if (pair.second == c) {
                decrypted += pair.first;
                found = true;
                break;
            }
        }
        if (!found) decrypted += c; // Сохраняем неизвестные символы
    }
    return decrypted;
}

void DisplayGramota() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (true) {
        string fileName;
        cout << "Введите имя файла: ";
        getline(cin, fileName);

        string inputText;
        try {
            inputText = readFileToString2(fileName);
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            continue;
        }

        try {
            // Шифрование
            string encrypted = encryptTarabar(inputText, TarabarEng);

            ofstream encFile("encryptedTarabar.txt", ios::binary);
            if (!encFile) throw runtime_error("Ошибка создания encryptedTarabar.txt");
            encFile << encrypted;
            encFile.close();

            cout << "Зашифрованный текст:\n" << encrypted << "\n";
            cout << "Сохранен в encryptedTarabar.txt\n";

            // Дешифровка
            ifstream decFile("encryptedTarabar.txt", ios::binary);
            if (!decFile) throw runtime_error("Ошибка чтения encryptedTarabar.txt");
            string encryptedContent((istreambuf_iterator<char>(decFile)),
                                  istreambuf_iterator<char>());
            decFile.close();

            string decrypted = decryptTarabar(encryptedContent, TarabarEng);

            ofstream outFile("decryptedTarabar.txt", ios::binary);
            if (!outFile) throw runtime_error("Ошибка создания decryptedTarabar.txt");
            outFile << decrypted;
            outFile.close();

            cout << "Расшифрованный текст:\n" << decrypted << "\n";
            cout << "Сохранен в decryptedTarabar.txt\n";

            break;
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }
}