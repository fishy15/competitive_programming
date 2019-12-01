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
    //cin.tie(0); ios::sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<string> pin;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            pin.push_back(s);
        }
        int ans = 0;
        set<char> hmm = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        for (int i = 0; i < n; i++) {
            if (hmm.count(pin[i][0])) {
                hmm.erase(pin[i][0]);
            }
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (pin[i] == pin[j]) {
                    pin[i][0] = *(hmm.begin());
                    hmm.erase(pin[i][0]);
                    ans++;
                }
            }
        }

        cout << ans << '\n';
        for (string s : pin) { 
            cout << s << '\n';
        }
    }

    return 0;
}
