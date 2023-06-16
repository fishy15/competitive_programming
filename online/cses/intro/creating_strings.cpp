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

int n;
string s;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    n = (int)(s.size());

    vector<int> cur;
    set<string> ans;

    for (int i = 0; i < n; i++) {
        cur.push_back(i);
    }

    do {
        string thonk = "";
        for (int i : cur) {
            thonk += s[i];
        }
        ans.insert(thonk);
    } while (next_permutation(cur.begin(), cur.end()));

    cout << ans.size() << '\n';
    for (string s : ans) {
        cout << s << '\n';
    }

    return 0;
}
