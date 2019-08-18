// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eed:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinx:
// :pray: :eyg:
// :pray: :evan:
// :pray: :cj:
// :pray: :steph:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :vmaddur:
// :pray: :dorijanko:
// :pray: :gaming:
// :pray: :kassuno:
// :pray: :hyacinth:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:
// :pray: :jony:
// :pray: :kage:
// :pray: :ghost:
// :pray: :aha:
// :pray: :coolguy:
// :pray: :imax:
// :pray: :howlet:
// :pray: :darren:
// :pray: :arie: 
// :pray: :blastman: 
// :pray: :zephyr: 
// :pray: :bigc:

#include <iostream>
#include <fstream>
#include <vector>
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
#define MAXN 200000

using namespace std;

int n;
vector<pair<int,int>> dolls;
pair<int, int> t[4 * MAXN + 4];

void update(int pos, int val, int cnt, int v = 1, int l = 1, int r = n) {
    if (r < pos || l > pos) {
        return;
    } else if (l == r) {
        t[v] = {val, cnt};
    } else {
        int mid = l + (r - l) / 2;
        update(pos, val, cnt, 2 * v, l, mid);
        update(pos, val, cnt, 2 * v + 1, mid + 1, r);
        t[v].first = min(t[2 * v].first, t[2 * v + 1].first);
        t[v].second = 0;
        if (t[2 * v].first == t[v].first) {
            t[v].second += t[2 * v].second;
        }

        if (t[2 * v + 1].first == t[v].first) {
            t[v].second += t[2 * v + 1].second;
        }

        t[v].second %= MOD;
    }
}

pair<int, int> query(int pos, int v = 1, int l = 1, int r = n) {
    //cout << '\t' << pos << ' ' << l << ' ' << r << '\n';
    if (dolls[r].first < dolls[pos].second) {
        return {INF, 0};
    }

    if (dolls[l].first >= dolls[pos].second) {
        return t[v];
    }

    int mid = l + (r - l) / 2;
    pair<int, int> left = query(pos, 2 * v, l, mid);
    pair<int, int> right = query(pos, 2 * v + 1, mid + 1, r);
    pair<int, int> ans;
    ans.first = min(left.first, right.first);
    ans.second = 0;

    if (left.first == ans.first) {
        ans.second += left.second;
    }

    if (right.first == ans.first) {
        ans.second += right.second;
    }

    ans.second %= MOD;
    return ans;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    dolls = {{0, 0}};
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        dolls.push_back({y, x}); // intentional
    }

    sort(dolls.begin(), dolls.end());

    for (int i = n; i >= 0; i--) {
        auto num = query(i);
        if (num.first == INF) {
            update(i, dolls[i].first, 1);
        } else {
            num.first -= dolls[i].second - dolls[i].first;
            update(i, num.first, num.second);
        }
    }

    pair<int, int> ans = query(0);
    cout << ans.second << '\n';

    /* for (int i = 0; i <= 16; i++) { */
    /*     cout << t[i].first << ' ' << t[i].second << '\n'; */
    /* } */

    return 0;
}
