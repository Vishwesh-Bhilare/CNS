#include <iostream>
#include <bitset>
using namespace std;

// mod-2 division by generator 1101 (13)
int rem(int x) {
    for (int i = 10; i >= 3; i--)
        if (x >> i & 1) x ^= 13 << (i - 3);
    return x;
}

int main() {
    char ch;
    cout << "Enter a character: ";
    cin >> ch;

    int data = ch << 3;                  // 8 data bits + 3 zeros
    int sent = data | rem(data);         // add remainder
    cout << "Sent: " << bitset<11>(sent) << endl;

    int pos;
    cout << "Flip which bit? (0-10, -1 for none): ";
    cin >> pos;
    if (pos >= 0) sent ^= 1 << pos;
    cout << "Received: " << bitset<11>(sent) << endl;

    cout << (rem(sent) == 0 ? "No error\n" : "Error detected!\n");
}
