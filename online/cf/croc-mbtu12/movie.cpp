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

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

#define MAXN 100000

using namespace std;

int n, k;
vector<int> movie;
int diff[MAXN + 1];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    cin >> n >> k;
    
    int last = -1;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x != last) {
            movie.push_back(x);
            last = x;
        }
    }
    
    for (int i = 1; i < movie.size() - 1; i++) {
        if (movie[i - 1] == movie[i + 1]) {
            diff[movie[i]] += 2;
        } else {
            diff[movie[i]]++;
        }
    }
    
    diff[movie[0]]++;
    diff[movie[movie.size() - 1]]++;

    int maxval = 0;
    int index = 0;
    for (int i = 1; i <= k; i++) {
        if (diff[i] > maxval) {
            maxval = diff[i];
            index = i;
        }
    }
    
    cout << index << '\n';
}
