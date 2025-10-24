#include <iostream>
#include <clocale>
#include "modAlphaCipher.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string key = "КЛЮЧ";
    string text = "ПРИВЕТ МИР";
    
    modAlphaCipher cipher(key);

    cout << "Шифр с поддержкой русского алфавита" << endl;
    cout << "Ключ: " << key << endl << endl;

    cout << "Исходный текст: " << text << endl;

    string encrypted = cipher.encrypt(text);
    cout << "Зашифровано: " << encrypted << endl;

    string decrypted = cipher.decrypt(encrypted);
    cout << "Расшифровано: " << decrypted << endl;

    // Упрощенная проверка
    if (decrypted.find("ПРИВЕТ") != string::npos) {
        cout << "Результат: Ok — шифрование работает!" << endl;
    } else {
        cout << "Результат: Fail — ошибка в шифровании." << endl;
    }

    return 0;
}
