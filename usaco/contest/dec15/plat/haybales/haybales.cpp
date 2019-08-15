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
#include <stdio.h>
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

int n, q;
int a[MAXN + 1];
int t_min[4 * MAXN + 4];
int t_sum[4 * MAXN + 4];
int lazy[4 * MAXN + 4];

int build_min(int v, int l, int r) {
    if (l == r) {
        return t_min[v] = a[l];
    }

    int mid = l + (r - l) / 2;
    int min_l = build_min(2 * v, l, mid);
    int min_r = build_min(2 * v + 1, mid + 1, r);

    return t_min[v] = min(min_l, min_r);
}

int build_sum(int v, int l, int r) {
    if (l == r) {
        return t_sum[v] = a[l];
    }

    int mid = l + (r - l) / 2;
    int sum_l = build_sum(2 * v, l, mid);
    int sum_r = build_sum(2 * v + 1, mid + 1, r);

    return t_sum[v] = sum_l + sum_r;
}

void push(int v) {
    cout << "PUSH " << lazy[v] << '\n';
    lazy[2 * v] += lazy[v];  
    lazy[2 * v + 1] += lazy[v];
    t_min[v] += lazy[v];
    t_sum[v] += lazy[v];
    lazy[v] = 0;
}

void update(int v, int x, int y, int d, int l = 1, int r = n) {
    if (x <= l && r <= y) {
        lazy[v] += d;
        t_min[v] += d;
        t_sum[v] += d;
    } else if (l <= y && r >= x) {
        push(v);
        int mid = l + (r - l) / 2;
        update(2 * v, x, y, d, l, mid);
        update(2 * v + 1, x, y, d, mid + 1, r);
        t_sum[v] = t_min[2 * v] + t_min[2 * v + 1];
        t_min[v] = min(t_min[2 * v], t_min[2 * v + 1]);
    }
}

int query_min(int v, int x, int y, int l = 1, int r = n) {
    if (x <= l && r <= y) {
        return t_min[v] + lazy[v];
    }

    if (r < x || l > y) {
        return INF;
    }

    push(v);
    int mid = l + (r - l) / 2;
    int left = query_min(2 * v, x, y, l, mid);
    int right = query_min(2 * v + 1, x, y, mid + 1, r);
    return min(left, right);
}

int query_sum(int v, int x, int y, int l = 1, int r = n) {
    if (x <= l && r <= y) {
        cout << t_sum[v] << ' ' << lazy[v] << '\n';
        return t_sum[v] + lazy[v] * (r - l + 1);
    }

    if (r < x || l > y) {
        return 0;
    }

    push(v);
    int mid = l + (r - l) / 2;
    int left = query_sum(2 * v, x, y, l, mid);
    int right = query_sum(2 * v + 1, x, y, mid + 1, r);
    return left + right;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build_min(1, 1, n);
    build_sum(1, 1, n);

    while (q--) {
        char code; cin >> code;
        if (code == 'M') {
            int l, r; cin >> l >> r;
            cout << query_min(1, l, r) << '\n';
        } else if (code == 'P') {
            int l, r, c; cin >> l >> r >> c;
            update(1, l, r, c);
            for (int i = 0; i <= 16; i++) {
                cout << t_sum[i] << '\n';
            }
        } else if (code == 'S') {
            int l, r; cin >> l >> r;
            cout << query_sum(1, l, r) << '\n';
        }
    }

    return 0;
}
