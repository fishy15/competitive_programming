#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

#define MAXN 3010

using namespace std;

int n;
int s[MAXN];
int t[MAXN];
int ans;
int perm[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> t[i];
    for (int i = 0; i < n; i++) perm[i] = i;

    sort(s, s + n);
    sort(t, t + n);

    vector<pair<int, int>> cur;
    set<int> cow_left, spot_left;
    vector<int> ord;
    do {
        cow_left.clear();
        spot_left.clear();
        ord.clear();
        cur.clear();
        for (int i = 0; i < n; i++) {
            if (s[i] <= t[perm[i]]) {
                cur.push_back({i, perm[i]});
            } else {
                cow_left.insert(s[i]);
                spot_left.insert(t[perm[i]]);
                ord.push_back(perm[i]);
            }
        }
        if (!cur.empty() && (cow_left.empty() || *cow_left.begin() > *spot_left.rbegin())) {
            if (!next_permutation(ord.begin(), ord.end())) ans++;
        }
    } while (next_permutation(perm, perm + n));

    cout << ans << '\n';
    return 0;
}
