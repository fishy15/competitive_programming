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
#define MAXN 500010

using namespace std;

int n;
ll d1[MAXN];
ll dn[MAXN];
vector<array<ll, 3>> ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i < n - 1; i++) {
        cin >> d1[i];
    }
    for (int i = 1; i < n - 1; i++) {
        cin >> dn[i];
    }

    if (n == 1) {
        cout << "TAK\n";
        return 0;
    } else if (n == 2) {
        cout << "TAK\n";
        cout << "1 2 1\n";
        return 0;
    }

    // case that 1 and n are directly connected
    bool works = true;
    for (int i = 1; i < n - 1; i++) {
        if (abs(d1[i] - dn[i]) != abs(d1[1] - dn[1])) {
            works = false;
            break;
        }
    }

    if (works) {
        ll d = abs(d1[1] - dn[1]);
        if (d) {
            cout << "TAK\n";
            cout << 1 << ' ' << n << ' ' << d << '\n';
            for (int i = 1; i < n - 1; i++) {
                if (d1[i] > dn[i]) {
                    cout << n << ' ' << i + 1 << ' ' << dn[i] << '\n'; 
                } else {
                    cout << 1 << ' ' << i + 1 << ' ' << d1[i] << '\n';
                }
            }
            return 0;
        }
    }

    ll min_dist = INFLL;
    for (int i = 1; i < n - 1; i++) {
        min_dist = min(min_dist, d1[i] + dn[i]);
    }
    
    if (!min_dist) {
        cout << "NIE\n";
        return 0;
    }

    vector<pair<int, ll>> pts = {{0, 0}, {n - 1, min_dist}};
    map<ll, int> loc = {{0, 0}, {min_dist, n - 1}};
    for (int i = 1; i < n - 1; i++) {
        if (d1[i] + dn[i] == min_dist) {
            pts.push_back({i, d1[i]});
            loc[d1[i]] = i;
        }
    }

    sort(pts.begin(), pts.end(), [](const pair<int, ll> &p1, const pair<int, ll> &p2) {
        return p1.second < p2.second;
    });

    for (int i = 0; i < pts.size() - 1; i++) {
        ll d = pts[i + 1].second - pts[i].second;
        if (d == 0) {
            cout << "NIE\n";
            return 0;
        }
        ans.push_back({pts[i].first, pts[i + 1].first, d});
    }

    d1[n - 1] = min_dist;
    for (int i = 1; i < n - 1; i++) {
        if (d1[i] + dn[i] > min_dist) {
            ll pos = d1[i] - dn[i] + min_dist;
            if (pos % 2 != 0) {
                cout << "NIE\n";
                return 0;
            }
            pos /= 2;
            if (!loc.count(pos)) {
                cout << "NIE\n";
                return 0;
            }
            ans.push_back({loc[pos], i, d1[i] - d1[loc[pos]]});
        }
    }

    cout << "TAK\n";
    for (auto arr : ans) {
        cout << arr[0] + 1 << ' ' << arr[1] + 1 << ' ' << arr[2] << '\n';
    }

    return 0;
}
