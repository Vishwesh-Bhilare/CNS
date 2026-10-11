#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

int main() {
    ifstream file("samplee.csv");
    map<string, int> counts;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string col;
        int colIndex = 0;

        while (getline(ss, col, ',')) {
            // Column index 4 corresponds to Column E (Protocol)
            if (colIndex == 4 && col != "Protocol") {
                counts[col]++;
                break;
            }

            colIndex++;
        }
    }

    for (auto const& [protocol, count] : counts) {
        cout << protocol << ": " << count << "\n";
    }

    return 0;
}
