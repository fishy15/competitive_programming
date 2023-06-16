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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, k;
vector<pair<int, int>> r;
ll ans;

void calc(int pos) {
    vector<int> range(4 * n + 10);
    for (int i = 0; i < n; i++) {
        if (pos & (1 << i)) {
            for (int j = r[i].first; j < r[i].second; j++) {
                range[j]++;
            }
        }
    }

    ll q = 0;
    for (int i = 1; i <= 2 * n + 5; i++) {
        if (range[i] == 0 && range[i - 1] != 0) {
            q++;
        }
    }

    ll qq = 1;
    for (int i = 0; i < k; i++) {
        qq *= q;
        qq %= MOD;
    }

    // cout << q << ' ' << qq << '\n';

    ans += qq;
    ans %= MOD;
}

int main() {
    ifstream fin("help.in");
    ofstream fout("help.out");

    fin >> n >> k;

    for (int i = 0; i < n; i++) {
        int a, b; fin >> a >> b;
        r.push_back({a, b});
    }

    for (int i = 1; i < (1 << n); i++) {
        calc(i);
    }

    fout << ans << '\n';

    return 0;
}
