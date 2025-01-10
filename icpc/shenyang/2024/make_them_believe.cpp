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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

pair<int, string> read_team() {
    string s;
    int c;
    cin >> s >> c;
    return {c, s};
}

pair<int, string> read_set() {
    auto a = read_team();
    auto b = read_team();
    auto c = read_team();
    auto d = read_team();
    return max({a, b, c, d});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    auto t1 = read_set();
    auto t2 = read_set();
    if (t1.first > t2.first) {
        cout << t1.second << " beats " << t2.second << '\n';
    } else {
        cout << t2.second << " beats " << t1.second << '\n';
    }

    return 0;
}
