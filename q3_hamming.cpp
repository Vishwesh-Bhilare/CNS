#include <iostream>
using namespace std;

int main() {
    char ch;
    cout << "Enter a character: ";
    cin >> ch;

    int code[12] = {0};                  // positions 1..11
    int dataPos[7] = {3, 5, 6, 7, 9, 10, 11};

    // place 7 data bits
    for (int i = 0; i < 7; i++) code[dataPos[i]] = (ch >> (6 - i)) & 1;

    // parity bits at positions 1, 2, 4, 8
    for (int p = 1; p <= 8; p <<= 1) {
        int x = 0;
        for (int i = 1; i <= 11; i++) if (i & p) x ^= code[i];
        code[p] = x;
    }

    cout << "Hamming code: ";
    for (int i = 1; i <= 11; i++) cout << code[i];
    cout << endl;

    int err;
    cout << "Enter error position to flip (1-11, 0 for none): ";
    cin >> err;
    if (err >= 1 && err <= 11) code[err] ^= 1;

    cout << "Received code: ";
    for (int i = 1; i <= 11; i++) cout << code[i];
    cout << endl;

    // syndrome = position of error
    int syndrome = 0;
    for (int p = 1; p <= 8; p <<= 1) {
        int x = 0;
        for (int i = 1; i <= 11; i++) if (i & p) x ^= code[i];
        if (x) syndrome += p;
    }

    if (syndrome == 0) cout << "No error detected\n";
    else {
        cout << "Error at position " << syndrome << ", correcting...\n";
        code[syndrome] ^= 1;
    }

    int val = 0;
    for (int i = 0; i < 7; i++) val = (val << 1) | code[dataPos[i]];
    cout << "Decoded character: " << (char)val << endl;
}
