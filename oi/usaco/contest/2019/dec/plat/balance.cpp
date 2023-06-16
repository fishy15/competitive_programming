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

int n;
vector<pair<ll, ll>> pts;

ll cross(pair<ll, ll> &v1, pair<ll, ll> &v2) {
    return v1.first * v2.second - v1.second * v2.first;
}

bool cw(pair<ll, ll> &a, pair<ll, ll> &b, pair<ll, ll> &c) {
    pair<ll, ll> v1 = {b.first - a.first, b.second - a.second};
    pair<ll, ll> v2 = {c.first - b.first, c.second - b.second};
    return cross(v1, v2) < 0;
}

int main() {
    ifstream fin("balance.in");
    ofstream fout("balance.out");

    fin >> n;
    pts.push_back({0, 0});
    for (int i = 1; i <= n; i++) {
        ll x; fin >> x;
        pts.push_back({i, x * 10000000});
    }

    pts.push_back({n + 1, 0});

    sort(pts.begin(), pts.end());

    vector<pair<ll, ll>> chull;

    for (int i = 0; i < n + 2; i++) {
        int sz = chull.size();
        while (sz > 1 && !cw(chull[sz - 2], chull[sz - 1], pts[i])) {
            chull.pop_back();
            sz = chull.size();
        }

        chull.push_back(pts[i]);
    }

    int pos = 0;

    for (int i = 1; i <= n; i++) {
        if (chull[pos + 1].first == i) {
            fout << (chull[pos + 1].second / 100) << '\n';
            pos++;
        } else {
            ll dist1 = i - chull[pos].first;
            ll dist2 = chull[pos + 1].first - i;
            double diff = chull[pos + 1].second - chull[pos].second;
            fout << (chull[pos].second + (ll)floor(diff * dist1 / (dist1 + dist2))) / 100 << '\n';
        }
    }

    return 0;
}
