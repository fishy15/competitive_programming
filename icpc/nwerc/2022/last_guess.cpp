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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

#include <bits/extc++.h>

using namespace std;

typedef vector<int> vi;
#define sz(x) (int) (x).size()
#define rep(i,a,b) for(int i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
    struct edge {
        int from, to, rev;
        ll cap, cost, flow;
    };
    int N;
    vector<vector<edge>> ed;
    vi seen;
    vector<ll> dist, pi;
    vector<edge*> par;

    MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

    void addEdge(int from, int to, ll cap, ll cost) {
        if (from == to) return;
        ed[from].push_back(edge{from, to, sz(ed[to]), cap, cost, 0});
        ed[to].push_back(edge{to, from, sz(ed[from])-1, 0, -cost, 0});
    }

    void path(int s) {
        fill(all(seen), 0);
        fill(all(dist), INF);
        dist[s] = 0; ll di;

        __gnu_pbds::priority_queue<pair<ll, int>> q;
        vector<decltype(q)::point_iterator> its(N);
        q.push({0, s});

        while (!q.empty()) {
            s = q.top().second; q.pop();
            seen[s] = 1; di = dist[s] + pi[s];
            for (edge& e : ed[s]) if (!seen[e.to]) {
                ll val = di - pi[e.to] + e.cost;
                if (e.cap - e.flow > 0 && val < dist[e.to]) {
                    dist[e.to] = val;
                    par[e.to] = &e;
                    if (its[e.to] == q.end())
                        its[e.to] = q.push({-dist[e.to], e.to});
                    else
                        q.modify(its[e.to], {-dist[e.to], e.to});
                }
            }
        }
        rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
    }

    pair<ll, ll> maxflow(int s, int t) {
        ll totflow = 0, totcost = 0;
        while (path(s), seen[t]) {
            ll fl = INF;
            for (edge* x = par[t]; x; x = par[x->from])
                fl = min(fl, x->cap - x->flow);

            totflow += fl;
            for (edge* x = par[t]; x; x = par[x->from]) {
                x->flow += fl;
                ed[x->to][x->rev].flow -= fl;
            }
        }
        rep(i,0,N) for(edge& e : ed[i]) totcost += e.cost * e.flow;
        return {totflow, totcost/2};
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int g, l;
    cin >> g >> l;
    
    string ans(l, ' ');
    vector is_not(l, array<bool, 26>{});
    array<bool, 26> locked{};

    vector<pair<string, string>> qrys;
    for (int i = 0; i < g - 1; i++) {
        string word, res;
        cin >> word >> res;
        qrys.push_back({word, res});

        for (int j = 0; j < l; j++) {
            int c = word[j] - 'a';
            if (res[j] == 'G') {
                ans[j] = word[j];
            } else if (res[j] == 'Y') {
                is_not[j][c] = true;
            } else {
                locked[c] = true;
                is_not[j][c] = true;
            }
        }

    }

    array<int, 26> cnt{};
    rep(c, 0, 26) {
        set<int> known_locs;
        vector<pair<int, int>> know_dont;
        for (const auto &[word, res] : qrys) {
            int know = 0;
            int dont = 0;
            rep(i, 0, l) {
                if (word[i] == (char) (c + 'a')) {
                    if (res[i] == 'G') {
                        known_locs.insert(i);
                        know++;
                    } else if (res[i] == 'Y') {
                        dont++;
                    }
                }
            }
            know_dont.push_back({know, dont});
        }

        for (auto [know, dont] : know_dont) {
            int know_not_included = known_locs.size() - know;
            cnt[c] = max(cnt[c], dont - know_not_included);
        }
    }

    auto idx = [&](int i) { return i; };
    auto chr = [&](int c) { return l + c; };
    auto chro = [&](int c) { return l + 26 + c; };
    int s = l + 26 + 26;
    int t = s + 1;

    MCMF gr(t + 1);

    for (int i = 0; i < l; i++) {
        gr.addEdge(s, idx(i), 1, 0);

        if (ans[i] == ' ') {
            for (int c = 0; c < 26; c++) {
                if (!is_not[i][c]) {
                    gr.addEdge(idx(i), chr(c), 1, 0);

                    if (!locked[c]) {
                        gr.addEdge(idx(i), chro(c), 1, 1);
                    }
                }
            }
        }
    }

    for (int c = 0; c < 26; c++) {
        gr.addEdge(chr(c), t, cnt[c], 0);
        gr.addEdge(chro(c), t, l, 0);
    }

    gr.maxflow(s, t);

    for (auto &row : gr.ed) {
        for (auto &e : row) {
            if (idx(0) <= e.from && e.from <= idx(l - 1)) {
                int i = e.from - idx(0);
                if (chr(0) <= e.to && e.to <= chr(25)) {
                    if (e.flow == 1) {
                        int c = e.to - chr(0);
                        ans[i] = (char) ('a' + c);
                    }
                } else if (chro(0) <= e.to && e.to <= chro(25)) {
                    if (e.flow == 1) {
                        int c = e.to - chro(0);
                        ans[i] = (char) ('a' + c);
                    }
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
