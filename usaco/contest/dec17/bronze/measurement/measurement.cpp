#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

typedef struct measure measure;
struct measure {
    int day;
    int id;
    int change;
};

int N, G;
vector<measure> m;

int main() {
    ifstream fin("measurement.in");
    ofstream fout("measurement.out");

    fin >> N >> G;
    for (int i = 0; i < N; i++) {
        int a, b, c; fin >> a >> b >> c;
        measure x;
        x.day = a;
        x.id = b;
        x.change = c;
        m.push_back(x);
    }

    sort(m.begin(), m.end(), [](const measure &a, const measure &b) {
        return a.day < b.day;
    });

    int curMax = 0;
    for (int i = 0; i < N; i++) {
        
    }
}
