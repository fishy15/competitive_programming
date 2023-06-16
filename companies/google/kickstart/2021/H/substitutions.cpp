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
#include <list>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int inc(int v) {
    return (v + 1) % 10;
}

struct node {
    int val;
    node *prev, *next;

    node(int v) : val(v), prev(nullptr), next(nullptr) {}

    node *insert(int v) {
        node *n = new node(v);
        node *two = next;

        next = n;
        n->prev = this;

        if (two) {
            n->next = two;
            two->prev = n;
        }

        return n;
    }

    node *remove() {
        if (prev) {
            if (next) {
                prev->next = next;
                next->prev = prev;
            } else {
                prev->next = nullptr;
            }
        } else {
            if (next) {
                next->prev = nullptr;
            }
        }

        node *p = prev;
        prev = nullptr;
        next = nullptr;

        return p;
    }

    bool valid() {
        return prev != nullptr;
    }

    bool has_next() {
        return next != nullptr;
    }

    bool ok() {
        if (has_next()) {
            return inc(val) == next->val;
        }
        return false;
    }
};

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    node *front = new node(-2);
    node *cur = front;

    vector<set<node*>> change(10);
    for (int i = 0; i < n; i++) {
        cur = cur->insert(s[i] - '0');
    }

    cur = front->next;
    for (int i = 0; i < n - 1; i++) {
        if (cur->ok()) {
            change[cur->val].insert(cur);
        }
        cur = cur->next;
    }

    while (true) {
        vector<set<node*>> nxt_change(10);
        bool cont = false;
        for (int i = 0; i < 10; i++) {
            for (auto ptr : change[i]) {
                if (ptr->valid() && ptr->ok()) {
                    int v = ptr->val;
                    ptr->next->remove();
                    node *p = ptr->remove();

                    node* nxt = p->insert(inc(inc(v)));

                    if (p->ok()) {
                        if (p->val < i) {
                            nxt_change[p->val].insert(p);
                            cont = true;
                        } else {
                            change[p->val].insert(p);
                        }
                    }

                    if (nxt->ok()) {
                        if (p->val < i) {
                            nxt_change[nxt->val].insert(nxt);
                            cont = true;
                        } else {
                            change[nxt->val].insert(nxt);
                        }
                    }
                }
            }
        }

        change.swap(nxt_change);
        if (!cont) break;
    }

    cur = front->next;
    while (cur) {
        cout << cur->val;
        cur = cur->next;
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
