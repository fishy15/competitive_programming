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
#define MAXN 1000

using namespace std;

int x, y;
int rook[MAXN][MAXN];
array<int, 2> loc[MAXN];
multiset<int> row;
multiset<int> col;

bool ok(int i, int j) {
    return i >= 0 && j >= 0 && i < 999 && j < 999 && !rook[i][j];
}

int main() {
    cin >> x >> y;
    x--; y--;

    for (int i = 0; i < 666; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        rook[a][b] = true;
        row.insert(a);
        col.insert(b);
        loc[i] = {a, b};
    }

    while (x != 499 || y != 499) {
        int nx = x;
        int ny = y;
        if (x < 499) nx++;
        else if (x > 499) nx--;
        if (y < 499) ny++;
        else if (y > 499) ny--;

        int a, b, c;
        if (rook[nx][ny]) {
            cout << nx + 1 << ' ' << y + 1 << '\n';
            cin >> a >> b >> c;
            if (a > 0) {
                cout << "-1 -1 -1\n";
            }
            return 0;
        }
        
        cout << nx + 1 << ' ' << ny + 1 << endl;
        x = nx;
        y = ny;
        cin >> a >> b >> c;
        if (a <= 0) return 0;
        a--; b--; c--;
        auto [ro, co] = loc[a];
        row.erase(row.find(ro));
        col.erase(col.find(co));
        row.insert(b);
        col.insert(c);
        loc[a] = {b, c};
        rook[ro][co] = false;
        rook[b][c] = true;
    }

    int a = 0;
    int b = 0;
    int c = 0;

    int cnt[4] = {0, 0, 0, 0};
    int d = 0;
    for (int i = 0; i < 499; i++) {
        for (int j = 0; j < 499; j++) {
            cnt[0] += rook[i][j];
        }
    }
    for (int i = 0; i < 499; i++) {
        for (int j = 500; j < 999; j++) {
            cnt[1] += rook[i][j];
        }
    }
    for (int i = 500; i < 999; i++) {
        for (int j = 0; j < 499; j++) {
            cnt[2] += rook[i][j];
        }
    }
    for (int i = 500; i < 999; i++) {
        for (int j = 500; j < 999; j++) {
            cnt[3] += rook[i][j];
        }
    }
    d = min_element(cnt, cnt + 4) - cnt;
    while (true) {
        int nx = x;
        int ny = y;

        if (d < 2) nx++;
        else nx--;

        if (d % 2) ny--;
        else ny++;

        if (rook[nx][ny]) {
            cout << nx + 1 << ' ' << y + 1 << '\n';
            cin >> a >> b >> c;
            if (a > 0) {
                cout << "wtmoo";
            }
            return 0;
        }

        cout << nx + 1 << ' ' << ny + 1 << endl;
        x = nx;
        y = ny;
        cin >> a >> b >> c;
        if (a <= 0) return 0;
        a--; b--; c--;
        auto [ro, co] = loc[a];
        row.erase(row.find(ro));
        col.erase(col.find(co));
        row.insert(b);
        col.insert(c);
        loc[a] = {b, c};
        rook[ro][co] = false;
        rook[b][c] = true;
    }

    return 0;
}
