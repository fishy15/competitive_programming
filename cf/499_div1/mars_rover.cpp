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

struct node {
    // ans = 0, or = 1, xor = 2, not = 3, in = 4
    int op;
    int a, b;
    int val;
    int norm;
    int flip;
    node() { memset(this, 0, sizeof(node)); };
};

vector<int> inp;
node arr[MAXN];

void dfs1(int v) {
    int a = arr[v].a;
    int b = arr[v].b;
    if (arr[v].op == 0) {
        dfs1(a);
        dfs1(b);
        arr[v].val = arr[a].val && arr[b].val;
    } else if (arr[v].op == 1) {
        dfs1(a);
        dfs1(b);
        arr[v].val = arr[a].val || arr[b].val;
    } else if (arr[v].op == 2) {
        dfs1(a);
        dfs1(b);
        arr[v].val = arr[a].val ^ arr[b].val;
    } else if (arr[v].op == 3) {
        dfs1(a);
        arr[v].val = !arr[a].val;
    } else if (arr[v].op == 4) {
        arr[v].val = a;
    }
}

void dfs2(int v) {
    int a = arr[v].a;
    int b = arr[v].b;
    /* cout << v << ' ' << arr[v].val << ' ' << arr[v].norm << ' ' << arr[v].flip << ' ' << arr[v].op << ' ' << a << ' ' << b << '\n'; */
    if (arr[v].op == 0) {
        if ((!(arr[a].val) && arr[b].val) != arr[v].val) {
            arr[a].flip = arr[v].flip;
        } else {
            arr[a].flip = arr[v].norm;
        }
        if ((!(arr[b].val) && arr[a].val) != arr[v].val) {
            arr[b].flip = arr[v].flip;
        } else {
            arr[b].flip = arr[v].norm;
        }
        arr[a].norm = arr[v].norm;
        arr[b].norm = arr[v].norm;
        dfs2(a);
        dfs2(b);
    } else if (arr[v].op == 1) {
        if ((!(arr[a].val) || arr[b].val) != arr[v].val) {
            arr[a].flip = arr[v].flip;
        } else {
            arr[a].flip = arr[v].norm;
        }
        if ((!(arr[b].val) || arr[a].val) != arr[v].val) {
            arr[b].flip = arr[v].flip;
        } else {
            arr[b].flip = arr[v].norm;
        }
        arr[a].norm = arr[v].norm;
        arr[b].norm = arr[v].norm;
        dfs2(a);
        dfs2(b);
    } else if (arr[v].op == 2) {
        if ((!(arr[a].val) ^ arr[b].val) != arr[v].val) {
            arr[a].flip = arr[v].flip;
        } else {
            arr[a].flip = arr[v].norm;
        }
        if ((!(arr[b].val) ^ arr[a].val) != arr[v].val) {
            arr[b].flip = arr[v].flip;
        } else {
            arr[b].flip = arr[v].norm;
        }
        arr[a].norm = arr[v].norm;
        arr[b].norm = arr[v].norm;
        dfs2(a);
        dfs2(b);
    } else if (arr[v].op == 3) {
        arr[a].flip = arr[v].flip;
        arr[a].norm = arr[v].norm;
        dfs2(a);
    } 
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        if (s == "AND") {
            arr[i].op = 0;
            cin >> arr[i].a >> arr[i].b;
        } else if (s == "OR") {
            arr[i].op = 1;
            cin >> arr[i].a >> arr[i].b;
        } else if (s == "XOR") {
            arr[i].op = 2;
            cin >> arr[i].a >> arr[i].b;
        } else if (s == "NOT") {
            arr[i].op = 3;
            cin >> arr[i].a;
        } else {
            arr[i].op = 4;
            cin >> arr[i].a;
            inp.push_back(i);
        }
    }

    dfs1(1);
    arr[1].flip = !arr[1].val;
    arr[1].norm = arr[1].val;
    dfs2(1);

    string ans = "";
    for (auto x : inp) {
        ans += (arr[x].flip + '0');
    }
    cout << ans << '\n';

    return 0;
}
