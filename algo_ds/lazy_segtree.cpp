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
#define MAXN 100000

using namespace std;

int n;
int a[MAXN];
int t[4 * MAXN + 1];
int lazy[4 * MAXN + 1];

int build(int v, int l, int r) {
    if (l == r) {
        return t[v] = a[l];
    }

    int min_l = build(2 * v, l, l + (r - l) / 2);
    int min_r = build(2 * v + 1, r - (r - 1) / 2, r);

    return t[v] = min(min_l, min_r);
}

void push(int v) {
    lazy[2 * v] += lazy[v];  
    lazy[2 * v + 1] += lazy[v];
    lazy[v] = 0;
}

void update(int v, int x, int y, int d, int l, int r) {
    if (x <= l && r <= y) {
        lazy[v] += d;
    } else {
        push(v);
        if (l <= n && n <= l + (r - l) / 2) {
            update(2 * v, x, y, d, l, l + (r - l) / 2);
        } else {
            update(2 * v + 1, x, y, d, r - (r - 1) / 2, r);
        }
    }
}

int query(int v, int x, int y, int l, int r) {
    if (l <= x && y <= r) {
        return t[v] + lazy[v];
    }

    if (r < x || l > y) {
        return INF;
    }

    push(v);
    int left = query(2 * v, x, y, l, l + (r - l) / 2);
    int right = query(2 * v + 1, x, y, r - (r - l) / 2, r);
    return min(left, right) + lazy[v];
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    return 0;
}
