#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> graph;
vector<vector<int>> regionNum;
vector<int> count2;
int curTot;
int n;

void floodfill(int i, int j, int num) {
    //cout << i << ' ' << j << endl;
    regionNum[i][j] = num;
    curTot++;

    if (i > 0 && regionNum[i - 1][j] == 0 && graph[i][j] == graph[i - 1][j]) {
        floodfill(i - 1, j, num);
    }

    if (i < n - 1 && regionNum[i + 1][j] == 0 && graph[i][j] == graph[i + 1][j]) {
        floodfill(i + 1, j, num);
    }

    if (j > 0 && regionNum[i][j - 1] == 0 && graph[i][j] == graph[i][j - 1]) {
        floodfill(i, j - 1, num);
    }

    if (j < 9 && regionNum[i][j + 1] == 0 && graph[i][j] == graph[i][j + 1]) {
        floodfill(i, j + 1, num);
    }
}

void drop() {
    for (int j = 0; j < 10; j++) {
        vector<char> s;
        for (int i = 0; i < n; i++) {
            s.push_back(graph[i][j]);
        }

        for (int i = n - 1; i >= 0; i--) {
            int pos = i + 1;
            while (pos < n && s[pos] == '0') {
                pos++;
            }
            
            if (pos - 1 != i) {
                s[pos - 1] = s[i];
                s[i] = '0';
            }
        }
        
        for (int i = 0; i < n; i++) {
            graph[i][j] = s[i];
        }
    }
}

int main() {
    ifstream fin("mooyomooyo.in");
    ofstream fout("mooyomooyo.out");

    int k; fin >> n >> k;
    graph = vector<string>(n);

    for (int i = 0; i < n; i++) {
        fin >> graph[i];
    }

    regionNum = vector<vector<int>>(n, vector<int>(10, 0));
    bool cont = true;
    while (cont) {
        cont = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 10; j++) {
                regionNum[i][j] = 0;
            }
        }

        count2 = vector<int>();
        count2.push_back(-1);
        int regPos = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 10; j++) {
                if (!regionNum[i][j]) {
                    curTot = 0;
                    floodfill(i, j, regPos);
                    count2.push_back(curTot);
                    regPos++;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 10; j++) {
                if (count2[regionNum[i][j]] >= k && graph[i][j] != '0') {
                    cont = true;
                    graph[i][j] = '0';
                }
            }
        }

        drop();
    }

    for (int i = 0; i < n; i++) {
        fout << graph[i] << endl;
    }

    return 0;
}
