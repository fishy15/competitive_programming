#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

typedef struct group group;
struct group {
    int val;
    set<int> connect;
};

int n;
int board[250][250];
bool visited[250][250];
vector<group> groups;

int main() {
    ifstream fin("multimoo.in");
    ofstream fout("multimoo.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> board[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                
            }
        }
    }

    return 0;
}