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
#define MAXN 1000000

using namespace std;

int n, k;
vector<string> cc;
set<string> c;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        cc.push_back(s);
        c.insert(s);
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            string res;
            res.reserve(k);
            for (int p = 0; p < k; p++) {
                if (cc[i][p] == cc[j][p]) {
                    res += cc[i][p];
                } else {
                    if ((cc[i][p] == 'S' && cc[j][p] == 'E') || (cc[i][p] == 'E' && cc[j][p] == 'S')) {
                        res += 'T';
                    } else if ((cc[i][p] == 'S' && cc[j][p] == 'T') || (cc[i][p] == 'T' && cc[j][p] == 'S')) {
                        res += 'E';
                    } else {
                        res += 'S';
                    }
                }
            }

            ans += c.count(res);
        }
    }

    cout << ans / 3 << '\n';

    return 0;
}
