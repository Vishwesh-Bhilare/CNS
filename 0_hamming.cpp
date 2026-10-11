#include <iostream>
using namespace std;

int main() {
    // SENDER
    string d;
    cout << "Enter 4 data bits: ";
    cin >> d;

    int x[8];

    x[3] = d[0] - '0';
    x[5] = d[1] - '0';
    x[6] = d[2] - '0';
    x[7] = d[3] - '0';

    x[1] = x[3] ^ x[5] ^ x[7];
    x[2] = x[3] ^ x[6] ^ x[7];
    x[4] = x[5] ^ x[6] ^ x[7];

    cout << "Sender code: ";
    for (int i = 1; i <= 7; i++)
        cout << x[i];

    // RECEIVER
    string s;
    int h[8], p;

    cout << "\nEnter received code: ";
    cin >> s;

    for (int i = 1; i <= 7; i++)
        h[i] = s[i - 1] - '0';

    int p1 = h[1] ^ h[3] ^ h[5] ^ h[7];
    int p2 = h[2] ^ h[3] ^ h[6] ^ h[7];
    int p4 = h[4] ^ h[5] ^ h[6] ^ h[7];

    p = p1 + 2 * p2 + 4 * p4;

    if (p == 0) {
        cout << "No Error";
    } else {
        cout << "Error at position: " << p << endl;

        h[p] ^= 1;

        cout << "Corrected code: ";
        for (int i = 1; i <= 7; i++)
            cout << h[i];
    }

    return 0;
}
