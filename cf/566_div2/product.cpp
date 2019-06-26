// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eed:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinx:
// :pray: :eyg:
// :pray: :evan:
// :pray: :cj:
// :pray: :steph:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :vmaddur:
// :pray: :dorijanko:
// :pray: :gaming:
// :pray: :kassuno:
// :pray: :hyacinth:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:
// :pray: :jony:
// :pray: :kage:
// :pray: :ghost:
// :pray: :aha:
// :pray: :coolguy:
// :pray: :imax:
// :pray: :howlet:
// :pray: :darren:

#include <iostream>
#include <fstream>
#include <vector>
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

vector<vector<ll>> matrix_mult(vector<vector<ll>> m1, vector<vector<ll>> m2) {
    vector<vector<ll>> ans;

    for (ll i = 0; i < m1.size(); i++) {
        vector<ll> row;
        for (ll j = 0; j < m2[0].size(); j++) {
            ll sum = 0;
            for (ll a = 0; a < m1[0].size(); a++) {
                sum += m1[i][a] * m2[a][j];
                if (sum > MOD) {
                    sum -= MOD;
                }
            }
            
            row.push_back(sum);
        }

        ans.push_back(row);
    }

    return ans;
}

vector<vector<ll>> matrix_expo(vector<vector<ll>> m, ll n) {
    if (n == 1) {
        return m;
    }

    vector<vector<ll>> temp = matrix_expo(m, n / 2);

    if (n % 2 == 0) {
        return matrix_mult(temp, temp);
    }

    return matrix_mult(matrix_mult(temp, temp), m);
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    return 0;
}
