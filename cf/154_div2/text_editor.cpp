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
#define INF 0x3f3f3f3f

using namespace std;

int n;
vector<int> lines;
int r1, c1, r2, c2;

void move(int& pos, int goal) {
    if (pos > goal) {
        pos--;
    } else {
        pos++;
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> n;
    
    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        lines.push_back(x);
    }

    fin >> r1 >> c1 >> r2 >> c2;
    r1--;
    c1--;
    r2--;
    c2--;

    int ans = INF;

    for (int mid = 0; mid < n; mid++) {
        int col = c1;
        int steps = 0;

        for (int pos = r1; pos != mid; move(pos, mid)) {
            col = min(col, lines[pos]);
            steps++;
        }

        for (int pos = mid; pos != r2; move(pos, r2)) {
            col = min(col, lines[pos]);
            steps++;
        }

        col = min(col, lines[r2]);
        steps += abs(col - c2);

        ans = min(steps, ans);
    }

    fout << ans << '\n';

    return 0;
}
