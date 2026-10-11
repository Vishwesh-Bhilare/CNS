#include <iostream>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) { cout << "Usage: ./udp_sender <receiver_ip> <filename>\n"; return 1; }

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9090);
    inet_pton(AF_INET, argv[1], &addr.sin_addr);

    ifstream in(argv[2], ios::binary);
    if (!in) { cout << "File not found\n"; return 1; }

    char buf[1024];
    while (in.read(buf, sizeof(buf)) || in.gcount() > 0) {
        sendto(s, buf, in.gcount(), 0, (sockaddr*)&addr, sizeof(addr));
        usleep(1000);                 // small delay so receiver keeps up
    }
    sendto(s, buf, 0, 0, (sockaddr*)&addr, sizeof(addr));   // end marker
    cout << "File sent\n";
    close(s);
}
