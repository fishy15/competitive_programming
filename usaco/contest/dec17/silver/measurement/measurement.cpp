#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

typedef struct entry entry;
struct entry {
    int day;
    int id;
    int change;
};

int main() {
    ifstream fin("measurement.in");
    ofstream fout("measurement.out");

    int n; fin >> n;
    vector<entry> entries;
    for (int i = 0; i < n; i++) {
        int a, b, c; fin >> a >> b >> c;
        entry e;
        e.day = a;
        e.id = b;
        e.change = c;

        entries.push_back(e);
    }

    sort(entries.begin(), entries.end(), [](const entry &e1, const entry &e2) {
        return e1.day < e2.day;
    });


}
