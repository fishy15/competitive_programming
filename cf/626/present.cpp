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

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n;
vector<int> nums;
int cnt[8];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    int ans = 0;

    for (int a = 0; a < 21; a++) {
        for (int i = 0; i < 8; i++) cnt[i] = 0;

        for (int i : nums) {
            int v = 0;
            v += 4 * (((1 << (a + 1)) & i) != 0);
            v += 2 * (((1 << a) & i) != 0);
            if (a > 0) {
                v += (((1 << (a - 1)) & i) != 0);
            }
            cnt[v]++;
        }

        for (int i = 0; i < 8; i++) {
            cout << cnt[i] << ' ';
            for (int j = i + 1; j < 8; j++) {
                int s = i + j;
                if ((cnt[i] * cnt[j]) % 2 == 1) {
                    int v = (s >> 1);
                    ans ^= v * (1 << a);
                } 
            }
        } cout << '\n';

        for (int i = 0; i < 8; i++) {
            int s = 2 * i;
            if ((cnt[i] * (cnt[i] - 1) / 2) % 2 == 1) {
                int v = (s >> 1);
                cout << s << ' ' << v << ' ' << a << '\n';
                ans ^= v * (1 << a);
            }
        }

        cout << '\t' << ans << '\n';
    }

    cout << ans << '\n';

    return 0;
}
