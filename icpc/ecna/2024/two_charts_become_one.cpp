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

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

map<int, int> get_tree(string s) {
    map<int, int> res;
    vector<int> par;

    string cur_num;
    s += '(';
    for (char c : s) {
        if ('0' <= c && c <= '9') {
            cur_num += c;
        } else {
            if (c == '(' || c == ')') {
                if (!cur_num.empty()) {
                    int num = stoi(cur_num);
                    cur_num = "";
                    int p = par.empty() ? -1 : par.back();
                    res[num] = p;
                    par.push_back(num);
                }

                if (c == ')') {
                    par.pop_back();
                }
            }
        }
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t;
    getline(cin, s);
    getline(cin, t);

    if (get_tree(s) == get_tree(t)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
