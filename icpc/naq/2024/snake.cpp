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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

pair<int, int> diff(pair<int, int> a, pair<int, int> b) {
    return {a.first - b.first, a.second - b.second};
}

pair<int, int> move(pair<int, int> a, int d) {
    return {a.first + dx[d], a.second + dy[d]};
}

int idx_of(pair<int, int> a) {
    rep(i, 0, 4) {
        if (a.first == dx[i] && a.second == dy[i]) {
            return i;
        }
    }
    return -1;
}

int left(int x) {
    return (x + 1) % 4;
}

int right(int x) {
    return (x + 3) % 4;
}

int TAIL_SIZE;

vector<int> uncompress(int tail) {
    vector<int> res(TAIL_SIZE);

    rep(i, 0, TAIL_SIZE) {
        res[i] = tail % 3;
        tail /= 3;
    }

    return res;
}

int compress(const vector<int> &tail) {
    int ans = 0;
    for (int i = TAIL_SIZE - 1; i >= 0; i--) {
        ans = 3 * ans + tail[i];
    }
    return ans;
}

struct loc {
    pair<int, int> head;
    int first_dir;
    int tail;

    bool operator<(const loc &other) const {
        return tie(head, first_dir, tail) < tie(other.head, other.first_dir, other.tail);
    }

    vector<pair<int, int>> get() const {
        int cur_d = first_dir;
        vector<pair<int, int>> res;
        res.reserve(TAIL_SIZE + 2);
        res.push_back(head);
        res.push_back(move(head, cur_d));

        auto changes = uncompress(tail);
        rep(i, 0, TAIL_SIZE) {
            if (changes[i] == 0) {
                cur_d = left(cur_d);
            } else if (changes[i] == 2) {
                cur_d = right(cur_d);
            }
            res.push_back(move(res.back(), cur_d));
        }

        return res;
    }
};

int gg(int x) {
    if (x == 3) return 2;
    if (x == 0) return 1;
    return 0;
}

loc conv(const vector<pair<int, int>> &path) {
    vector<int> tail;
    int cur_d = idx_of(diff(path[1], path[0])); 
    int init_d = cur_d;
    rep(i, 2, TAIL_SIZE+2) {
        auto new_d = idx_of(diff(path[i], path[i-1]));
        auto rot_amt = gg((new_d - cur_d + 4) % 4); // maps -1 -> 0, 0 -> 1, 1 -> 2
        tail.push_back(rot_amt);
        cur_d = new_d;
    }

    return loc{path[0], init_d, compress(tail)};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int r, c;
    cin >> r >> c;

    int ax, ay;

    vector<string> grid(r);
    vector<pair<int, int>> path(16, {-1, -1});
    rep(i, 0, r) {
        cin >> grid[i];
    }

    rep(i, 0, r) {
        rep(j, 0, c) {
            auto v = grid[i][j];
            if ('0' <= v && v <= '9') {
                path[v - '0'] = {i, j};
            } else if ('a' <= v && v <= 'f') {
                path[v - 'a' + 10] = {i, j};
            }

            if (v == 'A') {
                ax = i;
                ay = j;
            }
        }
    }

    while (path.back() == pair{-1, -1}) {
        path.pop_back();
    }

    if (sz(path) == 1) {
        cout << "1\n";
        return 0;
    }

    TAIL_SIZE = sz(path) - 2;

    auto init_loc = conv(path);

    auto cmp = [&](const auto &loc1, const auto &loc2) -> bool {
        auto d1 = abs(loc1.head.first - ax) + abs(loc1.head.second - ay);
        auto d2 = abs(loc2.head.first - ax) + abs(loc2.head.second - ay);
        return d1 > d2;
    };

    priority_queue<loc, vector<loc>, decltype(cmp)> q(cmp);
    q.push(init_loc);
    set<loc> vis;
    vis.insert(init_loc);

    auto in_bounds = [&](pair<int, int> a) {
        auto [x, y] = a;
        return x >= 0 && y >= 0 && x < r && y < c;
    };

    while (!q.empty()) {
        auto cur = q.top();
        q.pop();

        auto [x, y] = cur.head;
        if (grid[x][y] == 'A') {
            cout << "1\n";
            return 0;
        }

        auto cur_path = cur.get();
        cur_path.pop_back(); // last location doesn't matter anymore
        rep(d, 0, 4) {
            if (d != cur.first_dir) {
                auto new_head = move(cur_path[0], d);
                if (in_bounds(new_head) && count(all(cur_path), new_head) == 0) {
                    auto new_path = cur_path;
                    new_path.insert(new_path.begin(), new_head);
                    auto new_loc = conv(new_path);

                    auto [_, ok] = vis.insert(new_loc);
                    if (ok) {
                        q.push(new_loc);
                    }
                }
            }
        }
    }

    cout << "0\n";

    return 0;
}
