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
#include <optional>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

struct state {
    map<int, int> cnt;
    bool wildcard = false;

    void add(int card) {
        cnt[card]++;
    }

    int rem() {
        // freq, value
        pair<int, int> best = {INF, -1};
        for (auto [v, c] : cnt) {
            best = min(best, {c, v});
        }

        auto to_rem = best.second;
        cnt[to_rem]--;
        if (cnt[to_rem] == 0) {
            cnt.erase(to_rem);
        }

        return to_rem;
    }

    pair<bool, int> winning() {
        auto it = cnt.begin();
        auto num_cards = it->second;
        if (sz(cnt) == 1 && num_cards == 4 && !wildcard) {
            return {true, it->first};
        } else {
            return {false, -1};
        }
    }
};

string cards = "A23456789DQJK";
int get_value(char c) {
    return cards.find(c);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;
    k--;

    vector<state> ppl(n);
    rep(i, 0, n) {
        string cs;
        cin >> cs;
        for (auto c : cs) {
            ppl[i].add(get_value(c));
        }
    }

    ppl[k].wildcard = true;
    int wildcard_turn = -1;
    int turn = 0;
    int cur = k;

    // check if anyone is initially winning
    // value, who
    auto get_winner = [&] {
        pair<int, int> init_win = {INF, -1};
        rep(i, 0, n) {
            auto [win, v] = ppl[i].winning();
            if (win) {
                init_win = min(init_win, pair{v, i});
            }
        }

        return init_win.second;
    };

    auto init_win = get_winner();
    if (init_win != -1) {
        cout << init_win + 1 << '\n';
        return 0;
    }

    while (true) {
        int nxt = (cur + 1) % n;
        if (ppl[cur].wildcard && turn - wildcard_turn > 1) {
            ppl[cur].wildcard = false;
            ppl[nxt].wildcard = true;
            wildcard_turn = turn;
            /* cout << cur << " moves wildcard to " << nxt << endl; */
        } else {
            auto v = ppl[cur].rem();
            ppl[nxt].add(v);

            /* cout << cur << " moves " << v << " to " << nxt << endl; */
        }

        auto win = get_winner();
        if (win != -1) {
            cout << win + 1 << '\n';
            return 0;
        }

        turn++;
        cur = nxt;
    }

    return 0;
}
