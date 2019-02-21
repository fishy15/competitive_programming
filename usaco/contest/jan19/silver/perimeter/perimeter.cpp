#include <iostream>
#include <fstream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

int n;
vector<string> grid;
vector<vector<bool>> visited;
vector<vector<pair<int, int>>> blobs;

void floodfill(int x, int y, int loc) {
    //cout << x << ' ' << y << ' ' << loc << endl;
    blobs[loc].push_back({x, y});
    visited[x][y] = true;

    if (x > 0 && !visited[x - 1][y] && grid[x - 1][y] == '#') {
        floodfill(x - 1, y, loc);
    }

    if (y > 0 && !visited[x][y - 1] && grid[x][y - 1] == '#') {
        floodfill(x, y - 1, loc);
    }

    if (x < n - 1&& !visited[x + 1][y] && grid[x + 1][y] == '#') {
        floodfill(x + 1, y, loc);
    }

    if (y < n - 1 && !visited[x][y + 1] && grid[x][y + 1] == '#') {
        floodfill(x, y + 1, loc);
    }
}

int get_peri(int i, int j) {
    int ans = 0;
    if (i == 0 || grid[i - 1][j] == '.') {
        ans++;
    }

    if (j == 0 || grid[i][j - 1] == '.') {
        ans++;
    }

    if (i == n - 1 || grid[i + 1][j] == '.') {
        ans++;
    }

    if (j == n - 1 || grid[i][j + 1] == '.') {
        ans++;
    }

    return ans;
}

int main() {
    ifstream fin("perimeter.in");
    ofstream fout("perimeter.out");

    fin >> n;

    for (int i = 0; i < n; i++) {
        string s; fin >> s;
        grid.push_back(s);
    }

    visited = vector<vector<bool>>(n, vector<bool>(n, false));

    int cur = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#' && !visited[i][j]) {
                blobs.push_back(vector<pair<int, int>>());
                floodfill(i, j, cur);
                cur++;
            }
        }
    }

    int max_area = 0;
    int max_peri = INF;  

    for (auto v : blobs) {
        if (v.size() >= max_area) {
            int peri = 0;
            for (auto p : v) {
                peri += get_peri(p.first, p.second);
            }

            if (v.size() == max_area) {
                max_peri = max_peri < peri ? max_peri : peri;
            } else {
                max_peri = peri;
                max_area = v.size();
            }
        }
    }

    fout << max_area << ' ' << max_peri << '\n';
    return 0;
}