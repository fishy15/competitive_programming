#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        int c; cin >> c;
        vector<ll> custs(c, 0);
        for (int j = 0; j < c; j++) {
            int tot; cin >> tot;
            for (int k = 0; k < tot; k++) {
                ll val; cin >> val;
                custs[j] += val;
            }
        }

        sort(custs.begin(), custs.end());

        double time = 0.0;
        double total = 0.0;
        for (int j = 0; j < c; j++) {
            time += custs[j];
            total += time;
        }

        cout << total / c << '\n';
    }

    return 0;
}
