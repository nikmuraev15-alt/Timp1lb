#ifndef MODALPHACIPHER_H
#define MODALPHACIPHER_H

#include <string>
#include <vector>
#include <stdexcept>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& msg) : std::invalid_argument(msg) {}
};

class modAlphaCipher
{
private:
    const std::string alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    std::vector<int> key;

    std::string removeSpaces(const std::string& s) const;
    std::vector<int> textToNumbers(const std::string& text) const;
    std::string numbersToText(const std::vector<int>& numbers) const;

public:
    modAlphaCipher(const std::string& key);
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);
};

#endif
