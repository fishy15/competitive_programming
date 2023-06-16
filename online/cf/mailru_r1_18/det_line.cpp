#include <iostream>
#include <vector>
#define MAXS 100

using namespace std;

int stops[MAXS + 1];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int r; cin >> r;
        for (int i = 0; i < r; i++) {
            int x; cin >> x;
            stops[x]++;
        }
    }

    for (int i = 1; i <= 100; i++) {
        if (stops[i] == n) {
            cout << i << ' ';
        }
    }

    return 0;
}
