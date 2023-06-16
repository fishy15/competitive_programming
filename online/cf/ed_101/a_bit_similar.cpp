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
#include <functional>
#include <numeric>

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
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    string flipped;
    for (char c : s) {
        if (c == '0') {
            flipped += '1';
        } else
            flipped += '0';
    }

    int front = max(k - 25, 0);
    int back = k - front;

    int ones_in_front = 0;
    unsigned back_nums = 0;

    set<unsigned> lowest;

    auto process = [&]() {
        if (ones_in_front == 0) {
            lowest.insert(back_nums);
        }
    };

    // initialize both values
    for (int i = 0; i < front; i++) {
        if (flipped[i] == '1') {
            ones_in_front++;
        }
    }

    for (int i = front; i < k; i++) {
        back_nums <<= 1;
        back_nums += flipped[i] - '0';
    }

    process();

    for (int i = 1; i < n - k + 1; i++) {
        // substring from i to i + k - 1
        if (flipped[i - 1] == '1') {
            ones_in_front--;
        }

        if (flipped[i + front - 1] == '1') {
            ones_in_front++;
        }

        back_nums <<= 1;
        back_nums += flipped[i + k - 1] - '0';
        back_nums &= (1u << back) - 1;

        process();
    }

    // check if all full
    if (k < 25 && lowest.size() == (1u << k)) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    unsigned mex = 0;

    for (unsigned x : lowest) {
        if (x == mex) {
            mex++;
        } else {
            break;
        }
    }

    for (int i = 0; i < front; i++) {
        cout << '0';
    }

    for (int i = 0; i < back; i++) {
        if (mex & (1 << (back - i - 1))) {
            cout << '1';
        } else {
            cout << '0';
        }
    }

    cout << '\n';

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q;
    cin >> q;

    while (q--) {
        solve();
    }

    return 0;
}
