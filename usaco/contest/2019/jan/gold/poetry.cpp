#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#define ll long long
#define MOD 1000000007

using namespace std;

int n, m, k;
ll line_per_scheme[5001];
ll dp[5001];
ll type_count[26];
vector<pair<int, int>> words;

void mod(ll &res) {
    if (res > MOD) {
        res %= MOD;
    }
}

void calcTable() {
    dp[0] = 1;
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (i - words[j].first >= 0) {
                dp[i] += dp[i - words[j].first];
                mod(dp[i]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (k - words[i].first >= 0) {
            line_per_scheme[words[i].second] += dp[k - words[i].first];
            mod(line_per_scheme[words[i].second]);
        }
    }
}

ll modPow(ll num, ll exp) {
    if (exp == 1) {
        return num;
    }

    ll val = 0;
    if (exp % 2 == 0) {
        val = modPow(num, exp / 2);
        val *= val;
    } else {
        val = modPow(num, exp - 1) * num;
    }

    mod(val);
    return val;
}

ll calcExp(int count) {
    ll sum = 0;
    for (int i = 1; i <= 5000; i++) {
        if (line_per_scheme[i] != 0) {
            sum += modPow(line_per_scheme[i], count);
            mod(sum);
        }
    }

    return sum;
}

int main() {
    ifstream fin("poetry.in");
    ofstream fout("poetry.out");

    fin >> n >> m >> k;
    
    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        words.push_back({x, y});
    }

    for (int i = 0; i < m; i++) {
        char c; fin >> c;
        type_count[c - 'A']++;
    }

    calcTable();

    /*
    for (int i = 0; i <= 4; i++) {
        cout << dp[i] << endl;
    }
    */

    ll ans = 1;
    for (int i = 0; i < 26; i++) {
        if (type_count[i] > 0) {
            ans *= calcExp(type_count[i]);
            mod(ans);
        }
    }
    
    fout << ans << '\n';
    return 0;
}
