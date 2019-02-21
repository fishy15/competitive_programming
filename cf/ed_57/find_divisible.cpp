#include <iostream>

using namespace std;

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        int l, r; cin >> l >> r;
        if (2*l <= r) {
            cout << l << ' ' << 2*l << '\n';
        } 
    }

    return 0;
}
