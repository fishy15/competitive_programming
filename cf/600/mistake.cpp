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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;

    vector<int> ans;
    set<int> cur;
    set<int> done;
    int prev = -1;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x > 0) {
            if (done.count(x)) {
                cout << "-1\n";
                return 0;
            }

            done.insert(x);
            cur.insert(x);
        } else {
            x = -x;
            if (!cur.count(x)) {
                cout << "-1\n";
                return 0;
            }

            cur.erase(x);

            if (cur.empty()) {
                done = {};
                ans.push_back(i - prev);
                prev = i;
            }
        }
    }

    if (!cur.empty()) {
        cout << "-1\n";
        return 0;
    }

    cout << ans.size() << '\n';
    for (int i : ans) {
        cout << i << ' ';
    } cout << '\n';

    return 0;
}
