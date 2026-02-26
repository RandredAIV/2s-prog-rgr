#include <iostream>
#include <Windows.h>
#include "table.h"
#include "tarabar.h"
#include "password.h"
#include "PolybiusCipher.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool passwordEntered = false; //проверка на ввод пароля

    while (!passwordEntered) {
        string userPassword;
        cout << "[Меню]. Введите пароль для начала работы программы: ";
        getline(cin, userPassword);

        try {
            if (!checkPassword(userPassword)) {
                throw invalid_argument("Неверный пароль\n");
            }
            passwordEntered = true; // Пароль введен корректно
        }
        catch (const invalid_argument& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

    while (true) {
        try {
            string MenuChoice;
            cout << "----------------------------------------------------\n";
            cout << "[Меню]. Выберите Шифр:\n1. Двойная табличная перестановка\n2. Тарабарская грамота\n3. Шифр Полибия\n4. Выход\n";
            cout << "----------------------------------------------------\n";
            getline(cin, MenuChoice);

            if (MenuChoice != "1" && MenuChoice != "2" && MenuChoice != "3" && MenuChoice != "4") {
                throw invalid_argument("Необходимо ввести '1', '2', '3' или '4' без пробелов.\n");
            }
            int ChoiceMenu = stoi(MenuChoice);// преобразование строки в int
            switch (ChoiceMenu) {
                case 1:
                    DisplayTable();
                    break;
                case 2:
                    DisplayGramota();
                    break;
                case 3:
                    DisplayPolybius();
                    break;
                case 4:
                    cout << "----------------------------------------------------\n";
                    cout << "Работа программы завершена\n";
                    cout << "----------------------------------------------------\n";
                    return 0;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Ошибка: " << e.what() << endl;
            cout << "----------------------------------------------------\n";
        }
    }
}