// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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
    cin.tie(0); ios::sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        set<int> ans;
        int smth = (int)(sqrt(n));
        for (int i = 0; i <= smth; i++) {
            ans.insert(i);
        }
        int pos = 1;
        while (n / pos != smth) {
            ans.insert(n / pos);
            pos++;
        }

        cout << ans.size() << '\n';
        for (int i : ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }

    return 0;
}
