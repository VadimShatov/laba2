#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"
#include <locale>

using namespace std;

void check(const wstring& Text, const wstring& key, const bool destructCipherText = false) {
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text); // зашифровывание
        if (destructCipherText) // надо "портить"?
            cipherText.front() = towlower(cipherText.front()); // "портим"
        decryptedText = cipher.decrypt(cipherText); // расшифровывание
        cipherText = cipher.encrypt(Text);
        decryptedText = cipher.decrypt(cipherText);
        wcout << L"Ключ=" << key << endl;
        wcout << Text << endl;
        wcout << cipherText << endl;
        wcout << decryptedText << endl;
    }
    catch (const cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    }
}

int main(int argc, char** argv) {
    locale loc("ru_RU.UTF-8");
    locale::global(loc);

    check(L"БЫСТРАЯКОШКАНАПРУГЕСКАЧАЛА", L"Простой");
    check(L"БЫСТРАЯКОШКАНАПРУГЕСКАЧАЛА", L"");
    check(L"БЫСТРАЯКОШКАНАПРУГЕСКАЧАЛА", L"АБВГД123");
    check(L"Ленивая собака через скачет лиса", L"СУПЕР");
    check(L"123", L"АБВГ");
    check(L"БЫСТРАЯКОШКАНАПРУГЕСКАЧАЛА", L"СЕКРЕТНО", true);

    return 0;
}