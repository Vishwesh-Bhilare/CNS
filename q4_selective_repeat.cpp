#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int main() {
    srand(time(0));
    int total, N;
    cout << "Total frames: ";
    cin >> total;
    cout << "Window size: ";
    cin >> N;

    bool ok[1000] = {};                  // ok[i] = frame i acknowledged
    int base = 0;

    while (base < total) {
        for (int j = base; j < min(base + N, total); j++)
            if (!ok[j]) {
                cout << "Sent " << j;
                if (rand() % 4) { ok[j] = true; cout << " -> ACK\n"; }
                else cout << " -> lost, resend only this\n";
            }
        while (ok[base]) base++;         // slide window
    }
    cout << "Done\n";
}
