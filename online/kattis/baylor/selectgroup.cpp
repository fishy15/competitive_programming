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
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>
#include <sstream>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

vector<string> names;
map<string, int> idx;
map<int, set<int>> grp;

vector<string> get_line() {
    vector<string> ans;

    if (cin) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cur;

        while (getline(ss, cur, ' ')) {
            if (cur != "") {
                ans.push_back(cur);
            }
        }
    }

    return ans;
}

int get_idx(string s) {
    if (!idx.count(s)) {
        idx[s] = names.size();
        names.push_back(s);
    }

    return idx[s];
}

void add_grp(const vector<string> &line) {
    string name = line[1];
    int n = stoi(line[2]);

    int name_idx = get_idx(name);

    for (int i = 0; i < n; i++) {
        string person = line[i + 3];
        int person_idx = get_idx(person);
        grp[name_idx].insert(person_idx);
    }
}

set<int> join(set<int> &s1, set<int> &s2) {
    if (s1.size() < s2.size()) swap(s1, s2);
    for (int x : s2) s1.insert(x);
    return s1;
}

set<int> inter(set<int> &s1, set<int> &s2) {
    if (s1.size() < s2.size()) swap(s1, s2);
    
    auto it = s1.begin();

    while (it != s1.end()) {
        if (!s2.count(*it)) {
            auto nxt = next(it);
            s1.erase(it);
            it = nxt;
        } else {
            it = next(it);
        }
    }

    return s1;
}

set<int> diff(set<int> &s1, set<int> &s2) {
    auto it = s1.begin();

    while (it != s1.end()) {
        if (s2.count(*it)) {
            auto nxt = next(it);
            s1.erase(it);
            it = nxt;
        } else {
            it = next(it);
        }
    }

    return s1;
}

set<int> solve(vector<string> &line, int &idx) {
    string &s = line[idx];
    idx++;

    if (s == "union") {
        auto s1 = solve(line, idx);
        auto s2 = solve(line, idx);
        return join(s1, s2);
    } else if (s == "intersection") {
        auto s1 = solve(line, idx);
        auto s2 = solve(line, idx);
        return inter(s1, s2);
    } else if (s == "difference") {
        auto s1 = solve(line, idx);
        auto s2 = solve(line, idx);
        return diff(s1, s2);
    } else {
        int x = get_idx(s);
        return grp[x];
    }
}

void answer_query(vector<string> &line) {
    int idx = 0;
    auto res = solve(line, idx);

    set<string> ans;
    for (int x : res) {
        ans.insert(names[x]);
    }

    for (string s : ans) {
        cout << s << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while (true) {
        auto line = get_line();
        if (line.empty()) break;

        if (line[0] == "group") {
            add_grp(line);
        } else {
            answer_query(line);
        }
    }

    return 0;
}
