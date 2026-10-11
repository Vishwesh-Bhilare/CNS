#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) { cout << "Usage: ./tcp_client <server_ip>\n"; return 1; }

    int s = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, argv[1], &addr.sin_addr);

    if (connect(s, (sockaddr*)&addr, sizeof(addr)) < 0) { cout << "Connect failed\n"; return 1; }

    const char* msg = "Hello from client";
    send(s, msg, strlen(msg), 0);

    char buf[1024] = {0};
    recv(s, buf, sizeof(buf) - 1, 0);
    cout << "Server says: " << buf << endl;

    close(s);
}
