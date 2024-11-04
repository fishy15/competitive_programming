#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int INF = 0x3f3f3f3f;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

vector<bool> cutpoints(const vector<vi> &adj) {
    int timer=0, n=sz(adj);
    vi tin(n,-1), low(n,-1);
    vector<bool> vis(n);
    vector<bool> iscut(n);
    auto dfs = [&](auto &&self, int v, int p) -> void {
        vis[v] = true;
        tin[v] = low[v] = timer++;
        int ch = 0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (vis[to])
                low[v] = min(low[v], tin[to]);
            else {
                self(self, to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p!=-1) iscut[v]=1;
                ++ch;
            }
        }
        if(p == -1 && ch > 1) iscut[v]=1;
    };
    rep(i,0,n) if (!vis[i]) dfs(dfs, i, -1);
    return iscut;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int r, c;
    cin >> r >> c;

    vector<string> start(r), finish(r);
    rep(i, 0, r) {
        cin >> start[i];
    }
    rep(i, 0, r) {
        cin >> finish[i];
    }

    auto comp_dists = [&](int sx, int sy) {
        vector dist(r, vector(c, 0x3f3f3f3fLL));
        queue<pii> q;
        q.push({sx, sy});
        dist[sx][sy] = 0;


        auto ok = [&](int x, int y) {
            return x >= 0 && x < r && y >= 0 && y < c && dist[x][y] == INF && finish[x][y] != 'X';
        };

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            rep(d, 0, 4) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (ok(nx, ny)) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        return dist;
    };

    auto get_finish_ord = [&] {
        vector vis(r, vector(c, false));

        auto ok = [&](int x, int y) {
            if (x >= 0 && x < r && y >= 0 && y < c) {
                if (finish[x][y] == '*' && !vis[x][y]) {
                    return true;
                }
            }
            return false;
        };

        int sx, sy;
        rep(i, 0, r) {
            rep(j, 0, c) {
                if (finish[i][j] == '*') {
                    sx = i;
                    sy = j;
                    goto start_bfs;
                }
            }
        }

start_bfs:
        queue<pii> q;
        q.push({sx, sy});
        vis[sx][sy] = true;

        vector<pii> ord;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            ord.push_back({x, y});

            rep(d, 0, 4) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (ok(nx, ny)) {
                    vis[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }

        return ord;
    };


    vector<pii> finish_pts = get_finish_ord();

    vector sum_dists(r, vector(c, 0LL));
    rep(i, 0, r) {
        rep(j, 0, c) {
            if (finish[i][j] == '*') {
                auto dists = comp_dists(i, j);
                rep(x, 0, r) {
                    rep(y, 0, c) {
                        sum_dists[x][y] += dists[x][y];
                    }
                }
            }
        }
    }

    auto heuristic = [&](const vector<vector<ll>> &vals, const vector<string> &grid) {
        ll best = INF;
        rep(i, 0, r) {
            rep(j, 0, c) {
                if (grid[i][j] == '*') {
                    best = min(best, vals[i][j]);
                }
            }
        }
        return best;
    };

    auto adj_to_star = [&](const vector<string> &grid, int i, int j) {
        auto ok = [&](int x, int y) {
            if (x >= 0 && x < r && y >= 0 && y < c) {
                if (grid[x][y] == '*') {
                    return true;
                }
            }
            return false;
        };

        rep(d, 0, 4) {
            int nx = i + dx[d];
            int ny = j + dy[d];
            if (ok(nx, ny)) {
                return true;
            }
        }

        return false;
    };

    auto comp = [&](int x, int y) {
        return x * c + y;
    };
    auto decomp = [&](int num) {
        return pair{num / c, num % c};
    };

    auto compress = [&](const vector<string> &grid) {
        int n = r * c;
        vector<vi> adj(n);
        auto ok = [&](int x, int y) {
            if (x >= 0 && x < r && y >= 0 && y < c) {
                if (grid[x][y] == '*') {
                    return true;
                }
            }
            return false;
        };
        rep(i, 0, r) {
            rep(j, 0, c) {
                if (grid[i][j] == '*') {
                    rep(d, 0, 4) {
                        int nx = i + dx[d];
                        int ny = j + dy[d];
                        if (ok(nx, ny)) {
                            adj[comp(i, j)].push_back(comp(nx, ny));
                        }
                    }
                }
            }
        }
        return adj;
    };

    vector fixed(r, vector(c, false));
    vector<array<int, 4>> moves;
    auto cur = start;

    for (auto [gx, gy] : finish_pts) {
        auto dists = comp_dists(gx, gy);

        vector<vector<pii>> levels;
        rep(i, 0, r) {
            rep(j, 0, c) {
                if (dists[i][j] != INF) {
                    while (sz(levels) <= dists[i][j]) {
                        levels.push_back({});
                    }
                    levels[dists[i][j]].push_back({i, j});
                }
            }
        }

        while (cur[gx][gy] == '.') {
            auto orig_h = heuristic(dists, cur);

            array<int, 4> move;
            move.fill(-1);

            auto adj = compress(cur);
            auto iscut = cutpoints(adj);
            vi remove, cutpts;
            rep(i, 0, r*c) {
                auto [x, y] = decomp(i);
                if (cur[x][y] == '*') {
                    if (iscut[i] || fixed[x][y]) {
                        cutpts.push_back(i);
                    } else {
                        remove.push_back(i);
                    }
                }
            }

            assert(sz(remove) > 0);

            int mx = -1, my = -1;
            if (orig_h == INF) {
                goto done;
            }
            assert(orig_h > 0);

            for (auto [i, j] : levels[orig_h - 1]) {
                if (adj_to_star(cur, i, j)) {
                    if (sz(remove) >= 2) {
                        mx = i;
                        my = j;
                        break;
                    } else {
                        auto [rx, ry] = decomp(remove[0]);
                        bool adjacent = false;
                        rep(d, 0, 4) {
                            int nx = i + dx[d];
                            int ny = j + dy[d];
                            if (nx >= 0 && nx < r && ny >= 0 && ny < c && cur[nx][ny] == '*') {
                                if (nx != rx || ny != ry) {
                                    adjacent = true;
                                }
                            }
                        }

                        if (adjacent) {
                            mx = i;
                            my = j;
                            break;
                        }
                    }
                }
            }

            if (mx == -1) {
                goto done;
            }

            for (auto pt : remove) {
                auto [x, y] = decomp(pt);
                cur[x][y] = '.';
                if (adj_to_star(cur, mx, my)) {
                    move = {x, y, mx, my};
                    cur[mx][my] = '*';
                    break;
                }
                cur[x][y] = '*';
            }

    done:
            if (move[0] == -1) {
                cout << "NO\n";
                return 0;
            }
            moves.push_back(move);
        }

        fixed[gx][gy] = true;
    }

    cout << "YES\n";
    cout << sz(moves) << '\n';
    for (auto [a, b, i, j] : moves) {
        cout << a+1 << ' ' << b+1 << ' ' << i+1 << ' ' << j+1 << '\n';
    }

    return 0;
}

