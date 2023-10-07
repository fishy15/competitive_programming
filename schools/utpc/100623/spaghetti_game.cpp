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
#define MAXN 200
#define MAXT 200

using namespace std;

bool win[MAXT + 1][MAXN + 1];
int mo[MAXT + 1][MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, ta;
    cin >> n >> m >> ta;

    const int t = ta;

    vector<int> a(n);
    for (auto &x : a) cin >> x;

    vector<int> b(m);
    for (auto &x : b) cin >> x;

    a.push_back(0);
    b.push_back(0);

    /* cout << "T: " << t << endl; */

    // initial state
    for (int i = 0; i <= MAXN; i++) {
        win[0][i] = (i >= t);
    }

    for (int ct = 1; ct <= MAXT; ct++) {
        if (ct % 2 == 0) {
            for (int i = 0; i <= MAXN; i++) {
                win[ct][i] = (i >= t);
            }

            // lario turn
            /* cout << "l" << endl; */
            for (int i = 0; i < t; i++) {
                for (auto m : a) {
                    if (i + m >= t || !win[ct - 1][i + m]) {
                        /* cout << "move from " << i << " wins " << m << endl; */
                        /* cout << (i + m >= t) << ' ' << (!win[ct - 1][i + m]) << endl; */
                        win[ct][i] = true;
                        mo[ct][i] = m;
                        break;
                    }
                }
            }
        } else {
            /* cout << "m" << endl; */
            for (int i = 0; i < t; i++) {
                for (auto m : b) {
                    /* if (i - m >= 0) { cout << "move " << i << ' ' << m << ' ' << !win[ct - 1][i - m] << endl; } */
                    if (i - m >= 0 && !win[ct - 1][i - m]) {
                        win[ct][i] = true;
                        mo[ct][i] = m;
                        break;
                    }
                }
            }
        }

        /* for (int a = 0; a <= t; a++) { */
        /*     cout << "(" << win[ct][a] << " " << mo[ct][a] << ") "; */
        /* } */
        /* cout << '\n'; */
    }

    if (win[200][0]) {
        cout << "Lario" << endl;
        int cur_size = 0;
        for (int i = 200; i > 0; i -= 2) {
            cout << mo[i][cur_size] << endl;
            cur_size += mo[i][cur_size];

            if (cur_size >= t) break;

            int mm;
            cin >> mm;
            cur_size -= mm;
        }
    } else {
        cout << "Muigi" << endl;
        int cur_size = 0;
        for (int i = 200 - 1; i > 0; i -= 2) {
            int mm;
            cin >> mm;
            cur_size += mm;

            if (cur_size >= t) break;

            cout << mo[i][cur_size] << endl;
            cur_size -= mo[i][cur_size];
        }
    }

    return 0;
}
