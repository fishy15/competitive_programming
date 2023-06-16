// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> empty;
    priority_queue<array<int, 3>> not_empty;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        empty.push({x, i});
    }

    string s; cin >> s;
    int ppl = (int)(s.size());

    for (int i = 0; i < ppl; i++) {
        if (s[i] == '0') {
            pair<int, int> top = empty.top();
            cout << top.second + 1 << ' ';
            not_empty.push({top.first, top.second, 1});
            empty.pop();
        } else {
            array<int, 3> top = not_empty.top();
            cout << top[1] + 1 << ' ';
            top[2]++;
            not_empty.pop();
        }
    }

    return 0;
}
