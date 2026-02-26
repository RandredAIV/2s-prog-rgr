#include "table.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <Windows.h>

using namespace std;

string readFileToString1(const string& fileName) {
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл");
    }

    string content((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
    file.close();

    if (content.empty()) {
        throw runtime_error("Файл пуст");
    }

    return content;
}

void fillTable(const string& message, vector<vector<char>>& table, int size, char fillChar) {
    int msgIndex = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (msgIndex < message.size()) {
                table[i][j] = message[msgIndex++];
            } else {
                table[i][j] = fillChar;
            }
        }
    }
}

vector<int> generateRandomKey(int size) {
    vector<int> key(size);
    iota(key.begin(), key.end(), 0);
    random_device rd;
    mt19937 g(rd());
    shuffle(key.begin(), key.end(), g);
    return key;
}

vector<int> generatereverseKey(const vector<int>& key) {
    vector<int> reverseKey(key.size());
    for (int i = 0; i < key.size(); ++i) {
        reverseKey[key[i]] = i;
    }
    return reverseKey;
}

string encrypt(const string& message, const vector<int>& colKey, const vector<int>& rowKey, char fillChar) {
    int size = colKey.size();
    vector<vector<char>> table(size, vector<char>(size));
    fillTable(message, table, size, fillChar);

    // Применяем перестановку столбцов
    vector<vector<char>> tempTable = table;
    for (int j = 0; j < size; ++j) {
        int newCol = colKey[j];
        for (int i = 0; i < size; ++i) {
            table[i][newCol] = tempTable[i][j];
        }
    }

    // Применяем перестановку строк
    tempTable = table;
    for (int i = 0; i < size; ++i) {
        int newRow = rowKey[i];
        table[newRow] = tempTable[i];
    }

    // Собираем зашифрованный текст
    string encrypted;
    for (const auto& row : table) {
        for (char c : row) {
            encrypted += c;
        }
    }
    return encrypted;
}

string decrypt(const string& message, const vector<int>& colKey, const vector<int>& rowKey, char fillChar) {
    int size = colKey.size();
    vector<vector<char>> table(size, vector<char>(size));

    // Заполняем таблицу из зашифрованного сообщения
    int index = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (index < message.size()) {
                table[i][j] = message[index++];
            } else {
                table[i][j] = fillChar;
            }
        }
    }

    // Обратная перестановка строк
    vector<vector<char>> tempTable = table;
    for (int i = 0; i < size; ++i) {
        table[rowKey[i]] = tempTable[i];
    }

    // Обратная перестановка столбцов
    tempTable = table;
    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {
            table[i][colKey[j]] = tempTable[i][j];
        }
    }

    // Собираем расшифрованный текст (игнорируем fillChar)
    string decrypted;
    for (const auto& row : table) {
        for (char c : row) {
            if (c != fillChar) {
                decrypted += c;
            }
        }
    }
    return decrypted;
}

void DisplayTable() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (true) {
        string fileName;
        cout << "Введите имя файла: ";
        getline(cin, fileName);

        string message;
        try {
            message = readFileToString1(fileName);
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            continue;
        }

        try {
            // Определяем размер таблицы
            int messageLength = message.size();
            int size = ceil(sqrt(messageLength));

            // Генерируем ключи
            vector<int> colKey = generateRandomKey(size);
            vector<int> rowKey = generateRandomKey(size);
            vector<int> reverseColKey = generatereverseKey(colKey);
            vector<int> reverseRowKey = generatereverseKey(rowKey);

            char fillChar = '#';

            // Шифрование
            string encrypted = encrypt(message, colKey, rowKey, fillChar);

            // Сохраняем зашифрованный текст
            ofstream encFile("encryptedTable.txt", ios::binary);
            if (!encFile) throw runtime_error("Ошибка создания encryptedTable.txt");
            encFile << encrypted;
            encFile.close();

            cout << "Зашифрованный текст сохранен в encryptedTable.txt\n";

            // Дешифровка
            ifstream decFile("encryptedTable.txt", ios::binary);
            if (!decFile) throw runtime_error("Ошибка чтения encryptedTable.txt");
            string encryptedContent((istreambuf_iterator<char>(decFile)),
                                  istreambuf_iterator<char>());
            decFile.close();

            string decrypted = decrypt(encryptedContent, reverseColKey, reverseRowKey, fillChar);

            // Сохраняем расшифрованный текст
            ofstream outFile("decryptedTable.txt", ios::binary);
            if (!outFile) throw runtime_error("Ошибка создания decryptedTable.txt");
            outFile << decrypted;
            outFile.close();

            cout << "Расшифрованный текст:\n" << decrypted << "\n";
            cout << "Сохранен в decryptedTable.txt\n";

            break;
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }
}