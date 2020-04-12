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

#define ll long long
#define eps 1e-8
#define MOD 1000000007
#define MOD2 1000000009

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100000

using namespace std;

int n, k;
int nums[MAXN + 1];
bool done[MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    int cnt = 0;
    for (int i = 0; i <= n; i++) {
        string s; cin >> s;
        if (s != "?") {
            nums[i] = stoi(s);
            done[i] = true;
            cnt++;
        } 
    }

    if (k == 0) {
        if (done[0]) {
            if (nums[0]) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
            }
        } else {
            if (cnt % 2) {
                cout << "Yes\n";
            } else {
                cout << "No\n"; 
            }
        }
    } else {
        if (cnt == n + 1) {
            ll cur = nums[n];
            for (int i = n - 1; i >= 0; i--) {
                cur *= k;
                cur += nums[i];
                if (abs(cur) > 1000000000LL) {
                    cout << "No\n";
                    return 0;
                }
            }

            if (cur == 0) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else {
            if (n % 2) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}
