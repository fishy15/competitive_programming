#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef struct node node;
struct node {
    int head;
    vector<int> connect;
    bool visited;
    int below;
};

int getDist(int);
int n;
vector<node> tree;
vector<int> dist;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    tree = vector<node>(n + 1);

    // init
    for (int i = 0; i < n; i++) {
        tree[i].visited = false;
        tree[i].below = 0;
        tree[i].head = -1;
    }

    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        tree[i + 2].connect.push_back(x);
        tree[x].connect.push_back(i + 2);
    }

    vector<int> queue = {1};

    while (!queue.empty()) {
        for (int i : queue) {
            tree[i].visited = true;
        } 
        
        vector<int> nq;
        for (int i = 0; i < queue.size(); i++) {
            for (int j : tree[queue[i]].connect) {
                if (!tree[j].visited) {
                    nq.push_back(j);
                    tree[j].head = queue[i];
                }
            }
        }

        queue = nq;
    }

    /*
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << tree[i].head << endl;
    }
    */
    dist = vector<int>(n + 1);
    //cout << dist.size();
    for (int i = 1; i <= n; i++) {
        dist[i] = 0;
    }

    getDist(1);

    sort(dist.begin(), dist.end());
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << ' ';
    }
    return 0;
}

int getDist(int n) {
    //cout << n << endl;
    if (dist[n] > 0) {
        return dist[n];
    } else {
        if (tree[n].connect.size() == 1 && n != 1) {
            dist[n] = 1;
            return 1;
        } 
    }

    int ans = 0;
    for (int i : tree[n].connect) {
        if (i != tree[n].head) {
            ans += getDist(i);
        }
    }

    dist[n] = ans;
    return ans;
}
