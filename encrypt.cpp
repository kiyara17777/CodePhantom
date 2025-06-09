#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void xorEncrypt(const string& inputFile, const string& outputFile, const string& key) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    if (!in || !out) {
        cerr << "File error!" << endl;
        return;
    }

    char ch;
    int keyIndex = 0;
    while (in.get(ch)) {
        ch ^= key[keyIndex]; 
        out.put(ch);
        keyIndex = (keyIndex + 1) % key.length(); 
    }

    in.close();
    out.close();
    cout << "Encrypted successfully!" << endl;
}

int main() {
    string inputFile, outputFile, key, disguiseExt;
    cout << "Enter file to encrypt: ";
    cin >> inputFile;
    cout << "Enter password: ";
    cin >> key;
    cout << "Enter disguise extension (e.g., .jpg or .mp3): ";
    cin >> disguiseExt;

    outputFile = "encrypted" + disguiseExt;
    xorEncrypt(inputFile, outputFile, key);
    return 0;
}
