// :pray: :arrayman:
// :pray: :summitosity:
// :pray: :pusheenosity:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk-duk-go:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eediosity:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinxiosity
// :pray: :eggyosity:
// :pray: :squares-are-fine:
// :pray: :see-jay:
// :pray: :stephiosity:
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

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct gap gap;
struct gap {
    int a, b;
    int len;
};

int n, m, k;
vector<int> nums;
vector<gap> tape;

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    for (int i = 0; i < n - 1; i++) {
        gap g;
        g.a = nums[i];
        g.b = nums[i+1];
        g.len = nums[i+1]-nums[i]-1;
        tape.push_back(g);
    }

    sort(tape.begin(), tape.end(), [](const gap &g1, const gap &g2) {
        return g1.len < g2.len;
    });

    int sum = 0;
    for (int i = 0; i < n - k; i++) {
        sum += tape[i].len;
    }

    sum += n;
    cout << sum << '\n';
    return 0;
}