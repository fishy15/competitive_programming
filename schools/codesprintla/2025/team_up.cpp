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
#include <cassert>

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

struct max_segtree {
    int n;
    vector<int> tree;
    max_segtree(int _n) : n(_n), tree(2*n, -INF) {}
    
    //qry [l, r]
    int qry(int l, int r) {
        l+=n; r+=n;
        int res = -INF;
        while(l<=r) {
            if(l%2==1)
                res=max(res,tree[l++]);
            if(r%2==0)
                res=max(res,tree[r--]);
            l/=2;
            r/=2;
        }
        return res;
    }
    void reset(int p) { set(p, -INF); }
    void set(int p, int v) {
        p+=n;
        tree[p] = v;
        p/=2;
        while(p > 0) {
            tree[p] = max(tree[2*p],tree[2*p+1]);
            p/=2;
        }
    }
};

struct min_segtree {
    int n;
    vector<int> tree;
    min_segtree(int _n) : n(_n), tree(2*n, INF) {}
    
    //qry [l, r]
    int qry(int l, int r) {
        l+=n; r+=n;
        int res = INF;
        while(l<=r) {
            if(l%2==1)
                res=min(res,tree[l++]);
            if(r%2==0)
                res=min(res,tree[r--]);
            l/=2;
            r/=2;
        }
        return res;
    }
    void reset(int p) { set(p, INF); }
    void set(int p, int v) {
        p+=n;
        tree[p] = v;
        p/=2;
        while(p > 0) {
            tree[p] = min(tree[2*p],tree[2*p+1]);
            p/=2;
        }
    }
};

struct add_segtree {
    int n;
    vector<int> tree;
    add_segtree(int _n) : n(_n), tree(2*n) {}
    
    //qry [l, r]
    int qry(int l, int r) {
        l+=n; r+=n;
        int res = 0;
        while(l<=r) {
            if(l%2==1)
                res+=tree[l++];
            if(r%2==0)
                res+=tree[r--];
            l/=2;
            r/=2;
        }
        return res;
    }
    void reset(int p) { set(p, 0); }
    void set(int p, int v) {
        p+=n;
        tree[p] = v;
        p/=2;
        while(p > 0) {
            tree[p] = tree[2*p]+tree[2*p+1];
            p/=2;
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> teams(n);
    vector<set<int>> by_team(n);
    rep(i, 0, n) {
        cin >> teams[i];
        teams[i]--;
        by_team[teams[i]].insert(i);
    }

    min_segtree first_second(n);
    max_segtree first_last(n);
    min_segtree last_first(n);
    max_segtree last_stl(n); // second to last
    add_segtree first_count_not_me(n);
    add_segtree last_count_not_me(n);

    auto modify_team = [&](const set<int> &team, bool adding) {
        if (sz(team) >= 2) {
            int first = *begin(team);
            int last = *rbegin(team);
            int second, stl;
            if (sz(team) == 2) {
                second = last;
                stl = first;
            } else if (sz(team) == 3) {
                int mid = *next(begin(team));
                second = mid;
                stl = mid;
            } else {
                second = *next(begin(team));
                stl = *next(rbegin(team));
            }

            if (adding) {
                first_second.set(first, second);
                /*cout << "Upding " << first << " to " << second << endl;*/
                first_last.set(first, last);
                last_first.set(last, first);
                last_stl.set(last, stl);
                first_count_not_me.set(first, sz(team) - 1);
                last_count_not_me.set(last, sz(team) - 1);
            } else {
                first_second.reset(first);
                /*cout << "restting " << first << endl;*/
                first_last.reset(first);
                last_first.reset(last);
                last_stl.reset(last);
                first_count_not_me.reset(first);
                last_count_not_me.reset(last);
            }
        }
    };

    for (const auto &t : by_team) {
        modify_team(t, true);
    }

    while (q--) {
        int typ;
        cin >> typ;

        if (typ == 1) {
            int t, i;
            cin >> t >> i;
            t--;
            i--;

            int old_t = teams[i];
            if (old_t != t) {
                modify_team(by_team[old_t], false);
                modify_team(by_team[t], false);
                by_team[old_t].erase(i);
                teams[i] = t;
                by_team[t].insert(i);
                modify_team(by_team[old_t], true);
                modify_team(by_team[t], true);
            }
        } else {
            int t;
            cin >> t;
            t--;

            auto &cur_team = by_team[t];
            if (sz(cur_team) <= 1) {
                cout << "-1\n";
            } else {
                int lo = *begin(cur_team);
                int hi = *rbegin(cur_team);

                bool ok = true;
                // check if there are any violations before
                if (lo != 0) {
                    /*cout << "qrying " << 0 << ' ' << lo-1 << endl;*/
                    auto lowest_snd = first_second.qry(0, lo-1);
                    /*cout << "lowest second is " << lowest_snd << endl;*/
                    /*rep(i, 0, lo) {*/
                    /*    cout << first_second.qry(i, i) << ' ';*/
                    /*}*/
                    /*cout << '\n';*/
                    if (lowest_snd < lo) {
                        ok = false;
                    }

                    auto highest_last = first_last.qry(0, lo-1);
                    /*cout << "highest last is " << highest_last << endl;*/
                    if (highest_last > hi) {
                        ok = false;
                    }
                }

                if (hi != n-1) {
                    auto lowest_first = last_first.qry(hi+1, n-1);
                    if (lowest_first < lo) {
                        ok = false;
                    }

                    auto highest_stl = last_stl.qry(hi+1, n-1);
                    if (highest_stl > hi) {
                        ok = false;
                    }
                }

                if (ok) {
                    int ans = 0;
                    if (lo != 0) {
                        ans += first_count_not_me.qry(0, lo-1);
                    }
                    if (hi != n-1) {
                        ans += last_count_not_me.qry(hi+1, n-1);
                    }
                    cout << ans << '\n';
                } else {
                    cout << "-1\n";
                }
            }
        }
    }

    /*rep(i, 0, n) {*/
    /*    cout << i << ": ";*/
    /*    for (auto x : by_team[i]) cout << x << ' ';*/
    /*    cout << endl;*/
    /*}*/
    /**/
    return 0;
}
