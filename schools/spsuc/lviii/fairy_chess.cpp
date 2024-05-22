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

using u64 = unsigned long long;

constexpr int K = 1;
constexpr int B = 2;
constexpr int R = 4;

// 1 = knight
// 2 = bishop
// 4 = rook
map<char, int> getm{
    {'B', 2},
    {'R', 4},
    {'Q', 2 xor 4},
    {'A', 1 xor 2},
    {'C', 1 xor 4},
    {'M', 1 xor 2 xor 4},
};

array<int, 8> dx = {2, 1, -1, -2, -2, -1, 1, 2};
array<int, 8> dy = {1, 2, 2, 1, -1, -2, -2, -1};

int get(u64 mask, int x, int y) {
    return (mask >> (x * 8 + y)) & 1;
}

void toggle(u64 &mask, int x, int y) {
    mask ^= 1ull << (x * 8 + y);
}

u64 compute_knight_mask(int x, int y) {
    u64 res = 0;
    toggle(res, x, y);

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (min(nx, ny) >= 0 && max(nx, ny) < 8) {
            toggle(res, nx, ny);
        }
    }

    return res;
}

u64 compute_bishop_mask(int x, int y) {
    u64 res = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i - j == x - y || i + j == x + y) {
                toggle(res, i, j);
            }
        }
    }

    return res;
}

u64 compute_rook_mask(int x, int y) {
    u64 res = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (x == i || y == j) {
                toggle(res, i, j);
            }
        }
    }

    return res;
}

struct state {
    u64 placed;
    u64 covered;
    int added;

    bool operator==(const state &st) const {
        return tie(placed, covered, added) == tie(st.placed, st.covered, st.added);
    }
};

struct chash {
    size_t operator()(const state &st) const {
        return st.placed ^ st.covered;
    }
};

void pr(u64 m) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << get(m, i, j);
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string ord;
    cin >> ord;

    array<array<u64, 8>, 8> knight_mask{}, rook_mask{}, bishop_mask{};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            knight_mask[i][j] = compute_knight_mask(i, j);
            rook_mask[i][j] = compute_rook_mask(i, j);
            bishop_mask[i][j] = compute_bishop_mask(i, j);
        }
    }

    unordered_map<state, bool, chash> cache;

    auto solve = [&](auto &&self, state cur) -> bool {
        auto it = cache.find(cur);
        if (it != cache.end()) {
            return it->second;
        }

        bool ans = false;
        if (cur.added == (int) ord.size()) {
            ans = false;
        } else {
            auto piece = getm[ord[cur.added]];
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    // if unset, then we are not attacked by a placed piece
                    if (get(cur.covered, i, j) == 0) {
                        u64 will_cover = 0;
                        if (piece & K) will_cover |= knight_mask[i][j];
                        if (piece & R) will_cover |= rook_mask[i][j];
                        if (piece & B) will_cover |= bishop_mask[i][j];

                        // if unset, then we don't attack anything placed either
                        if ((will_cover & cur.placed) == 0) {
                            auto nxt = cur;
                            toggle(nxt.placed, i, j);
                            nxt.covered |= will_cover;
                            nxt.added++;

                            if (!self(self, nxt)) {
                                ans = true;
                                goto cleanup;
                            }
                        }
                    }
                }
            }
        }

cleanup:
        return ans;
        // return cache[cur] = ans;
    };

    state empty{0, 0, 0};
    if (solve(solve, empty)) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
    }

    return 0;
}
