#include <iostream>
#include <arpa/inet.h>
using namespace std;

string str(unsigned x) {
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
    cout << "Number of subnets: ";
    cin >> n;

    unsigned net = ntohl(inet_addr(s.c_str())) & (~0u << (32 - p));

    int bits = 0;
    while ((1 << bits) < n) bits++;      // extra bits needed
    int np = p + bits;
    unsigned size = 1u << (32 - np);

    cout << "Subnet mask: " << str(~0u << (32 - np)) << "  (/" << np << ")\n";
    cout << "Hosts per subnet: " << size - 2 << endl;
    for (int i = 0; i < n; i++)
        cout << "Subnet " << i + 1 << ": " << str(net + i * size)
             << " - " << str(net + i * size + size - 1) << endl;
}
