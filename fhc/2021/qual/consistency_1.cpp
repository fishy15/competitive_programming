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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

char vowels[5] = {'A', 'E', 'I', 'O', 'U'};

bool is_vowel(int c) {
    return count(vowels, vowels + 5, c + 'A') > 0;
}

void solve() {
    string s; cin >> s;

    int dist[26][26];
    memset(dist, INF, sizeof dist);

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (is_vowel(i) == is_vowel(j)) {
                dist[i][j] = 2;
            } else {
                dist[i][j] = 1;
            }
        }
    }

    ll ans = INF;
    for (int i = 0; i < 26; i++) {
        ll cur = 0;
        for (char c : s) {
            cur += dist[c - 'A'][i];
        }

        ckmin(ans, cur);
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
