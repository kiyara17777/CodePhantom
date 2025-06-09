#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void xorDecrypt(const string& inputFile, const string& outputFile, const string& key) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    if (!in || !out) {
        cerr << "File error! Could not open files." << endl;
        return;
    }

    char ch;
    int keyIndex = 0;
    while (in.get(ch)) {
        ch ^= key[keyIndex];  // XOR decryption
        out.put(ch);
        keyIndex = (keyIndex + 1) % key.length();
    }

    in.close();
    out.close();
    cout << "✅ File decrypted successfully!" << endl;
}

int main() {
    string inputFile, outputFile, key;

    cout << "Enter the encrypted file name (e.g., encrypted.jpg): ";
    cin >> inputFile;

    cout << "Enter the password used during encryption: ";
    cin >> key;

    cout << "Enter output file name (e.g., output.txt): ";
    cin >> outputFile;

    xorDecrypt(inputFile, outputFile, key);
    return 0;
}
