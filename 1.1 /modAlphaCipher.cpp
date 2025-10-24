#include "modAlphaCipher.h"
#include <stdexcept>

std::string modAlphaCipher::removeSpaces(const std::string& s) const
{
    std::string result;
    for (char c : s) {
        if (c != ' ') result += c;
    }
    return result;
}

std::vector<int> modAlphaCipher::textToIndices(const std::string& text) const
{
    std::vector<int> indices;
    
    for (size_t i = 0; i < text.size(); i += 2) {
        if (i + 1 >= text.size()) break;
        
        std::string letter = text.substr(i, 2);
        size_t pos = numAlpha.find(letter);
        
        if (pos == std::string::npos) {
            throw cipher_error("Invalid character");
        }
        
        indices.push_back(pos / 2);
    }
    
    if (indices.empty()) {
        throw cipher_error("Empty text");
    }
    
    return indices;
}

std::string modAlphaCipher::indicesToText(const std::vector<int>& indices) const
{
    std::string result;
    for (int idx : indices) {
        result += numAlpha.substr(idx * 2, 2);
    }
    return result;
}

modAlphaCipher::modAlphaCipher(const std::string& skey)
{
    key = textToIndices(removeSpaces(skey));
}

std::string modAlphaCipher::encrypt(const std::string& open_text)
{
    std::vector<int> work = textToIndices(removeSpaces(open_text));
    int alphaSize = numAlpha.size() / 2;
    
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaSize;
    }
    
    return indicesToText(work);
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text)
{
    std::vector<int> work = textToIndices(removeSpaces(cipher_text));
    int alphaSize = numAlpha.size() / 2;
    
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] - key[i % key.size()] + alphaSize) % alphaSize;
    }
    
    return indicesToText(work);
}
