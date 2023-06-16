/*
 * First, we note that it makes sense to put people with similar preferences in the same team, so we sort
 * by the size in reverse order. For each index, we can store the number of teams, the max size of 
 * a team, and the size of the component. To transition from the answer for the first i elements to the first 
 * (i + 1) elements, we want to try putting a the new element in a pre-existing team. If all the teams are
 * at the max size so far, then we need to increment the max size, otherwise we should keep the max size 
 * the same. We can also create the transition of the formation of a new team, since if person i + 1 wants
 * a team of size x, then the team must have at least x elements. Doing the DP, we can calculate the max
 * number of teams and the min size of the biggest team. The DP also marks which locations are the ends 
 * of the team, so we can iterate and put people into teams. There may be some people left over, which we 
 * can just fill in (as long as the team sizes stay below the max size).
 */

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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000010

using namespace std;

int n;
pair<int, int> players[MAXN];
// {num_teams, max_size, cur_size}
array<int, 3> dp[MAXN];

void cmp(array<int, 3> &a, const array<int, 3> &b) {
    if (a[0] == b[0]) {
        a = min(a, b);
    } else {
        a = max(a, b);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> players[i].first;
        players[i].second = i;
    }

    sort(players, players + n, greater<pair<int, int>>());

    for (int i = 0; i <= n; i++) {
        dp[i] = {-1, 0};
    }

    dp[players[0].first] = {1, players[0].first, players[0].first};
    for (int i = 0; i < n; i++) {
        if (dp[i][0] != -1) {
            if (i == dp[i][0] * dp[i][1]) {
                cmp(dp[i + 1], {dp[i][0], dp[i][1] + 1, 0});
            } else {
                cmp(dp[i + 1], {dp[i][0], dp[i][1], 0});
            }
            if (i + players[i].first <= n) {
                cmp(dp[i + players[i].first], {dp[i][0] + 1, max(dp[i][1], players[i].first), players[i].first});
            }
        }
    }

    set<int> to_assign;
    vector<vector<int>> ans;
    int cur = n;

    while (cur > 0) {
        int nxt_cur = cur - dp[cur][2];
        if (nxt_cur == cur) {
            to_assign.insert(cur - 1);
            cur--;
        } else {
            ans.push_back({});
            for (int i = nxt_cur; i < cur; i++) {
                ans.back().push_back(players[i].second);
            }
            cur = nxt_cur;
        }
    }

    int idx = dp[n][0] - 1;
    for (int i : to_assign) {
        while ((int)(ans[idx].size()) == dp[n][1]) {
            idx--;
        }
        ans[idx].push_back(players[i].second);
    }

    cout << dp[n][0] << '\n';

    for (auto &v : ans) {
        cout << v.size() << ' ';
        for (int i : v) cout << i + 1 << ' ';
        cout << '\n';
    }


    return 0;
}
