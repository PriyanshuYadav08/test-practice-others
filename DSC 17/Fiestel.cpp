#include <iostream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

// Simple round function: XOR with key
string roundFunction(const string& input, const string& key) {
    string result = input;
    for (size_t i = 0; i < input.size(); ++i) {
        result[i] = input[i] ^ key[i % key.size()];
    }
    return result;
}

// Feistel cipher encryption
string feistelEncrypt(const string& plaintext, const string& key, int rounds) {
    size_t blockSize = plaintext.size() / 2;
    string left = plaintext.substr(0, blockSize);
    string right = plaintext.substr(blockSize);

    for (int round = 0; round < rounds; ++round) {
        string temp = right;
        right = roundFunction(right, key);
        for (size_t i = 0; i < blockSize; ++i) {
            right[i] = left[i] ^ right[i];
        }
        left = temp;
    }
    return left + right;
}

// Feistel cipher decryption
string feistelDecrypt(const string& ciphertext, const string& key, int rounds) {
    size_t blockSize = ciphertext.size() / 2;
    string left = ciphertext.substr(0, blockSize);
    string right = ciphertext.substr(blockSize);

    for (int round = 0; round < rounds; ++round) {
        string temp = left;
        left = roundFunction(left, key);
        for (size_t i = 0; i < blockSize; ++i) {
            left[i] = right[i] ^ left[i];
        }
        right = temp;
    }
    return left + right;
}

int main() {
    string input = "HelloWorld";
    string key = "secret";
    int rounds = 4;

    if (input.size() % 2 != 0) {
        input += ' '; // Pad with space
    }

    cout << "Original input: " << input << endl;

    string encrypted = feistelEncrypt(input, key, rounds);
    cout << "Encrypted: " << encrypted << endl;

    // Decrypt
    string decrypted = feistelDecrypt(encrypted, key, rounds);
    cout << "Decrypted: " << decrypted << endl;

    // Verify
    if (decrypted == input) {
        cout << "Recovery successful!" << endl;
    } else {
        cout << "Recovery failed!" << endl;
    }

    return 0;
}