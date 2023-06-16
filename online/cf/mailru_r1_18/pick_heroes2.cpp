#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct hero hero;
struct hero {
    int pos;
    int power;
    bool picked;
    hero* pair;
};

int main() {
    int n, m; cin >> n >> m;
    vector<hero> heroes = vector<hero>(2*n + 1);

    for (int i = 1; i <= 2*n; i++) {
        cin >> heroes[i].power;
        heroes[i].picked = false;
        heroes[i].pos = i;
        heroes[i].pair = nullptr;
    }

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        heroes[a].pair = &heroes[b];
        heroes[b].pair = &heroes[a];
    }

    sort(heroes.begin(), heroes.end(), [](const hero &a, const hero &b) {
        return a.power < b.power;
    });

    int index = 2 * n;
    int prev = -1;

    int t; cin >> t;
    if (t == 2) {
        cin >> prev;
        if (prev == -1) {
            return 0;
        }

        for (int i = 0; i <= 2 * n - 1; i++) {
            if (heroes[i].pos == prev) {
                prev = i;
            }
        }

        heroes[prev].picked = true;
    }

    for (int i = 0; i < n; i++) {
        /*
        for (auto h : heroes) {
            cout << h.picked << ' ';
        } cout << endl;
        */
        bool needed = true;
        if (prev >= 0 && heroes[prev].pair != nullptr) {
            needed = false;
            int partner = heroes[prev].pair->pos;
            if (!heroes[partner].picked) {
                cout << partner << '\n';
                cout.flush();
            } else {
                needed = true;
            }

            heroes[partner].picked = true;
        }
        
        if (needed) {
            while (heroes[index].picked) {
                index--;
            }

            cout << heroes[index].pos << '\n';
            cout.flush();

            //cout << index << " is picked\n";
            heroes[index].picked = true;
            //cout << index << " PICKED\n";
        }

        cin >> prev;

        if (prev == -1) {
            return 0;
        }

        for (int i = 1; i <= 2 * n; i++) {
            if (heroes[i].pos == prev) {
                prev = i;
            }
        }

        heroes[prev].picked = true;
    }

    return 0;
}
