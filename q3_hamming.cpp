#include <iostream>
#include <bitset>
using namespace std;

int main() {
    char ch;
    cout << "Enter a character: ";
    cin >> ch;
    string d = bitset<7>(ch).to_string();

    // positions 1..11; powers of 2 (1,2,4,8) are parity bits, rest are data
    int code[12] = {0};
    int j = 0;
    for (int i = 1; i <= 11; i++)
        if (i & (i - 1)) code[i] = d[j++] - '0';

    // parity bit p = XOR of all positions that have bit p set
    for (int p = 1; p <= 8; p *= 2)
        for (int i = 1; i <= 11; i++)
            if ((i & p) && i != p) code[p] ^= code[i];

    cout << "Hamming code: ";
    for (int i = 1; i <= 11; i++) cout << code[i];
    cout << endl;

    // simulate error
    int pos;
    cout << "Flip which position? (1-11, 0 for none): ";
    cin >> pos;
    if (pos >= 1 && pos <= 11) code[pos] ^= 1;

    cout << "Received    : ";
    for (int i = 1; i <= 11; i++) cout << code[i];
    cout << endl;

    // receiver: failed parity checks add up to the error position
    int err = 0;
    for (int p = 1; p <= 8; p *= 2) {
        int x = 0;
        for (int i = 1; i <= 11; i++)
            if (i & p) x ^= code[i];
        if (x) err += p;
    }

    if (err == 0) cout << "No error\n";
    else {
        cout << "Error at position " << err << ", corrected\n";
        code[err] ^= 1;
    }

    // extract data bits
    string out = "";
    for (int i = 1; i <= 11; i++)
        if (i & (i - 1)) out += to_string(code[i]);
    cout << "Decoded: " << (char)bitset<7>(out).to_ulong() << endl;
}
