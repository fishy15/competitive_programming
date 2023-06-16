#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>

using namespace std;

vvpii graph;
int N, Q;

int bfs(int loc, int k);

int main() {
    ifstream fin("mootube.in");
    ofstream fout("mootube.out");

    fin >> N >> Q;

    graph = vvpii(N);
    for (int i = 0; i < N - 1; i++) {
        int x, y, r; fin >> x >> y >> r;
        //cout << x << ' ' << y << ' ' << r << endl;
        graph[x - 1].push_back(make_pair(y - 1, r));
        graph[y - 1].push_back(make_pair(x - 1, r));
    }

    for (int i = 0; i < Q; i++) {
        //cout << "prob " << i << endl;
        int s, k; fin >> k >> s;
        //cout << s << ' ' << k << endl;

        int res = bfs(s - 1, k);
        fout << res - 1 << '\n';
    }

    return 0;
}

int bfs(int loc, int k) {
    //cout << loc << " works\n";
    vb visited = vb(N, false);
    queue<int> q;
    q.push(loc);
    int ans = 0;

    while (!q.empty()) {
        int num = q.front();
        q.pop();
        visited[num] = true;
        ans++;
        for (int i = 0; i < graph[num].size(); i++) {
            auto point = &graph[num][i];
            if (point->second >= k && !visited[point->first]) {
                q.push(point->first);
            }
        }
    }

    return ans;
}

