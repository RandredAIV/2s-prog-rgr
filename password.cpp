#include "password.h"

bool checkPassword(const string& password) {
    string cypherpassword, result = ""; // Инициализация строк для хранения зашифрованного пароля и результата дешифрования
    int step; // Переменная для хранения шага сдвига при шифровании пароля
    ifstream in("password.txt"); // Открытие файла с зашифрованным паролем для чтения

    if (!in.is_open()) { // Проверка успешного открытия файла
        throw runtime_error("Не удалось открыть файл password.txt для чтения.\n"); // Генерация исключения в случае ошибки открытия файла
    }

    in >> cypherpassword >> step; // Считывание зашифрованного пароля и шага сдвига из файла
    in.close(); // Закрытие файла после считывания


    for (size_t i = 0; i < cypherpassword.size(); i++) { // Цикл по символам зашифрованного пароля
        if (cypherpassword[i] >= step && cypherpassword[i] <= 127) { // Проверка, что символ в диапазоне ASCII и требует расшифровки
            result += static_cast<char>((cypherpassword[i] - step) % 128); // Дешифровка символа и добавление к результату
        } else { // Если символ не требует дешифровки (не входит в диапазон ASCII)
            result += static_cast<char>(cypherpassword[i]); // Просто добавление символа к результату
        }
    }

    if(password == result){
        return true; // Сравнение введенного пароля с расшифрованным паролем и возвращение результата сравнения
    }
    else{
        return false;
    }

}