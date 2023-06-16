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

int n;
string s;
set<int> loc[26];
int nonzero = 0;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    cin >> s;

    for (int i = 0; i < n; i++) {
        loc[s[i] - 'a'].insert(i);
    }

    int l = 0;
    int r = n;

    while (r - l > 1) {
        loc[s[l] - 'a'].erase(l);

        while (nonzero < 26 && loc[nonzero].empty()) {
            nonzero++;
        }


        if (nonzero < s[l] - 'a') {
            int r2 = *loc[nonzero].rbegin();
            for (int i = r2; i < r; i++) {
                loc[s[i] - 'a'].erase(i);
            }

            swap(s[l], s[r2]);
            r = r2;
        }

        l++;
    }

    cout << s << '\n';

    return 0;
}
