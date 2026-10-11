#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
using namespace std;

string toStr(unsigned int ip) {
    return to_string(ip >> 24) + "." + to_string((ip >> 16) & 255) + "." +
           to_string((ip >> 8) & 255) + "." + to_string(ip & 255);
}

int main() {
    string s;
    int prefix, n;
    unsigned int a, b, c, d;

    cout << "Enter network IP (e.g. 192.168.1.0): ";
    cin >> s;
    sscanf(s.c_str(), "%u.%u.%u.%u", &a, &b, &c, &d);
    cout << "Enter prefix length (e.g. 24): ";
    cin >> prefix;

    unsigned int ip = (a << 24) | (b << 16) | (c << 8) | d;
    unsigned int mask = 0xFFFFFFFFu << (32 - prefix);

    cout << "Subnet mask : " << toStr(mask) << endl;
    cout << "Network     : " << toStr(ip & mask) << endl;
    cout << "Broadcast   : " << toStr(ip | ~mask) << endl;
    cout << "Usable hosts: " << ((1u << (32 - prefix)) - 2) << endl;

    cout << "\nHow many subnets do you need? ";
    cin >> n;
    int bits = ceil(log2(n));
    int np = prefix + bits;
    if (np > 30) { cout << "Too many subnets\n"; return 1; }

    unsigned int nmask = 0xFFFFFFFFu << (32 - np);
    unsigned int size = 1u << (32 - np);
    cout << "New prefix /" << np << ", mask " << toStr(nmask)
         << ", hosts per subnet " << size - 2 << endl;

    unsigned int net = ip & mask;
    for (int i = 0; i < n; i++) {
        unsigned int st = net + i * size;
        cout << "Subnet " << i + 1 << ": " << toStr(st) << "/" << np
             << "  hosts " << toStr(st + 1) << " - " << toStr(st + size - 2)
             << "  broadcast " << toStr(st + size - 1) << endl;
    }
}
