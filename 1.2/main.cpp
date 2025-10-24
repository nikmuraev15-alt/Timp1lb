#include <iostream>
#include <string>
#include <locale>
#include "RouteCipher.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    wcout << L"Шифр Маршрутной Перестановки" << endl;
    wcout << L"Удаляются: пробелы, знаки препинания, цифры" << endl;
    
    try {
        int key;
        wcout << L"\nВведите ключ (столбцы): ";
        wcin >> key;
        wcin.ignore();
        
        RouteCipher cipher(key);
        wcout << L"Ключ установлен: " << key << endl;
        
        int choice;
        wstring text;
        
        while (true) {
            wcout << L"\n1. Зашифровать\n2. Расшифровать\n3. Выйти\nВыберите: ";
            wcin >> choice;
            wcin.ignore();
            
            if (choice == 3) break;
            
            if (choice == 1 || choice == 2) {
                wcout << L"Введите текст: ";
                getline(wcin, text);
                
                try {
                    wstring result = (choice == 1) ? cipher.encrypt(text) : cipher.decrypt(text);
                    wcout << L"Результат: " << result << endl;
                } catch (const CipherError& e) {
                    wcout << L"Ошибка: " << e.what() << endl;
                }
            } else {
                wcout << L"Неверный выбор" << endl;
            }
        }
        
    } catch (const CipherError& e) {
        wcout << L"Ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
