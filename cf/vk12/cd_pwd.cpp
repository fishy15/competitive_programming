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

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#include <sstream>

#define ll long long
#define eps 1e-8
#define MOD 10000007

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    vector<string> stack;
    int t; cin >> t;

    for (int i = 0; i < t; i++) {
        string cmd; cin >> cmd;

        if (cmd == "pwd") {
            cout << '/';
            for (string s : stack) {
                cout << s << '/';
            }
            cout << '\n';
        } else {
            string path; cin >> path;
            stringstream ss(path);
            string token;

            if (path[0] == '/') {
                stack = vector<string>();
            }

            while(getline(ss, token, '/')) {
                if (token.size() > 0) {
                    if (token == "..") {
                        stack.pop_back();
                    } else {
                        stack.push_back(token);
                    }
                }
            }
        }
    }

    return 0;
}
