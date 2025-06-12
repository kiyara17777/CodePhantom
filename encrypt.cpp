#include <iostream>
#include <fstream>
#include <string>
#include <ctime>     
#include <cstring>   
using namespace std;

void logActivity(const string& message) {
    ofstream log("logs.txt", ios::app);
    if (log.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        dt[strlen(dt) - 1] = '\0';  
        log << "[" << dt << "] " << message << endl;
        log.close();
    }
}

void xorEncrypt(const string& inputFile, const string& outputFile, const string& key) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    if (!in || !out) {
        cerr << "[Error] File could not be opened!" << endl;
        logActivity("❌ Failed to open file: " + inputFile);
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

    cout << "[Success] Encrypted successfully as: " << outputFile << endl;
    logActivity("[Encrypted] " + inputFile + " → " + outputFile + " using password: ****");
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
