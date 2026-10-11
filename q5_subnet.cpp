#include <iostream>
#include <arpa/inet.h>
using namespace std;

string str(unsigned x) {                         // number -> "a.b.c.d"
    in_addr a;
    a.s_addr = htonl(x);
    return inet_ntoa(a);
}

int main() {
    string s;
    int p, n;
    cout << "Network IP: ";
    cin >> s;
    cout << "Prefix (e.g. 24): ";
    cin >> p;

    unsigned ip = ntohl(inet_addr(s.c_str()));   // "a.b.c.d" -> number
    unsigned mask = ~0u << (32 - p);
    unsigned net = ip & mask;
    unsigned bc = net | ~mask;

    cout << "Mask     : " << str(mask) << endl;
    cout << "Network  : " << str(net) << endl;
    cout << "Broadcast: " << str(bc) << endl;
    cout << "Hosts    : " << bc - net - 1 << endl;

    cout << "\nNumber of subnets: ";
    cin >> n;
    int bits = 0;
    while ((1 << bits) < n) bits++;              // bits needed for n subnets
    int np = p + bits;
    unsigned size = 1u << (32 - np);

    cout << "New prefix /" << np << "  mask " << str(~0u << (32 - np)) << endl;
    for (int i = 0; i < n; i++) {
        unsigned st = net + i * size;
        cout << "Subnet " << i + 1 << ": " << str(st) << "  -  " << str(st + size - 1) << endl;
    }
}
