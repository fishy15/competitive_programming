// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakfin:
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
// :pray: :hyafinth:
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
#define MAXN 200000

using namespace std;

int n, q;
ll a[MAXN + 1];
ll t_min[4 * MAXN + 5];
ll t_sum[4 * MAXN + 5];
ll lazy[4 * MAXN + 5];

ll build_min(int v, int l, int r) {
    if (l == r) {
        return t_min[v] = a[l];
    }

    int mid = l + (r - l) / 2;
    ll min_l = build_min(2 * v, l, mid);
    ll min_r = build_min(2 * v + 1, mid + 1, r);

    return t_min[v] = min(min_l, min_r);
}

ll build_sum(int v, int l, int r) {
    if (l == r) {
        return t_sum[v] = a[l];
    }

    int mid = l + (r - l) / 2;
    ll sum_l = build_sum(2 * v, l, mid);
    ll sum_r = build_sum(2 * v + 1, mid + 1, r);

    return t_sum[v] = sum_l + sum_r;
}

void push(int v, int l, int r) {
    lazy[2 * v] += lazy[v];  
    lazy[2 * v + 1] += lazy[v];
    t_min[v] += lazy[v];
    t_sum[v] += lazy[v] * (r - l + 1);
    lazy[v] = 0;
}

void update(int v, int x, int y, int d, int l = 1, int r = n) {
    //printf("%d %d %d %d %d %d\n", v, x, y, d, l, r);
    if (x <= l && r <= y) {
        lazy[v] += d;
    } else if (l <= y && r >= x) {
        push(v, l, r);
        int mid = l + (r - l) / 2;
        update(2 * v, x, y, d, l, mid);
        update(2 * v + 1, x, y, d, mid + 1, r);
        t_sum[v] = t_sum[2 * v] + t_sum[2 * v + 1] + lazy[2 * v] * (mid - l + 1) + lazy[2 * v + 1] * (r - mid);
        t_min[v] = min(t_min[2 * v] + lazy[2 * v], t_min[2 * v + 1] + lazy[2 * v + 1]);
    }
}

ll query_min(int v, int x, int y, int l = 1, int r = n) {
    if (x <= l && r <= y) {
        return t_min[v] + lazy[v];
    }

    if (r < x || l > y) {
        return INF;
    }

    push(v, l, r);
    int mid = l + (r - l) / 2;
    ll left = query_min(2 * v, x, y, l, mid);
    ll right = query_min(2 * v + 1, x, y, mid + 1, r);
    return min(left, right);
}

ll query_sum(int v, int x, int y, int l = 1, int r = n) {
    if (x <= l && r <= y) {
        return t_sum[v] + lazy[v] * (r - l + 1);
    }

    if (r < x || l > y) {
        return 0;
    }

    push(v, l, r);
    int mid = l + (r - l) / 2;
    ll left = query_sum(2 * v, x, y, l, mid);
    ll right = query_sum(2 * v + 1, x, y, mid + 1, r);
    return left + right;
}

int main() {
    ifstream fin("haybales.in");
    ofstream fout("haybales.out");
    
    fin >> n >> q;
    for (int i = 1; i <= n; i++) {
        fin >> a[i];
    }

    build_min(1, 1, n);
    build_sum(1, 1, n);

    int count = 0;
    while (q--) {
        //printf("%d\n", count);
        count++;
        char code; fin >> code;
        if (code == 'M') {
            int l, r; fin >> l >> r;
            fout << query_min(1, l, r) << '\n';
        } else if (code == 'P') {
            int l, r, c; fin >> l >> r >> c;
            update(1, l, r, c);
        } else if (code == 'S') {
            int l, r; fin >> l >> r;
            fout << query_sum(1, l, r) << '\n';
        }
    }

    return 0;
}
