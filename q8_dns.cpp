#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    string in;
    cout << "Enter URL or IP: ";
    cin >> in;

    in_addr a;
    if (inet_aton(in.c_str(), &a)) {             // input is an IP
        hostent* h = gethostbyaddr(&a, sizeof(a), AF_INET);
        if (h) cout << "URL: " << h->h_name << endl;
        else cout << "Not found\n";
    } else {                                     // input is a URL
        hostent* h = gethostbyname(in.c_str());
        if (h) cout << "IP: " << inet_ntoa(*(in_addr*)h->h_addr_list[0]) << endl;
        else cout << "Not found\n";
    }
}
