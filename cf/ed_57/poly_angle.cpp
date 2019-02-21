#include <iostream>
#include <vector>

using namespace std;

int angles[180];

int main() {
    int t; cin >> t;

    for (int i = 1; i < 180; i++) {
        bool done = false;
        for (int j = 3; j <= 998244353 && !done; j++) {
            for (int k = 1; k < j - 1; k++) {
                int val = 180 * k;
                if (val % j == 0 && val / j == i) {
                    angles[i] = j;
                    done = true;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < t; i++) {
        int a; cin >> a;
        cout << angles[a] << '\n';
    }

}
