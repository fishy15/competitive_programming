#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> connections;
vector<bool> in_loop;
vector<int> queue;
int pos = 0;

void is_loop(int);

int main() {
    ifstream fin("shuffle.in");
    ofstream fout("shuffle.out");

    fin >> N;
    connections = vector<int>(N, 0);
    in_loop = vector<bool>(N);
    queue = vector<int>(N);

    for (int i = 0; i < N; i++) {
        int x; fin >> x;
        connections[i] = x - 1;
        //cout << x  << ' ';
        in_loop[i] = false;

        //cout << connections[i] << '\n';
    }

    for (int i = 0; i < N; i++) {
        queue = vector<int>();
        int cur = i;
        queue.push_back(cur);
        for (int i = 0; i < N; i++) {
            cur = connections[cur];
            if (cur == queue[0]) {
                for (int j : queue) {
                    in_loop[j] = true;
                }
            } else if (in_loop[cur]) {
                break;
            } else {
                queue.push_back(cur);
            }
        }
    }

    int count = 0;
    for (bool b : in_loop) {
        //cout << b << " ";
        count += b;
    }

    //cout << endl;
    fout << count << '\n';
    return 0;
}
