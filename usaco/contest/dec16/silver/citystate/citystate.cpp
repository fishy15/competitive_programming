#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define ll long long

using namespace std;

string rev(string s) {
    return s.substr(2, 2) + s.substr(0, 2);
}

int main() {
    ifstream fin("citystate.in");
    ofstream fout("citystate.out");

    ll n; fin >> n;
    map<string, ll> m;
    for (int i = 0; i < n; i++) {
        string city, state; fin >> city >> state;
        string key = city.substr(0, 2) + state;
        m[key]++;
    }

    ll val = 0;
    for (auto &p : m) {
        string r = rev(p.first);
        if (r != p.first) {
            val += p.second * m[r];
        } 
    }

    fout << val / 2 << '\n';
    return 0;
}