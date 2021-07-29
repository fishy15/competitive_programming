#include <iostream>

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    int sum = 0;
    for (int i = n - 1; i > 0; i--) {
        sum += i * (n - i);
    }

    cout << sum + n << '\n';
    return 0;
}
