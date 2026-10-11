#include <iostream>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int ch;
    string in;
    cout << "1. URL -> IP\n2. IP -> URL\nChoice: ";
    cin >> ch;
    cout << "Enter: ";
    cin >> in;

    if (ch == 1) {
        addrinfo hints{}, *res;
        hints.ai_family = AF_INET;
        if (getaddrinfo(in.c_str(), nullptr, &hints, &res) != 0) { cout << "Lookup failed\n"; return 1; }
        for (addrinfo* p = res; p; p = p->ai_next) {
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &((sockaddr_in*)p->ai_addr)->sin_addr, ip, sizeof(ip));
            cout << "IP: " << ip << endl;
        }
        freeaddrinfo(res);
    } else {
        sockaddr_in sa{};
        sa.sin_family = AF_INET;
        inet_pton(AF_INET, in.c_str(), &sa.sin_addr);
        char host[NI_MAXHOST];
        if (getnameinfo((sockaddr*)&sa, sizeof(sa), host, sizeof(host), nullptr, 0, NI_NAMEREQD) != 0) {
            cout << "Lookup failed\n"; return 1;
        }
        cout << "URL: " << host << endl;
    }
}
