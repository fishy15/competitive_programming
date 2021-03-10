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
ll ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> s;
    n = s.size();

    for (int i = n - 1; i >= 0; i--) {
        cnt[s[i] - 'a']++;
        if (i < n - 1) {
            if (s[i] == s[i + 1]) {
                int left = n - i;
                ans += left - cnt[s[i] - 'a'];
                memset(cnt, 0, sizeof cnt);
                cnt[s[i] - 'a'] = left;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
