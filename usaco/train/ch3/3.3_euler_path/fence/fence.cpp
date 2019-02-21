/*
ID: aaryan.1
TASK: fence
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n;
int connect[500][500];
int num_edge[500];
vector<int> ans;

void dfs(int loc) {
    if (num_edge[loc] > 0) {
        for (int i = 0; i < 500; i++) {
            if (connect[loc][i] != 0) {
                connect[loc][i]--;;
                connect[i][loc]--;

                num_edge[loc]--;
                num_edge[i]--;

                dfs(i);
            }
        }
    }

    ans.insert(ans.begin(), loc + 1);
}

int main() {
    ifstream fin("fence.in");
    ofstream fout("fence.out");

    int n; fin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; fin >> a >> b;
        connect[a - 1][b - 1]++;
        connect[b - 1][a - 1]++;  

        num_edge[a - 1]++;
        num_edge[b - 1]++;
    }

    //cout << num_edge[0] << ' ' << num_edge[1] << '\n';

    // see if we need to start in a specific spot
    int start = -1;
    for (int i = 0; i < 500; i++) {
        //cout << "num: " << i << ' ' << num_edge[i] << endl;
        if (num_edge[i] > 0 && start == -1) {
            start = i;
        }

        if (num_edge[i] % 2 == 1) {
            start = i;
            break;
        }
    }

    //cout << start << '\n';
    dfs(start);

    for (int i : ans) {
        fout << i << '\n';
    }

    return 0;
}