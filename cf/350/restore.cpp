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

vector<int> cnt(10);
string s;
string sub;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s >> sub;

    if (s == "01" || s == "10") {
        cout << 0 << '\n';
        return 0;
    }

    for (char c : s) {
        cnt[c - '0']++;
    }

    for (int i = 1; i <= 1000000; i++) {
        string chk = to_string(i);
        if (chk.size() + i != s.size()) continue;
        vector<int> cntc(cnt); 
        bool bad = false;

        for (char c : chk) {
            if (cntc[c - '0']) {
                cntc[c - '0']--;
            } else {
                bad = true;
                break;
            }
        }
        if (bad) continue;

        for (char c : sub) {
            if (cntc[c - '0']) {
                cntc[c - '0']--;
            } else {
                bad = true;
                break;
            }
        }
        if (bad) continue;

        // check if 0
        int tot = 0;
        for (int j = 0; j < 10; j++) tot += cntc[j];
        if (cntc[0] == tot) {
            int cc = cntc[0];
            int tot2 = tot;
            for (char c : sub) {
                if (c == '0') cc++;
                tot2++;
            }
            if (cc == tot2) continue;
            cout << sub;
            for (int i = 0; i < cntc[0]; i++) cout << '0';
            cout << '\n';
        } else {
            string ans1 = "";
            string ans2 = "";
            // first digit
            ans2 += sub;
            int rem = -1;
            if (cntc[0] || sub[0] == '0') {
                for (int j = 1; j < 10; j++) {
                    if (cntc[j]) {
                        ans1 += to_string(j);
                        cntc[j]--;
                        rem = j;
                        break;
                    }
                }
            }
            for (int j = 0; j < 10; j++) {
                if (j == sub[0] - '0') {
                    string ok = "";
                    for (int k = 0; k < sub.size(); k++) {
                        ok += to_string(j);
                    }
                    if (sub <= ok) {
                        ans1 += sub;
                    }
                    for (int k = 0; k < cntc[j]; k++) {
                        ans1 += to_string(j);
                        ans2 += to_string(j);
                    }
                    if (sub > ok) {
                        ans1 += sub;
                    }
                } else {
                    for (int k = 0; k < cntc[j]; k++) {
                        ans1 += to_string(j);
                        ans2 += to_string(j);
                    }
                }
                if (j == rem) ans2 += to_string(j);
            }
            string s1 = min(ans1, ans2);
            string s2 = max(ans1, ans2);
            if (s1.size() != i || s1[0] == '0') {
                cout << s2 << '\n';
            } else {
                cout << s1 << '\n';
            }
        }
    }

    return 0;
}
