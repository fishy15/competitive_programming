#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct barn barn;
struct barn {
    bool open;
    bool visited;
    vector<bool> connect;

    barn(int sz) {
        connect = vector<bool>(sz, false);
        open = true;
        visited = false;
    }
};

int N, M;
vector<barn> barns;
int count;

void reset() {
    for (int i = 0; i <= N; i++) {
        barns[i].visited = false;
    }

    ::count = 0;
}

void floodfill(int x) {
    //cout << x << '\n';
    ::count++;
    barns[x].visited = true;
    for (int i = 0; i <= N; i++) {
        if (barns[x].connect[i] == true && !barns[i].visited && barns[i].open) {
            floodfill(i);

            // the purpose of having a zeroth barn is to be lazy to find the first unopened barn
            if (x == 0) {
                break;
            }
        }
    }
}

int main() {
    ifstream fin("closing.in");
    ofstream fout("closing.out");

    fin >> N >> M;

    for (int i = 0; i <= N; i++) {
        barns.push_back(barn(N + 1));

        if (i > 0) {
            barns[i].connect[0] = true;
            barns[0].connect[i] = true;
        }
    }

    for (int i = 0; i < M; i++) {
        int x, y; fin >> x >> y;
        barns[x].connect[y] = true;
        barns[y].connect[x] = true;
    }

    for (int i = 0; i < N; i++) {
        //cout << "stage " << i << endl;
        floodfill(0);

        if (::count == N + 1 - i) {
            fout << "YES\n";
        } else {
            fout << "NO\n";
        }

        reset();
        
        int off; fin >> off;
        barns[off].open = false;
    }

    return 0;
}