#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct boot boot;
struct boot {
    int depth;
    int step;
};

typedef struct pos pos;
struct pos {
    int boot_index;
    int tile_index;
};

int n, b; 
vector<int> tiles;
vector<boot> boots;

int main() {
    ifstream fin("snowboots.in");
    ofstream fout("snowboots.out");

    int n, b; fin >> n >> b;
    vector<int> tiles;
    vector<boot> boots;

    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        d.push_back(x);
    }

    for (int i = 0; i < b; i++) {
        int x, y; fin >> x >> y;
        boot a; 
        a.depth = x;
        a.step = y;
        boots.push_back(a);
    }
}
