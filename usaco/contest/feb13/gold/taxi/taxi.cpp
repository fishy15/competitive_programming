// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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

int main() {
    ifstream fin("taxi.in");
    ofstream fout("taxi.out");

    int n, m; fin >> n >> m;
    vector<pair<int, int>> events;

    for (int i = 0; i < n; i++) {
        int s, t; fin >> s >> t;
        if (s > t) {
            swap(s, t);
        }
        events.push_back({s, 1});
        events.push_back({t, -1});
    }

    sort(events.begin(), events.end());
    ll prev = 0;
    ll ans = 0;
    ll cur = 0;

    for (int i = 0; i < 2 * n; i++) {
        int val = cur == 0 ? 1 : 2 * cur - 1;
        ans += val * (events[i].first - prev);
        prev = events[i].first;
        cur += events[i].second;
    }

    ans += m - prev;
    fout << ans << '\n';
    return 0;
}
