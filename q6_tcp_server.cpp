#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);

    bind(s, (sockaddr*)&addr, sizeof(addr));
    listen(s, 1);
    cout << "Waiting for client...\n";

    int c = accept(s, nullptr, nullptr);
    char buf[1024] = {0};
    recv(c, buf, sizeof(buf) - 1, 0);
    cout << "Client says: " << buf << endl;

    const char* msg = "Hello from server";
    send(c, msg, strlen(msg), 0);

    close(c);
    close(s);
}
