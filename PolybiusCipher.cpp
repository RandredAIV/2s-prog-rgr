#include <iostream> // Для ввода/вывода
#include <fstream>  // Для работы с файлами
#include <stdexcept> // Для исключений
#include <codecvt>  // Для работы с кодировками (не используется в текущей версии)
#include <Windows.h> // Для SetConsoleCP/SetConsoleOutputCP
#include "PolybiusCipher.h" // Заголовочный файл с объявлениями функций

using namespace std; // Используем стандартное пространство имен

// Функция для чтения содержимого файла
string readPolybiusFile(const string& fileName) {
    // Открываем файл в бинарном режиме
    ifstream file(fileName, ios::binary);
    // Проверяем, открылся ли файл
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл " + fileName);
    }

    // Читаем все содержимое файла в строку
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close(); // Закрываем файл

    // Проверяем, не пуст ли файл
    if (content.empty()) {
        throw runtime_error("Файл " + fileName + " пуст");
    }

    return content; // Возвращаем содержимое файла
}

// Создание квадрата Полибия для английских заглавных букв
map<char, string> createPolybiusSquareEngUpper() {
    map<char, string> polybiusSquare;
    // Заполняем квадрат значениями (буква -> код)
    polybiusSquare['A'] = "11"; polybiusSquare['B'] = "12";
    polybiusSquare['C'] = "13"; polybiusSquare['D'] = "14";
    polybiusSquare['E'] = "15";
    // ... и так для всех букв алфавита
    return polybiusSquare;
}

// Аналогичные функции для других алфавитов и регистров...
// [Здесь должны быть аналогичные createPolybiusSquareEngLower(),
// createPolybiusSquareRusUpper(), createPolybiusSquareRusLower()]

// Создание обратного квадрата Полибия (код -> буква) для английских заглавных
map<string, char> createReversePolybiusSquareEngUpper() {
    map<string, char> reversePolybiusSquare;
    // Заполняем обратный квадрат (код -> буква)
    reversePolybiusSquare["11"] = 'A'; reversePolybiusSquare["12"] = 'B';
    reversePolybiusSquare["13"] = 'C'; reversePolybiusSquare["14"] = 'D';
    reversePolybiusSquare["15"] = 'E';
    // ... и так для всех кодов
    return reversePolybiusSquare;
}

// Аналогичные функции для других алфавитов и регистров...
// [Здесь должны быть аналогичные createReversePolybiusSquareEngLower(),
// createReversePolybiusSquareRusUpper(), createReversePolybiusSquareRusLower()]

// Функция шифрования текста
string encryptPolybius(const string& text, const map<char, string>& polybiusSquare) {
    string encryptedText; // Результат шифрования
    // Проходим по каждому символу исходного текста
    for (char c : text) {
        // Если символ есть в квадрате Полибия
        if (polybiusSquare.count(c) > 0) {
            // Добавляем соответствующий код
            encryptedText += polybiusSquare.at(c);
        } else {
            // Иначе оставляем символ как есть
            encryptedText += c;
        }
    }
    return encryptedText; // Возвращаем зашифрованный текст
}

// Функция дешифрования текста
string decryptPolybius(const string& text, const map<string, char>& reversePolybiusSquare) {
    string decryptedText; // Результат дешифрования
    string symbol; // Буфер для накопления цифр кода

    // Проходим по каждому символу зашифрованного текста
    for (char c : text) {
        // Если символ - цифра
        if (isdigit(c)) {
            symbol += c; // Добавляем цифру в буфер
            // Если накопили 2 цифры (полный код)
            if (symbol.length() == 2) {
                // Если код существует в квадрате
                if (reversePolybiusSquare.count(symbol) > 0) {
                    // Добавляем соответствующую букву
                    decryptedText += reversePolybiusSquare.at(symbol);
                } else {
                    // Иначе ставим знак вопроса (неизвестный код)
                    decryptedText += "?";
                }
                symbol.clear(); // Очищаем буфер
            }
        } else {
            // Если встретили не-цифру
            if (!symbol.empty()) {
                // Добавляем оставшиеся цифры как есть
                decryptedText += symbol;
                symbol.clear();
            }
            // Добавляем текущий символ как есть
            decryptedText += c;
        }
    }
    // Добавляем оставшиеся цифры, если они есть
    if (!symbol.empty()) {
        decryptedText += symbol;
    }
    return decryptedText; // Возвращаем расшифрованный текст
}

