#include <iostream>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9090);
    bind(s, (sockaddr*)&addr, sizeof(addr));

    ofstream out("received_file", ios::binary);
    char buf[1024];
    cout << "Waiting for file...\n";

    while (true) {
        int n = recvfrom(s, buf, sizeof(buf), 0, nullptr, nullptr);
        if (n <= 0) break;            // empty packet = end of file
        out.write(buf, n);
    }
    cout << "File saved as 'received_file'\n";
    out.close();
    close(s);
}
