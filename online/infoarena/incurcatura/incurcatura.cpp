#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

typedef struct node node;
struct node {
    set<int> connect;
};

int main() {
    ifstream fin("incurcatura.in");
    ofstream fout("incurcatura.out");

    int p, n; fin >> p >> n;
    vector<node> graph;

    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        node n;
        for (int j = 0; j < x; j++) {
            int y; fin >> y;
            n.connect.insert(y - 1);
        }

        graph.push_back(n);
    }

    vector<pair<int, int> > count;

    for (int i = 0; i < n; i++) {
        count.push_back(make_pair(0, i));
    }

    for (int i = 1; i < n; i++) {
        for (int j : graph[i].connect) {
            if (!graph[j].connect.count(i)) {
                    count[j].first += 2;
                    count[i].first += 1;
            }
        }
    }

    sort(count.rbegin(), count.rend());

    /*
    for (auto p : count) {
        cout << p.first << ' ' << p.second << '\n';
    }
    */

    if (p == 1) {
        fout << count[0].second + 1;
    } else {
        int val1 = count[0].second;
        int val2 = count[1].second;

        int mini = val1 < val2 ? val1 : val2;
        int maxi = val1 > val2 ? val1 : val2;

        fout << mini + 1 << ' ' << maxi + 1;
    }

    fout << endl;
    return 0;
}
