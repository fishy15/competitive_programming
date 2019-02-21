#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef long long ll;

using namespace std;

int main() {
    ifstream fin("diamond.in");
    ofstream fout("diamond.out");

    int N, K; fin >> N >> K;
    vector<ll> diamonds;

    for (int i = 0; i < N; i++) {
        ll sz; fin >> sz;
        diamonds.push_back(sz);
    }

    sort(diamonds.begin(), diamonds.end());

    int upper = 0;
    int max = 0;

    /*
    for (ll i : diamonds) {
        cout << i << '\n';
    }
    */

    for (int i = 0; i < N; i++) {
        while (upper < N - 1 && diamonds[upper + 1] - diamonds[i] <= 2*K) {
            upper++;
        }

        int val = upper - i + 1;
        max = max > val ? max : val;
    }

    fout << max << '\n';
    return 0;
}