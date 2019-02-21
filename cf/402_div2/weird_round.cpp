#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    int n;
    cin >> s >> n;

    int count = 0;
    int notzero = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == '0') {
            count++;
            
            if (count == n) {
                break;
            }
        } else {
            notzero++;
        }
    }

    if (count < n) {
        cout << s.size() - 1 << '\n';
        return 0;
    }

    cout << notzero << '\n';
    return 0;
}
