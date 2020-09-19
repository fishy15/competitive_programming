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
#define MAXP 100000

using namespace std;

// rmq segtree
int arr[MAXP + 1];
int segtree[4 * MAXP + 10];

void update(int v, int l, int r, int n, int x) {
    if (l == r) {
        arr[l] = x;
        segtree[v] = x;
    } else {
        int mid = l + (r - l) / 2;
        if (n <= mid) {
            update(2 * v, l, mid, n, x);
        } else {
            update(2 * v + 1, mid + 1, r, n, x);
        }

        segtree[v] = max(segtree[2 * v], segtree[2 * v + 1]);
    }
}

int query(int v, int l, int r, int x, int y) {
    if (r < x || y < l) {
        return 0;
    }

    if (x <= l && r <= y) {
        return segtree[v];
    }

    int mid = l + (r - l) / 2;
    int q1 = query(2 * v, l, mid, x, y);
    int q2 = query(2 * v + 1, mid + 1, r, x, y);
    return max(q1, q2);
}

struct board {
    pair<int, int> start;
    pair<int, int> end;
    int rank;
    int save;
};

int n, p;
vector<board> boards;
map<pair<int, int>, int> pos_start;
map<pair<int, int>, int> pos_end;
vector<pair<pair<int, int>, int>> process;

int main() {
    ifstream fin("boards.in");
    ofstream fout("boards.out");

    fin >> n >> p;

    for (int i = 0; i < p; i++) {
        int a, b, c, d; fin >> a >> b >> c >> d;
        board bb;
        bb.start = {a, b};
        bb.end = {c, d};
        boards.push_back(bb);
    }    

    sort(boards.begin(), boards.end(), [](const board &b1, const board &b2) {
        if (b1.end.second == b2.end.second) {
            return b1.end.first < b2.end.first;
        }
        return b1.end.second < b2.end.second;
    });

    for (int i = 0; i < p; i++) {
        boards[i].rank = i + 1;
        pos_start[boards[i].start] = i + 1;
        pos_end[boards[i].end] = i + 1;
        process.push_back({boards[i].start, 1});
        process.push_back({boards[i].end, -1});
    }

    sort(process.begin(), process.end());

    for (auto pp : process) {
        if (pp.second > 0) {
            int loc = pos_start[pp.first];
            int save1 = query(1, 1, p, 1, loc);
            board* b = &boards[loc - 1];
            b->save = save1 + b->end.first - b->start.first + b->end.second - b->start.second;
        } else {
            int loc = pos_end[pp.first];
            update(1, 1, p, loc, boards[loc - 1].save);
        }
    }

    fout << 2 * n - query(1, 1, p, 1, p) << '\n';

    return 0;
}
