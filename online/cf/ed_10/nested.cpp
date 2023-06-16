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

class BIT {
public:
    vector<int> bit;
    
    int get_max_one(int n) {
        return n & (~n + 1);
    }

    BIT(int sz) {
        bit = vector<int>(sz + 1, 0);
    }

    int get_before(int i) {
        int sum = 0;
        
        while (i > 0) {
            sum += bit[i];
            i -= get_max_one(i);
        }

        return sum;
    }

    void add(int i) {
        while (i < bit.size()) {
            bit[i]++;
            i += get_max_one(i);
        }
    }
};

int n;
vector<pair<int, int>> lines;

/*
 * sort by size
 * 5 types of lines
 * 
 * 1. before to before line
 * 2. before to inside line
 * 3. inside to inside line
 * 4. inside to after  line
 * 5. after  to after  line
 *
 * use start BIT and end BIT
 * 
 */

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        lines.push_back({x, y});
    }


    return 0;
}
