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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    // 1 = up, 2 = down
    int a = 0;
    int b = 0;
    vector<int> aisle(n);

    for (int i = 0; i < k; i++) {
        string id, dir;
        cin >> id >> dir;

        if (id[0] == 'A' || id[0] == 'B') {
            auto &to_set = id[0] == 'A' ? a : b;
            if (dir[0] == 'N') {
                to_set = 1;
            } else {
                to_set = 2;
            }
        } else {
            int idx = stoi(id) - 1;
            if (dir[0] == 'W') {
                aisle[idx] = 1;
            } else {
                aisle[idx] = 2;
            }
        }
    }

    ll ans = 0;

    auto same_dir = [&] {
        int first_nonmatch = -1;
        bool bad = false;

        for (int i = 0; i < n; i++) {
            if (aisle[i] != 0) {
                if (first_nonmatch == -1) {
                    first_nonmatch = i;
                } else {
                    if (first_nonmatch % 2 == i % 2) {
                        bad |= aisle[first_nonmatch] != aisle[i];
                    } else {
                        bad |= aisle[first_nonmatch] == aisle[i];
                    }
                }
            }
        }

        if (first_nonmatch == -1) {
            ans += 2;
        } else if (!bad) {
            ans += 1;
        }
    };

    auto diff_dir = [&] {
        int rest_cnt = 0;
        for (int i = 1; i < n - 1; i++) {
            if (aisle[i] == 0) {
                rest_cnt++;
            }
        }

        ans += 1LL << rest_cnt; 
    };

    // both going down
    if (a != 2 && b != 2) {
        if (aisle[0] != 1 && aisle[n - 1] != 1) {
            int old_a = aisle[0];
            int old_b = aisle[n - 1];

            aisle[0] = 2;
            aisle[n - 1] = 2;

            same_dir();

            aisle[0] = old_a;
            aisle[n - 1] = old_b;
        }
    }

    // both going up
    if (a != 1 && b != 1) {
        if (aisle[0] != 2 && aisle[n - 1] != 2) {
            int old_a = aisle[0];
            int old_b = aisle[n - 1];

            aisle[0] = 1;
            aisle[n - 1] = 1;

            same_dir();

            aisle[0] = old_a;
            aisle[n - 1] = old_b;
        }
    }

    if (a != 1 && b != 2) {
        if (aisle[0] != 1 && aisle[n - 1] != 2) {
            diff_dir();
        }
    }

    if (a != 2 && b != 1) {
        if (aisle[0] != 2 && aisle[n - 1] != 1) {
            diff_dir();
        }
    }

    cout << ans << '\n';

    return 0;
}
