/* #include <iostream> */
/* #include <map> */
/* #include <set> */
/* #include <utility> */
/* #include <vector> */

#include <bits/stdc++.h>

using namespace std;

constexpr int INF = 0x3f3f3f3f;

// NESW 0 1 2 3

enum dir {
    N = 0,
    E,
    S,
    W
};

struct edge {
    int v;
    int d;
    int id;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> ints(n);
    for (auto &[x, y] : ints) {
        cin >> y >> x;
    }

    // {nxt, k, id}
    vector<vector<edge>> adj(n);
    vector<int> power(m);

    for (int i = 0; i < m; i++) {
        int x, y, k;
        cin >> x >> y >> k;
        x--;
        y--;

        if (ints[x].first == ints[y].first) {
            if (ints[x].second > ints[y].second) swap(x, y);
            adj[x].push_back({y, E, i});
            adj[y].push_back({x, W, i});
        } else {
            if (ints[x].first > ints[y].first) swap(x, y);
            adj[x].push_back({y, N, i});
            adj[y].push_back({x, S, i});
        }

        power[i] = k;
    }

    vector<bool> exists(m, true);

    // tail part + cycle part
    auto find_path = [&](int sx, int sdir) -> pair<vector<pair<int, int>>, vector<pair<int, int>>> {
        int cur = sx;
        int cd = sdir;

        set<pair<int, int>> vis;
        vector<pair<int, int>> path;
        while (!vis.count({cur, cd})) {
            vis.insert({cur, cd});
            path.push_back({cur, cd});

            vector<edge> poss;
            int opp = (cd + 2) % 4;
            for (auto e : adj[cur]) {
                if (e.d != opp && exists[e.id]) {
                    poss.push_back(e);
                }
            }

            if (poss.size() == 0) {
                // we stop here
                return {path, {}};
            } else if (poss.size() == 1) {
                // must keep going
                cur = poss[0].v;
                cd = poss[0].d;
            } else if (poss.size() == 2) {
                // choose the more "left" i.e. first when we decrease direction
                // check if either is 1 left, otherwise check if either is two left
                if (poss[0].d == (opp + 1) % 4) {
                    cur = poss[0].v;
                    cd = poss[0].d;
                } else if (poss[1].d == (opp + 1) % 4) {
                    cur = poss[1].v;
                    cd = poss[1].d;
                } else if (poss[0].d == (opp + 2) % 4) {
                    cur = poss[0].v;
                    cd = poss[0].d;
                } else if (poss[1].d == (opp + 2) % 4) {
                    cur = poss[1].v;
                    cd = poss[1].d;
                }
            } else {
                for (auto e : poss) {
                    if (e.d == cd) {
                        cur = e.v;
                        cd = e.d;
                    }
                }
            }
        }

        auto it = find(path.begin(), path.end(), pair{cur, cd});
        vector tail(path.begin(), it);
        vector cycle(it, path.end());
        return {tail, cycle};
    };

    int start;
    cin >> start;
    start--;

    char startdc;
    cin >> startdc;
    int startd = "NESW"s.find(startdc);

    int cur = start;
    int cd = startd;

    // take a single step
    /* for (auto e : adj[cur]) { */
    /*     if (e.d == cd) { */
    /*         power[e.id]--; */
    /*         if (power[e.id] == 0) { */
    /*             exists[e.id] = false; */
    /*         } */
    /*         cur = e.v; */
    /*         cd = e.d; */
    /*     } */
    /* } */

    while (true) {
start_again:
        auto [tail, cycle] = find_path(cur, cd);

        /* cout << "on tail" << endl; */
        /* for (auto [v, d] : tail) { */
        /*     cout << v << ' ' << d << endl; */
        /* } */
        /* cout << "on cycle" << endl; */
        /* for (auto [v, d] : cycle) { */
        /*     cout << v << ' ' << d << endl; */
        /* } */

        // we are done
        if (tail.size() == 1 && cycle.empty()) {
            break;
        }

        // just need to go over this once
        for (int i = 0; i < (int) tail.size(); i++) {
            cur = tail[i].first;
            cd = tail[i].second;

            // we have an edge to remove
            if (i < (int) tail.size() - 1) {
                auto nxtd = tail[i + 1].second;
                edge mine;
                for (auto e : adj[cur]) {
                    if (e.d == nxtd) {
                        mine = e;
                        break;
                    }
                }

                if (!exists[mine.id]) {
                    goto start_again;
                } else {
                    power[mine.id]--;
                    if (power[mine.id] == 0) {
                        exists[mine.id] = false;
                    }
                }
            }
        }

        if (!tail.empty() && !cycle.empty()) {
            auto [nxtv, nxtd] = cycle[0];
            edge mine;
            for (auto e : adj[cur]) {
                if (e.d == nxtd) {
                    mine = e;
                    break;
                }
            }

            if (!exists[mine.id]) {
                goto start_again;
            } else {
                power[mine.id]--;
                if (power[mine.id] == 0) {
                    exists[mine.id] = false;
                }
            }
        }

        // id -> count
        map<int, int> cyc_count;
        for (int i = 0; i < (int) cycle.size(); i++) {
            int v = cycle[i].first;
            int d = cycle[(i + 1) % cycle.size()].second;
            edge mine;
            for (auto e : adj[v]) {
                if (e.d == d) {
                    mine = e;
                    break;
                }
            }
            cyc_count[mine.id]++;
        }

        int full_cycles = INF;
        for (auto [id, cnt] : cyc_count) {
            full_cycles = min(full_cycles, power[id] / cnt);
        }
        for (auto [id, cnt] : cyc_count) {
            power[id] -= full_cycles * cnt;
            if (power[id] == 0) {
                exists[id] = false;
            }
        }

        // check if we break any time
        for (int i = 0; i < (int) cycle.size(); i++) {
            int v = cycle[i].first;
            int d = cycle[(i + 1) % cycle.size()].second;
            edge mine;
            for (auto e : adj[v]) {
                if (e.d == d) {
                    mine = e;
                    break;
                }
            }

            if (!exists[mine.id]) {
                goto start_again;
            } else {
                power[mine.id]--;
                if (power[mine.id] == 0) {
                    exists[mine.id] = false;
                }
            }

            cur = cycle[(i + 1) % cycle.size()].first;
            cd = cycle[(i + 1) % cycle.size()].second;
        }
    }

    cout << ints[cur].first << ' ' << ints[cur].second << '\n';

    return 0;
}
