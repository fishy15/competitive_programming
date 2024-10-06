#include <bits/stdc++.h>

using ll = __int128;
using namespace std;

struct data {
    ll num_left;
    ll const_num;
    ll last_div;

    bool operator<(const data &other) const {
        if (num_left == other.num_left) {
            if (const_num == other.const_num) {
                return last_div > other.last_div;
            }
            return const_num > other.const_num;
        }
        return num_left < other.num_left;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int b;
    cin >> b;

    long long np;
    cin >> np;
    __int128 n = np;

    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    priority_queue<struct data> pq;
    map<ll, struct data> ans;

    ans[n] = {n, 0, 0};
    pq.push({n, 0, 0});

    vector<ll> divs;
    for (int d = 2; d < b; d++) {
        if (n % d == 0) {
            divs.push_back(d);
        }
    }

    __int128 bound = 1;
    for (int i = 0; i < 64; i++) bound *= 2;

    reverse(divs.begin(), divs.end());

    while (!pq.empty()) {
        auto [num_left, const_num, lst_dig] = pq.top();
        pq.pop();

        if (ans[num_left].const_num != const_num) continue;

        if (num_left == 1) {
            cout << (long long) const_num << '\n';
            return 0;
        } else {
            for (auto d : divs) {
                if (d < lst_dig) break;
                if (num_left % d == 0) {
                    auto new_left = num_left / d;
                    auto new_constr = const_num * b + d;
                    if (new_constr >= bound) continue;

                    struct data nxt{new_left, new_constr, d};
                    if (!ans.count(new_left) || ans[new_left] < nxt) {
                        ans[new_left] = nxt;
                        pq.push(nxt);
                    }
                }
            }
        }
    }

    cout << "impossible\n";

    return 0;
}
