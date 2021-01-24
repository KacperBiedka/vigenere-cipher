#include <iostream>
#include <string>
using namespace std;

extern string lowercaseAp;
extern string uppercaseAp;

int getPos (char sign) {
    for (int i = 0; i < lowercaseAp.size(); i++) {
        if (uppercaseAp[i] == sign || lowercaseAp[i] == sign) {
            return i;
        }
    }
}

void encrypt (string text, string keyword) {
    string encryptedValue;
    for (int i = 0; i < text.size(); i++) {
        int repeatBlock = i % keyword.size();
        int xOffset = getPos(text[i]);
        int yOffset = getPos(keyword[repeatBlock]);
        encryptedValue += lowercaseAp[(xOffset + yOffset) % lowercaseAp.size()];
    }
    cout << "Zaszyfrowany wynik - " << encryptedValue << endl;
}

void decrypt (string text, string keyword) {
    string decryptedValue;
    for (int i = 0; i < text.size(); i++) {
        int repeatBlock = i % keyword.size();
        int xOffset = getPos(text[i]);
        int yOffset = getPos(keyword[repeatBlock]);
        int index = xOffset > yOffset ? xOffset - yOffset : lowercaseAp.size() - (yOffset - xOffset);
        decryptedValue += lowercaseAp[index];
    }
    cout << "Odszyfrowany wynik - " << decryptedValue << endl;
}

void program () {
    string keyword;
    string inputPath;
    cout << "Podaj slowo do enkryptowania: " << endl;
    cin >> inputPath;
    cout << "Podaj slowo kluczowe: " << endl;
    if (!(cin >> keyword))
        cout << "Error :(";
    encrypt(inputPath, keyword);
    decrypt("mikm", "test");

}

void rerun (void method()) {
    cout << "czy chcesz ponowic operacje? (T/N)" << endl;
    char answer;
    cin >> answer;
    if (answer == 'T') {
        method();
        rerun(program);
    } else if (answer == 'N') {
        return;
    } else {
        rerun(program);
    }
}

int main() {
    cout << "Szyfrowanie plikow algorytmem Vigenere\'a" << endl;
    cout << "Autor - Kacper Biedka" << endl;
    program();
    rerun(program);
}
