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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

using row = array<int, 5>;
using bingo = array<row, 5>;

bool in(const row &r, int num) {
    return count(r.begin(), r.end(), num) > 0;
}

bool works(const row &r, const set<int> &nums) {
    for (int x : r) {
        if (!nums.count(x)) {
            return false;
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<bingo> boards;
    for (int i = 0; i < n; i++) {
        bingo board;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                cin >> board[j][k];
            }
        }

        boards.push_back(board);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int a = 0; a < 5; a++) {
                for (int b = 0; b < 5; b++) {
                    for (int x : boards[i][a]) {
                        if (in(boards[j][b], x)) {
                            set<int> other;

                            for (int y : boards[i][a]) {
                                other.insert(y);
                            }

                            for (int y : boards[j][b]) {
                                other.insert(y);
                            }

                            other.erase(x);

                            bool ok = true;
                            for (int k = 0; k < n; k++) {
                                for (int c = 0; c < 5; c++) {
                                    if (works(boards[k][c], other)) {
                                        ok = false;
                                        break;
                                    }
                                }
                            }

                            if (ok) {
                                cout << i + 1 << ' ' << j + 1 << '\n';
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "no ties\n";

    return 0;
}
