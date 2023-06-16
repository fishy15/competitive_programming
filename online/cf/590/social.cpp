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
#include <deque>

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

    deque<int> cur;
    set<int> in;

    int n, k; cin >> n >> k;

    for (int i = 0; i < n; i++) {
        int x; cin >> x; 
        if (!in.count(x)) {
            cur.push_front(x);
            in.insert(x);
            if (cur.size() == k + 1) {
                in.erase(cur.back());
                cur.pop_back();
            }
        }
    }

    cout << cur.size() << '\n';

    while (!cur.empty()) {
        cout << cur.front() << ' ';
        cur.pop_front();
    }

    return 0;
}
