#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern string lowercaseAp;
extern string uppercaseAp;

void showMenu () {
    cout << "Wybierz operacje:" << endl;
    cout << "1. Enkryptowanie" << endl;
    cout << "2. Dekryptowanie" << endl;
    cout << "Wybieram: ";
}

int getPos (char sign) {
    for (int i = 0; i < lowercaseAp.size(); i++) {
        if (uppercaseAp[i] == sign || lowercaseAp[i] == sign) {
            return i;
        }
    }
}

string transformLine (int operation, string text, string keyword) {
    string transformedValue;
    cout << "Input line - " << text << endl;
    for (int i = 0; i < text.size(); i++) {
        int repeatBlock = i % keyword.size();
        int xOffset = getPos(text[i]);
        int yOffset = getPos(keyword[repeatBlock]);
        if (text[i] == ' ') {
            transformedValue += ' ';
        } else {
            string alphabet;
            // determine if current sign is uppercase or lowercase
            if (text[i] >= 'A' && text[i] <= 'Z') {
                alphabet = uppercaseAp;
            } else {
                alphabet = lowercaseAp;
            }
            // Using a switch operator leaves more room for add additional commands
            switch(operation) {
                case 1:
                    transformedValue += alphabet[(xOffset + yOffset) % alphabet.size()];
                    break;
                case 2:
                    int index = xOffset >= yOffset ? xOffset - yOffset : alphabet.size() - (yOffset - xOffset);
                    transformedValue += alphabet[index];
                    break;
            }
        }
    }
    cout << "Converted line - " << transformedValue << endl;
    return transformedValue;
}

void transformFile (int operation, string keyword, string inputPath, string outputPath) {
    fstream inputHook(inputPath, ios::in | ios::out);
    fstream outputHook(outputPath, ios::in | ios::out);
    if (inputHook.good()) {
        string inputLine;
        string outputLine;
        while(!inputHook.eof()) {
            getline(inputHook, inputLine);
            string convertedLine = transformLine(operation, inputLine, keyword);
            convertedLine += '\n';
            outputHook.write(convertedLine.c_str(), sizeof(char)*convertedLine.size());
        }
    } else {
        cout << "Error :(" << endl;
    }
}

void program () {
    string keyword;
    string inputPath;
    string outputPath;
    string operation;
    int answer;
    while (answer > 2 || answer < 1) {
        showMenu();
        cin >> answer;
    }
    cout << "Podaj sciezke pliku wejscia: ";
    if (!(cin >> inputPath))
        cout << "Error :(";
    cout << "Podaj sciezke pliku wyjscia: ";
    if (!(cin >> outputPath))
        cout << "Error :(";
    cout << "Podaj slowo kluczowe: ";
    if (!(cin >> keyword))
        cout << "Error :(";
    transformFile(answer, keyword, inputPath, outputPath);
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
