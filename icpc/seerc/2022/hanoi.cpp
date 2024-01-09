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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> moves;

    vector<int> p(n);
    for (auto &x : p) {
        cin >> x;
    }

    vector<int> third;
    for (int i = n - 1; i >= 0; i--) {
        vector<int> tmp;
        moves.push_back({1, 2});
        while (!third.empty() && third.back() < p[i]) {
            tmp.push_back(third.back());
            third.pop_back();
            moves.push_back({3, 1});
        }
        moves.push_back({2, 3});
        third.push_back(p[i]);
        while (!tmp.empty()) {
            third.push_back(tmp.back());
            tmp.pop_back();
            moves.push_back({1, 3});
        }
    }

    cout << moves.size() << '\n';
    for (auto [a, b] : moves) {
        cout << a << ' ' << b << '\n';
    }

    return 0;
}
