#include <iostream>

using namespace std;

int main() {
    int n, k; cin >> n >> k;
    int div = 1;
    int mod = 0;

    while (true) {
        if (n % div == 0) {
            int mod = n / div;
            if (mod < k) {
                cout << (k * div + mod) << '\n';
                return 0;
            }
        }

        div++;
    }

    return 0;
}
