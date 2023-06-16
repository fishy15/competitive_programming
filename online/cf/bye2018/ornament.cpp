#include <iostream>

using namespace std;

int a, b, c;

bool check(int mid) {
    return (a >= mid - 1) && (b >= mid) && (c >= mid + 1);
}
int main() {
    cin >> a >> b >> c;
    int max = 0;
    if (check(a + 1)) {
        max = 3 * a + 3 > max ? 3 * a + 3 : max;
    }

    if (check(b)) {
        max = 3 * b > max ? 3 * b : max;
    }

    if (check(c - 1)) {
        max = 3 * c - 3 > max ? 3 * c - 3 : max;
    }

    cout << max << "\n";
}
