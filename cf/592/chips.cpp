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
#define MAXN 200000

using namespace std;

int n, k;
string s;
int cur[MAXN];
int dist[MAXN];

int start = -1;

int get(int pos) {
    pos %= n;
    if (pos < 0) pos += n;
    return pos;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    cin >> s;
    for (int i = 0; i < n; i++) {
        cur[i] = (s[i] == 'B');
    }

    for (int i = 0; i < n; i++) {
        if (cur[i] == cur[get(i + 1)]) {
            start = i + 1;
        }
    }

    if (start == -1) {
        if (k % 2 == 0) {
            cout << s << '\n';
        } else {
            for (int i = 0; i < n; i++) {
                if (cur[i]) {
                    cout << 'W';
                } else {
                    cout << 'B';
                }
            }
            cout << '\n';
        }
        return 0;
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (cur[get(i + start)] != cur[get(i + start + 1)]) {
            dist[get(i + start + 1)] = ++cnt;
        } else {
            dist[get(i + start + 1)] = (cnt = 0);
        }
    }

    cnt = 0;
    for (int i = 0; i < n; i++) {
        if (cur[get(-i + start)] != cur[get(-i + start - 1)]) {
            dist[get(-i + start - 1)] = min(++cnt, dist[get(-i + start - 1)]);
        } else {
            dist[get(-i + start - 1)] = (cnt = 0);
        }
    }

    for (int i = 0; i < n; i++) {
        if (k >= dist[i]) {
            if (dist[i] % 2 == 0) {
                cout << (cur[i] ? 'B' : 'W');
            } else {
                cout << (cur[i] ? 'W' : 'B');
            }
        } else {
            if (k % 2 == 0) {
                cout << (cur[i] ? 'B' : 'W');
            } else {
                cout << (cur[i] ? 'W' : 'B');
            }
        }
    }
    cout << '\n';

    return 0;
}
