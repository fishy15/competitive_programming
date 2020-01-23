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
#include <list>
#include <iterator>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    string s; cin >> s;
    list<pair<char, int>> cur = {};

    int c = '.';
    int cnt = 0;

    for (char c2 : s) {
        if (c == c2) {
            cnt++;
        } else {
            if (cnt > 0) {
                cur.push_back({c, cnt});
            }
            cnt = 1;
            c = c2;
        }
    }

    cur.push_back({c, cnt});
    cnt = 0;

    while (cur.size() > 1) {
        int minstep = INF;
        int i = 0;
        for (auto it = cur.begin(); it != cur.end(); it++, i++) {
            if (i == 0 || i == cur.size() - 1) {
                minstep = min(minstep, it->second);
            } else {
                minstep = min(minstep, (it->second + 1) / 2);
            }
        }

        cnt += minstep;

        i = 0;
        for (auto it = cur.begin(); it != cur.end(); it++, i++) {
            if (i == 0 || i == cur.size() - 1) {
                it->second -= minstep;
            } else {
                it->second -= 2 * minstep;
            }
        }

        auto it = cur.begin();
        while (!cur.empty() && it != cur.end()) {
            if (it->second <= 0) {
                it++;
                cur.erase(prev(it));
            } else {
                it++;
            }
        }

        it = cur.begin();
        while (!cur.empty() && next(it) != cur.end()) {
            if (it->first == next(it)->first) {
                it->second += next(it)->second;
                cur.erase(next(it));
            } else {
                it++;
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
