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

struct creature {
    int p1, p2;
    int c;
};

struct status {
    bool known;
    int val;
};

bool is_set(int msk, int x) {
    return ((msk >> x) & 1) != 0;
}

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<creature> creats(n);
    rep(i, 0, n) {
        char c;
        cin >> creats[i].p1 >> creats[i].p2 >> c;
        creats[i].p1--;
        creats[i].p2--;
        creats[i].c = (int) (c - 'a');
    }

    auto check_mask = [&](int msk) -> optional<vector<string>> {
        vector<pair<int, status>> colors(n, {-1, status{false, 0}});
        rep(i, 0, n) {
            colors[i].first = creats[i].c;
            colors[i].second.val = creats[i].c;
        }

        auto set_color = [&](int idx, int c) {
            if (c < colors[idx].first) {
                return false;
            } else if (c > colors[idx].first) {
                if (colors[idx].second.known) {
                    return colors[idx].second.val == c;
                } else {
                    if (colors[idx].second.val <= c) {
                        colors[idx].second.known = true;
                        colors[idx].second.val = c;
                    } else {
                        return false;
                    }
                }
            }
            return true;
        };

        auto set_bound = [&](int idx, int c) {
            if (c <= colors[idx].first) {
                return true;
            } else if (colors[idx].second.known) {
                return c <= colors[idx].second.val;
            } else {
                ckmax(colors[idx].second.val, c);
                return true;
            }
        };

        for (int i = n-1; i >= 0; i--) {
            if (creats[i].p1 != -1) {
                if (is_set(msk, i)) {
                    if (!set_color(creats[i].p1, creats[i].c)) {
                        return {};
                    }
                    if (colors[i].second.known) {
                        if (!set_color(creats[i].p2, colors[i].second.val)) {
                            return {};
                        }
                    } else {
                        if (!set_bound(creats[i].p2, colors[i].second.val)) {
                            return {};
                        }
                    }
                } else {
                    if (!set_color(creats[i].p2, creats[i].c)) {
                        return {};
                    }
                    if (colors[i].second.known) {
                        if (!set_color(creats[i].p1, colors[i].second.val)) {
                            return {};
                        }
                    } else {
                        if (!set_bound(creats[i].p1, colors[i].second.val)) {
                            return {};
                        }
                    }
                }
            }
        }

        rep(i, 0, n) {
            if (creats[i].p1 != -1 && !colors[i].second.known) {
                int p;
                if (is_set(msk, i)) {
                    p = creats[i].p2;
                } else {
                    p = creats[i].p1;
                }

                if (colors[p].first >= colors[i].second.val) {
                    colors[i].second.val = colors[p].first;
                } else {
                    colors[i].second.val = colors[p].second.val;
                }
            }
        }

        vector<string> res;
        rep(i, 0, n) {
            string cur;
            cur += (char) ('a' + colors[i].first);
            cur += (char) ('a' + colors[i].second.val);
            res.push_back(cur);
        }
        return res;
    };

    optional<vector<string>> ans;
    rep(msk, 0, 1 << n) {
        auto res = check_mask(msk);
        if (res) {
            if (ans) {
                *ans = min(*ans, *res);
            } else {
                ans = res;
            }
        }
    }

    if (ans) {
        for (auto &s : *ans) {
            cout << s << '\n';
        }
    } else {
        cout << "-1\n";
    }

    return 0;
}
