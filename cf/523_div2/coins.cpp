#include <iostream>

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n, k; cin >> n >> k;

    if (k % n == 0) {
        cout << k / n << '\n';
    } else {
        cout << k / n + 1 << '\n';
    }

    return 0;
}
