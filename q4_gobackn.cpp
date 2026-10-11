#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int total, N;
    cout << "Total frames: ";
    cin >> total;
    cout << "Window size: ";
    cin >> N;

    int base = 0, next = 0;
    while (base < total) {
        // sender sends the whole window
        while (next < base + N && next < total) {
            cout << "Sent frame " << next << endl;
            next++;
        }
        // receiver accepts frames in order only
        for (int i = base; i < next; i++) {
            if (rand() % 100 < 25) {   // 25% chance of loss
                cout << "Frame " << i << " lost! Timeout -> Go back to " << i << endl;
                next = base = i;
                break;
            }
            cout << "ACK " << i << " received" << endl;
            base = i + 1;
        }
    }
    cout << "All frames sent successfully\n";
}
