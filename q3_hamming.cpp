#include <iostream>
using namespace std;

int main() {
    char ch;
    cout << "Enter a character: ";
    cin >> ch;

    // data bits go in non-power-of-2 positions (3,5,6,7,9,10,11)
    int c[12] = {0}, j = 6;
    for (int i = 1; i <= 11; i++)
        if (i & (i - 1)) c[i] = (ch >> j--) & 1;

    // XOR of positions of all 1-bits; parity bits are set to cancel it out
    int x = 0;
    for (int i = 1; i <= 11; i++) if (c[i]) x ^= i;
    for (int p = 1; p <= 8; p *= 2) c[p] = (x & p) != 0;

    cout << "Hamming code: ";
    for (int i = 1; i <= 11; i++) cout << c[i];

    int pos;
    cout << "\nFlip which position? (1-11, 0 for none): ";
    cin >> pos;
    if (pos) c[pos] ^= 1;

    // receiver: same XOR gives 0 if fine, else the error position
    int err = 0;
    for (int i = 1; i <= 11; i++) if (c[i]) err ^= i;

    if (err) { cout << "Error at position " << err << ", corrected\n"; c[err] ^= 1; }
    else cout << "No error\n";

    int v = 0;
    for (int i = 1; i <= 11; i++) if (i & (i - 1)) v = v * 2 + c[i];
    cout << "Decoded: " << (char)v << endl;
}
