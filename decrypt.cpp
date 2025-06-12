#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstring>
using namespace std;

void logActivity(const string& message) {
    ofstream log("logs.txt", ios::app); 
    if (log) {
        time_t now = time(0);
        char* dt = ctime(&now);
        dt[strlen(dt) - 1] = '\0'; 
        log << "[" << dt << "] " << message << endl;
        log.close();
    }
}

void xorDecrypt(const string& inputFile, const string& outputFile, const string& key) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    if (!in || !out) {
        cerr << "[Error] Could not open files." << endl;
        logActivity("[Error] Failed to open " + inputFile + " or " + outputFile);
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

    cout << "[Success] File decrypted successfully as: " << outputFile << endl;
    logActivity("[Decrypted] " + inputFile + " → " + outputFile);
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