// Основная функция интерфейса для работы с шифром Полибия
void DisplayPolybius() {
    // Устанавливаем кодировку консоли для русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Основной цикл меню
    while (true) {
        try {
            // Вывод меню выбора языка
            cout << "---------------------------------\n";
            cout << "Выберите язык:\n1) English\n2) Русский\n3) Назад\n";
            cout << "---------------------------------\n";

            string languageChoice;
            getline(cin, languageChoice); // Чтение выбора пользователя

            // Проверка корректности ввода
            if (languageChoice != "1" && languageChoice != "2" && languageChoice != "3") {
                throw invalid_argument("Неправильная команда. Нужно ввести '1', '2' или '3'.\n");
            }

            int languageAction = stoi(languageChoice); // Преобразуем в число
            if (languageAction == 3) { // Если выбрано "Назад"
                break; // Выходим из цикла
            }

            // Меню выбора регистра букв
            cout << "---------------------------------\n";
            cout << "Выберите регистр:\n1) Заглавные буквы\n2) Строчные буквы\n3) Назад\n";
            cout << "---------------------------------\n";

            string caseChoice;
            getline(cin, caseChoice); // Чтение выбора пользователя

            // Проверка корректности ввода
            if (caseChoice != "1" && caseChoice != "2" && caseChoice != "3") {
                throw invalid_argument("Неправильная команда. Нужно ввести '1', '2' или '3'.\n");
            }

            int caseAction = stoi(caseChoice); // Преобразуем в число
            if (caseAction == 3) { // Если выбрано "Назад"
                continue; // Возвращаемся к выбору языка
            }

            // Запрос имени файла с текстом
            string fileName;
            cout << "Введите имя файла с текстом: ";
            getline(cin, fileName);

            string inputText; // Переменная для хранения текста из файла
            try {
                // Читаем содержимое файла
                inputText = readPolybiusFile(fileName);
            } catch (const exception& e) {
                // Обработка ошибок чтения файла
                cerr << "Ошибка: " << e.what() << endl;
                continue; // Возвращаемся в меню
            }

            // Выбираем нужные квадраты Полибия в зависимости от выбора пользователя
            map<char, string> polybiusSquare;
            map<string, char> reversePolybiusSquare;

            if (languageAction == 1) { // Английский
                if (caseAction == 1) { // Заглавные
                    polybiusSquare = createPolybiusSquareEngUpper();
                    reversePolybiusSquare = createReversePolybiusSquareEngUpper();
                } else { // Строчные
                    polybiusSquare = createPolybiusSquareEngLower();
                    reversePolybiusSquare = createReversePolybiusSquareEngLower();
                }
            } else { // Русский
                if (caseAction == 1) { // Заглавные
                    polybiusSquare = createPolybiusSquareRusUpper();
                    reversePolybiusSquare = createReversePolybiusSquareRusUpper();
                } else { // Строчные
                    polybiusSquare = createPolybiusSquareRusLower();
                    reversePolybiusSquare = createReversePolybiusSquareRusLower();
                }
            }

            // Шифруем текст
            string encryptedText = encryptPolybius(inputText, polybiusSquare);

            // Сохраняем зашифрованный текст в файл
            ofstream outputFile("encryptedPolybius.txt");
            if (!outputFile.is_open()) {
                throw runtime_error("Не удалось создать файл encryptedPolybius.txt\n");
            }
            outputFile << encryptedText;
            outputFile.close();

            // Выводим информацию пользователю
            cout << "Зашифрованный текст сохранен в файл encryptedPolybius.txt\n";
            cout << "Зашифрованный текст: " << encryptedText << "\n";
            cout << "---------------------------------\n";

            // Читаем зашифрованный текст обратно из файла (для демонстрации)
            ifstream inputFile("encryptedPolybius.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("Не удалось открыть файл encryptedPolybius.txt\n");
            }
            string readEncryptedText;
            getline(inputFile, readEncryptedText, '\0'); // Читаем до конца файла
            inputFile.close();

            // Дешифруем текст
            string decryptedText = decryptPolybius(readEncryptedText, reversePolybiusSquare);
            cout << "Расшифрованный текст: " << decryptedText << "\n";

            // Сохраняем расшифрованный текст в файл
            ofstream decryptFile("decryptedPolybius.txt");
            if (!decryptFile.is_open()) {
                throw runtime_error("Не удалось создать файл decryptedPolybius.txt\n");
            }
            decryptFile << decryptedText;
            decryptFile.close();

            // Выводим информацию пользователю
            cout << "Расшифрованный текст сохранен в файл decryptedPolybius.txt\n";
            cout << "---------------------------------\n";
        }
        catch (const exception& e) {
            // Обработка всех исключений
            cerr << "Ошибка: " << e.what();
        }
    }
}