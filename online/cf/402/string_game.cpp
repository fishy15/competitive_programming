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

// plan
// bin search for how many chars to remove
// generate the string for that many chars and then check (linear time)

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
#define MOD 10000007

using namespace std;

string original;
string target;
int n;
vector<int> seq;

string remove(int);
bool check(int);

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> original >> target;
    n = (int)(original.size());

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        seq.push_back(x);
    }

    int low = 0;
    int high = n;
    int ans = -1;

    while (low < high) {
        //cerr << low << ' ' << high << '\n';
        int mid = (low + high) / 2;

        if (check(mid)) {
            low = mid + 1;
            ans = mid;
        } else {
            high = mid;
        }
    }

    //cerr << remove(4) << '\n';
    //cerr << check(4) << '\n';
    cout << ans << '\n';

    return 0;
}

string remove(int pos) {
    string s(original);
    for (int i = 0; i < pos; i++) {
        s[seq[i] - 1] = ' ';
    }

    string ans = "";
    for (char c : s) {
        if (c != ' ') {
            ans += c;
        }
    }

    return ans;
}

bool check(int pos) {
    string s = remove(pos);

    int check_pos = 0;

    for (int i = 0; i < n - pos; i++) {
        if (target[check_pos] == s[i]) {
            check_pos++;
        }

        if (check_pos == target.size()) {
            return true;
        }
    }

    return false;
}