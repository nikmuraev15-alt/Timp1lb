#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class CipherError : public std::invalid_argument {
public:
    explicit CipherError(const std::string& msg) : std::invalid_argument(msg) {}
};

class RouteCipher {
private:
    int columns;
    
public:
    RouteCipher(int key);
    
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& text);
    
    int getColumns() const { return columns; }
};
