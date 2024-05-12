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

int randbit() {
    return rand() & 1;
}

int left() {
    cout << "? left" << endl;
    int x;
    cin >> x;
    return x;
}

int right() {
    cout << "? right" << endl;
    int x;
    cin >> x;
    return x;
}

int toggle() {
    cout << "? flip" << endl;
    int x;
    cin >> x;
    return x;
}

/*
int idx;
int n;
string s;
int cnt;

int left() {
    idx = (idx + n - 1) % n;
    cnt++;
    if (cnt >= 3 * n + 500) cout << "failed\n";
    return s[idx] - '0';
}

int right() {
    idx = (idx + 1) % n;
    cnt++;
    if (cnt >= 3 * n + 500) cout << "failed\n";
    return s[idx] - '0';
}

int toggle() {
    s[idx] = (s[idx] == '0') ? '1' : '0';
    cnt++;
    if (cnt >= 3 * n + 500) cout << "failed\n";
    return s[idx] - '0';
}
*/

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int cur;
    cin >> cur;

    // init
    /*
    cin >> s;
    n = s.size();
    cur = s[0] - '0';
    */

    vector<int> rand_str;
    vector<int> how_long_match(5001);

    while (true) {
        vector<int> found;
        for (int len = 3; len <= min(5000, (int) rand_str.size()); len++) {
            if (cur == rand_str.end()[-len]) {
                how_long_match[len]++;
                if (how_long_match[len] == 240) {
                    found.push_back(len);
                }
            } else {
                how_long_match[len] = 0;
            }
        }

        if (!found.empty()) {
            auto ans = *min_element(found.begin(), found.end());
            cout << "! " << ans << endl;
            return 0;
        }

        int bit = randbit();
        rand_str.push_back(bit);

        if (cur != bit) {
            toggle();
        }
        
        cur = right();
    }

    return 0;
}
