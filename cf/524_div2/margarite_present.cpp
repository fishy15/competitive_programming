#include <iostream>

using namespace std;

int sum_until_n(int n) {
    if (n % 2 == 0) {
        return n / 2;
    } 

    return n / 2 - n;
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        //cout << "l: " << sum_until_n(r) << " " << sum_until_n(l - 1) << endl;;
        cout << sum_until_n(r) - sum_until_n(l - 1) << '\n';
    }

    return 0;
}
