#include <iostream>

using namespace std;

int main() {
    int n, k; cin >> n >> k;
    int ans = 0;

    if (2*n % k == 0) {
        ans += 2*n / k;
    } else {
        ans += 2*n / k + 1;
    }

    if (5*n % k == 0) {
        ans += 5*n / k;
    } else {
        ans += 5*n / k + 1;
    }

    if (8*n % k == 0) {
        ans += 8*n / k;
    } else {
        ans += 8*n / k + 1;
    }

    cout << ans << '\n';
    return 0;
}
