/*
 * We note that the contribution by crossing the x and y axes can be counted independently, so we will focus
 * on one of them. We can increment 1 at the lower end of a segment and subtract 1 at the upper end, and 
 * we can query the prefix until 0 to get the number of intersections. To deal with changing queries, we can
 * have a segtree representing the vectors to the left of the cursor and a segtree for the rest. As we move
 * the cursor, we can shift vectors between the left and right part. Now, a change in the middle doesn't 
 * mean we have to change all the elements after since the changes only happen at the ends of left and right.
 * We can then query the appropriate 0 locations (might be shifted for the right part) for each query.
 */

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

int n, m;
array<int, 2> v[MAXN];

struct node {
    int v;
    int l, r;
    node *c[2];
    node(int l, int r) : v(0), l(l), r(r) {
        c[0] = c[1] = nullptr;
    }
    void upd(int x, int v) {
        this->v += v;
        if (l != r) {
            int m = l + (r - l) / 2;
            if (x <= m) {
                if (!c[0]) c[0] = new node(l, m);
                c[0]->upd(x, v);
            } else {
                if (!c[1]) c[1] = new node(m + 1, r);
                c[1]->upd(x, v);
            }
        }
    }
    int qry(int x) {
        if (x >= r) return v;
        if (x < l) return 0;
        int res = 0;
        if (c[0]) res += c[0]->qry(x);
        if (c[1]) res += c[1]->qry(x);
        return res;
    }
};

int cur;
int x = 1;
int y = 1;
int back_x = 1;
int back_y = 1;
const int MX = 5e7 + 10;
node *l_x = new node(-MX, MX);
node *l_y = new node(-MX, MX);
node *r_x = new node(-MX, MX);
node *r_y = new node(-MX, MX);

void upd_l(int d) {
    int nx = x + d * v[cur][0];
    int ny = y + d * v[cur][1];
    l_x->upd(min(nx, x), d);
    l_x->upd(max(nx, x), -d);
    l_y->upd(min(ny, y), d);
    l_y->upd(max(ny, y), -d);
    x = nx;
    y = ny;
}

void upd_r(int d) {
    int nx = back_x - d * v[cur][0];
    int ny = back_y - d * v[cur][1];
    r_x->upd(min(back_x, nx), d);
    r_x->upd(max(back_x, nx), -d);
    r_y->upd(min(back_y, ny), d);
    r_y->upd(max(back_y, ny), -d);
    back_x = nx;
    back_y = ny;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> v[i][0] >> v[i][1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int nx = back_x - v[i][0];
        int ny = back_y - v[i][1];
        r_x->upd(min(back_x, nx), 1);
        r_x->upd(max(back_x, nx), -1);
        r_y->upd(min(back_y, ny), 1);
        r_y->upd(max(back_y, ny), -1);
        back_x = nx;
        back_y = ny;
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        char c; cin >> c;
        if (c == 'B') {
            if (cur > 0) {
                cur--;
                upd_l(-1);
                upd_r(1);
            }
        } else if (c == 'F') {
            if (cur < n - 1) {
                upd_l(1);
                upd_r(-1);
                cur++;
            }
        } else if (c == 'C') {
            upd_r(-1);
            cin >> v[cur][0] >> v[cur][1];
            upd_r(1);
        } else if (c == 'Q') {
            int res = l_x->qry(0) + l_y->qry(0) + r_x->qry(back_x - x) + r_y->qry(back_y - y);
            cout << res << '\n';
        }
    }

    return 0;
}
