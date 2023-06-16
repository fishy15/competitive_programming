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

#define ll long long
#define eps 1e-8
#define MOD 10000007

using namespace std;

int n; 
priority_queue<int> a;
priority_queue<int> b;
priority_queue<int> none;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;

    int min_count = 0;
    int count = 0;
    int sum = 0;

    for (int i = 0; i < n; i++) {
        string s; int inf;
        cin >> s >> inf;
        if (s == "11") {
            min_count++;
            count++;
            sum += inf;
        } else if (s == "10") {
            a.push(inf);
        } else if (s == "01") {
            b.push(inf);
        } else {
            none.push(inf);
        }
    }

    while (a.size() > 0 && b.size() > 0) {
        min_count++;
        count += 2;
        sum += a.top();
        sum += b.top();

        a.pop();
        b.pop();
    }

    //cout << min_count << ' ' << count << '\n';
    if (a.empty()) {
        a.swap(b);
    }

    //cout << sum << '\n';

    while ((a.size() > 0 || none.size() > 0) && 2 * min_count > count) {
        if (a.empty()) {
            sum += none.top();             
            none.pop();
        } else if (none.empty()) {
            sum += a.top();
            a.pop();
        } else {
            int val1 = a.top();
            int val2 = none.top();

            if (val1 > val2) {
                sum += val1;
                a.pop();
            } else {
                sum += val2;
                none.pop();
            }
        }

        //cout << 2 * min_count + 2 << ' ' << count << '\n';
        count++;
    }

    cout << sum << '\n';
    return 0;
}
