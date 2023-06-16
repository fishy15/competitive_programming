#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    int n; cin >> n;
    int min_x = 2000000000;
    int min_y = 2000000000;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        if (x < min_x) {
            min_x = x;
        }

        if (y < min_y) {
            min_y = y;
        }
    }

    int max_a = -2000000000;
    int max_b = -2000000000;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        if (a > max_a) {
            max_a = a;
        }

        if (b > max_b) {
            max_b = b;
        }
    }

    cout << (min_x + max_a) << ' ' << (min_y + max_b) << '\n';
}
