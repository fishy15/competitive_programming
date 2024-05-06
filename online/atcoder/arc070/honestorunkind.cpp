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

bool says_kind(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    char res;
    cin >> res;
    return res == 'Y';
}

void answer(const vector<bool> &ans) {
    cout << "! ";
    for (auto b : ans) {
        cout << b;
    }
    cout << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int a, b;
    cin >> a >> b;

    int n = a + b;

    if (a <= b) {
        cout << "Impossible" << endl;
    } else {
        vector<int> honest_chain;
        for (int i = 0; i < n; i++) {
            if (honest_chain.empty() || says_kind(honest_chain.back(), i)) {
                honest_chain.push_back(i);
            } else {
                honest_chain.pop_back();
            }
        }

        vector<bool> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = says_kind(honest_chain.back(), i);
        }

        answer(ans);
    }

    return 0;
}
