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

string method1(string s) {
    int n = s.size();
    array<int, 26> cnts{};

    for (int i = 0; i < n; i++) {
        cnts[s[i] - 'a']++;
    }

    bool all_front = false;
    string front, back;

    for (int i = 0; i < 26; i++) {
        if (all_front) {
            for (int j = 0; j < cnts[i]; j++) {
                front += 'a' + i;
            }
        } else {
            for (int j = 0; j < cnts[i] / 2; j++) {
                front += 'a' + i;
                back += 'a' + i;
            }

            if (cnts[i] % 2 == 1) {
                back += 'a' + i;
                all_front = true;
            }
        }
    }

    reverse(back.begin(), back.end());
    front += back;

    string rev = front;
    reverse(rev.begin(), rev.end());
    return max(front, rev);
}

string method2(string s) {
    int n = s.size();
    array<int, 26> cnts{};

    for (int i = 0; i < n; i++) {
        cnts[s[i] - 'a']++;
    }

    char lonely = 0;
    string front, back;

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < cnts[i] / 2; j++) {
            front += 'a' + i;
            back += 'a' + i;
        }

        if (cnts[i] % 2 == 1) {
            if (lonely) {
                front += 'a' + i;
                back += lonely;
                lonely = 0;
            } else {
                lonely = 'a' + i;
            }
        }
    }

    if (lonely) back += lonely;

    reverse(back.begin(), back.end());
    front += back;

    string rev = front;
    reverse(rev.begin(), rev.end());
    return max(front, rev);
}

void solve() {
    string s;
    cin >> s;

    cout << min(method1(s), method2(s)) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }

    return 0;
}
