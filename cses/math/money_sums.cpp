// :pray: :fishy:

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
#define MAXN 100000

using namespace std;

int arr[MAXN + 1];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    vector<int> coins;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        coins.push_back(x);
    }

    arr[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = MAXN; j >= coins[i]; j--) {
            if (arr[j - coins[i]]) {
                arr[j] = 1;
            }
        }
    }

    vector<int> ans;
    int cnt = 0;
    for (int i = 1; i <= MAXN; i++) {
        if (arr[i]) {
            cnt++;
            ans.push_back(i);
        }
    }

    cout << cnt << '\n';

    for (int &i : ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
