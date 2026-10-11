#include <iostream>
#include <bitset>
using namespace std;

// mod-2 division: XOR the generator wherever a 1 is found
string divide(string data, string gen) {
    int n = gen.size();
    for (int i = 0; i + n <= (int)data.size(); i++)
        if (data[i] == '1')
            for (int j = 0; j < n; j++)
                data[i + j] = (data[i + j] == gen[j]) ? '0' : '1';
    return data.substr(data.size() - (n - 1));   // remainder
}

int main() {
    char ch;
    cout << "Enter a character: ";
    cin >> ch;

    string data = bitset<8>(ch).to_string();
    string gen = "1101";

    // sender: append zeros, divide, append remainder
    string rem = divide(data + string(gen.size() - 1, '0'), gen);
    string sent = data + rem;
    cout << "Data: " << data << "\nCRC : " << rem << "\nSent: " << sent << endl;

    // simulate error
    int pos;
    cout << "Flip which bit? (0-" << sent.size() - 1 << ", -1 for none): ";
    cin >> pos;
    string recv = sent;
    if (pos >= 0 && pos < (int)recv.size()) recv[pos] = (recv[pos] == '0') ? '1' : '0';
    cout << "Received: " << recv << endl;

    // receiver: remainder must be all zeros
    string check = divide(recv, gen);
    if (check.find('1') == string::npos) cout << "No error\n";
    else cout << "Error detected!\n";
}
