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

int n;
string s;
int cnt[26];
int cur[26];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        cnt[c - 'a']++;
    }

    cin >> s;
    for (char c : s) {
        cur[c - 'a']++;
    }

    int ans = 0;

    for (int i = 0; i < 26; i++) {
        ans += max(0, cur[i] - cnt[i]);
    }

    cout << ans << '\n';

    return 0;
}
