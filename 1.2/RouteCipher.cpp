#include "RouteCipher.h"
#include <algorithm>
#include <cctype>
#include <locale>

RouteCipher::RouteCipher(int key) {
    if (key <= 0) throw CipherError("Ключ должен быть положительным");
    if (key > 50) throw CipherError("Слишком большой ключ");
    columns = key;
}

std::wstring RouteCipher::cleanText(const std::wstring& text) {
    if (text.empty()) throw CipherError("Текст не может быть пустым");
    
    std::wstring result;
    std::locale loc("ru_RU.UTF-8");
    
    for (wchar_t c : text) {
        if (!std::iswspace(c) && !std::iswpunct(c) && !std::iswdigit(c)) {
            result += std::toupper(c, loc);
        }
    }
    
    if (result.empty()) throw CipherError("После очистки текст пуст");
    return result;
}

std::wstring RouteCipher::Encrypt(const std::wstring& text) {
    std::wstring clean = cleanText(text);
    int length = clean.length();
    int rows = (length + columns - 1) / columns;
    
    // Заполняем таблицу по строкам
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(columns, L'X'));
    for (int i = 0; i < length; i++) {
        table[i / columns][i % columns] = clean[i];
    }
    
    // Читаем по столбцам справа налево
    std::wstring result;
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            result += table[i][j];
        }
    }
    
    return result;
}

std::wstring RouteCipher::Decrypt(const std::wstring& text) {
    std::wstring clean = cleanText(text);
    int length = clean.length();
    int rows = (length + columns - 1) / columns;
    
    // Заполняем таблицу по столбцам справа налево
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(columns, L'X'));
    int index = 0;
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (index < length) table[i][j] = clean[index++];
        }
    }
    
    // Читаем по строкам
    std::wstring result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result += table[i][j];
        }
    }
    
    // Убираем лишние X в конце
    while (!result.empty() && result.back() == L'X') {
        result.pop_back();
    }
    
    return result;
}
