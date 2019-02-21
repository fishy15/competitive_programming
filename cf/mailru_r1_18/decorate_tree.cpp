#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef struct node node;
struct node {
    vector<int> connect;
    bool visited;
    int below;
};

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    vector<node> tree = vector<node>(n + 1);

    // init
    for (int i = 0; i < n; i++) {
        tree[i].visited = false;
        tree[i].below = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        tree[i + 2].connect.push_back(x);
        tree[x].connect.push_back(i + 2);
    }

    vector<int> dist;
    vector<int> queue;
    vector<int> backqueue;

    // fill queue with leaves
    for (int i = 2; i <= n; i++) {
        if (tree[i].connect.size() == 1) {
            queue.push_back(i);
        }
    }

    for (int i : queue) {
        cout << i << endl;
        tree[i].below = 1;
    }
    while (!queue.empty()) {
        for (int i : queue) {
            tree[i].visited = true;
        } 
        
        dist.push_back(queue.size());
        vector<int> nq;

        for (int i = 0; i < queue.size(); i++) {
            for (int j : tree[queue[i]].connect) {
                if (!tree[j].visited) {
                    nq.push_back(j);
                }
            }
        }

        // remove duplicates
        set<int> s;
        for (int i : nq) {
            s.insert(i);
        }
        nq = {};
        for (int i : s) {
            nq.push_back(i);
        }
        for (int i : nq) {
            for (int j : tree[i].connect) {
                if (tree[j].visited) {
                    tree[i].below += tree[j].below;
                    cout << "add " << j << " to " << i;
                }
            }
        }

        queue = nq;
    }

    int index = dist.size() - 1;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cout << tree[i].below << endl;
    }
    return 0;
}
