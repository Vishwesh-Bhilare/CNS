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

    int i = 0;                                   // first unacknowledged frame
    while (i < total) {
        int end = min(i + N, total);
        for (int j = i; j < end; j++) cout << "Sent " << j << endl;

        for (int j = i; j < end; j++) {
            if (rand() % 4 == 0) {               // 25% loss
                cout << "Frame " << j << " lost -> resend from " << j << endl;
                break;                           // go back: i stays at j
            }
            cout << "ACK " << j << endl;
            i++;
        }
    }
    cout << "Done\n";
}
