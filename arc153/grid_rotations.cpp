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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void do_moves(int q, const vector<int> &moves, vector<int> &idx) {
    int n = idx.size();
    int cur_rotation = 0;

    for (int i = 0; i < q / 2; i++) {
        cur_rotation += moves[2 * i] + (n - moves[2 * i + 1]);
        while (cur_rotation >= n) cur_rotation -= n;
    }

    rotate(idx.begin(), idx.begin() + cur_rotation, idx.end());
    if (q % 2 == 1) {
        rotate(idx.begin(), idx.begin() + moves[q - 1], idx.end());
        reverse(idx.begin(), idx.end());
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int h, w;
    cin >> h >> w;

    vector<string> grid(h);
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    int q;
    cin >> q;

    vector<int> x_move(q), y_move(q);
    for (int i = 0; i < q; i++) {
        cin >> x_move[i] >> y_move[i];
    }

    vector<int> x_idx(h), y_idx(w);
    iota(x_idx.begin(), x_idx.end(), 0);
    iota(y_idx.begin(), y_idx.end(), 0);

    do_moves(q, x_move, x_idx);
    do_moves(q, y_move, y_idx);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << grid[x_idx[i]][y_idx[j]];
        }
        cout << '\n';
    }

    return 0;
}
