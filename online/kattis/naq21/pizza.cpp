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
#include <unordered_set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>
#include <sstream>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

vector<int> or_imp[MAXN];
vector<pair<vector<int>, int>> and_imp;
map<string, int> var;
vector<int> added;
bool in[MAXN];
int ans;

int get_var(string s) {
    static int cnt = 0;
    if (!var.count(s)) {
        var[s] = cnt++;
    }
    return var[s];
}

void add(int x) {
    if (in[x]) return;
    in[x] = true;
    ans++;

    for (int y : or_imp[x]) {
        add(y);
    }

    for (auto &[v, y] : and_imp) {
        bool all_in = true;

        for (int a : v) {
            if (!in[a]) {
                all_in = false;
                break;
            }
        }

        if (all_in) {
            add(y);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int c; cin >> c;

    string trash; getline(cin, trash); // '\n' on first line

    for (int i = 0; i < c; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);

        string first; ss >> first;
        if (first == "if") {
            vector<int> before;
            bool is_and = false;

            string cur = "";
            while (true) {
                ss >> cur;
                if (cur == "then") break;
                if (cur == "and") { 
                    is_and = true;
                } else if (cur != "or") {
                    before.push_back(get_var(cur)); 
                }
            }

            sort(before.begin(), before.end());
            before.erase(unique(before.begin(), before.end()), before.end());

            string last; ss >> last;
            int last_v = get_var(last);

            if (is_and) {
                and_imp.emplace_back(before, last_v);
            } else {
                for (int x : before) {
                    or_imp[x].push_back(last_v);
                }
            }
        } else {
            added.push_back(get_var(first));
        }
    }

    for (int y : added) {
        add(y);
    }
    
    cout << ans << '\n';

    return 0;
}
