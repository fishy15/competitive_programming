/*
 * Note that the last character will be added to the sum and the second to last character will be subtracted.
 * This rest can be either added or subtracted arbitrarily, which can be proven by induction. Adjusting for
 * the last two characters, we can then set all the other characters to be subtracted and then greedily pick
 * numbers to be flipped to added until we reach T.
 */
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
ll t;
string s;
int cnt[26];

ll p2(char c) {
    return 1LL << (c - 'a');
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> t;
    cin >> s;
    t -= p2(s[n - 1]);
    t += p2(s[n - 2]);

    ll sum = 0;
    for (int i = 0; i < n - 2; i++) {
        cnt[s[i] - 'a']++;
        sum -= p2(s[i]);
    }

    for (int i = 25; i >= 0; i--) {
        while (cnt[i] > 0 && (sum + (1LL << (i + 1))) <= t) {
            sum += 1LL << (i + 1);
            cnt[i]--;
        }
    }

    cout << (sum == t ? "Yes" : "No") << '\n';

    return 0;
}
