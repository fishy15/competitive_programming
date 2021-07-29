#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    priority_queue<int> even;
    priority_queue<int> odd;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x % 2 == 0) {
            even.push(x);
        } else {
            odd.push(x);
        }
    }

    int escore = 0;
    int oscore = 0;
    for (int i = 0; i < n; i++) {
        if (even.empty()) even.push(0);
        if (odd.empty()) odd.push(0);

        if (i % 2 == 0) {
            if (even.top() > odd.top()) {
                escore += even.top();
                even.pop();
            } else {
                odd.pop();
            }
        } else {
            if (odd.top() > even.top()) {
                oscore += odd.top();
                odd.pop();
            } else {
                even.pop();
            }
        }
    }

    if (escore > oscore) {
        cout << "Alice\n";
    } else if (escore == oscore) {
        cout << "Tie\n";
    } else {
        cout << "Bob\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
