#include <iostream>
#include <vector>
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

    vector<bool> acked(total, false);
    int base = 0;                                // first unacknowledged frame

    while (base < total) {
        int end = min(base + N, total);
        for (int j = base; j < end; j++) {
            if (acked[j]) continue;              // already received, skip
            cout << "Sent " << j << endl;
            if (rand() % 4 == 0)                 // 25% loss
                cout << "Frame " << j << " lost -> only this one is resent\n";
            else {
                acked[j] = true;
                cout << "ACK " << j << endl;
            }
        }
        while (base < total && acked[base]) base++;   // slide window
    }
    cout << "Done\n";
}
