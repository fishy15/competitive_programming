/*
ID: aaryan.1
TASK: msquare
LANG: C++11
*/

#include <bits/stdc++.h>

using namespace std;

typedef struct pos pos;
struct pos {
    array<int, 8> val;
    string path;
};

bool operator<(const pos &p1, const pos &p2) {
    if (p1.val == p2.val) {
        return p1.path < p2.path;
    }

    return p1.val < p2.val;
}

pos res;
ofstream fout;

array<int, 8> A(array<int, 8> init) {
    int temp;
    // 0 1 2 3 4 5 6 7 -> 7 6 5 4 3 2 1 0
    reverse(init.begin(), init.end());
    return init;
}

array<int, 8> B(array<int, 8> init) {
    int temp;
    // 0 1 2 3 4 5 6 7 -> 3 0 1 2 5 6 7 4
    temp = init[3];
    init[3] = init[2];
    init[2] = init[1];
    init[1] = init[0];
    init[0] = temp;
    
    temp = init[4];
    init[4] = init[5];
    init[5] = init[6];
    init[6] = init[7];
    init[7] = temp;

    return init;
}

array<int, 8> C(array<int, 8> init) {
    int temp;
    // 0 1 2 3 4 5 6 7 -> 0 6 1 3 4 2 5 7

    temp = init[1];
    init[1] = init[6];
    init[6] = init[5];
    init[5] = init[2];
    init[2] = temp;
    
    return init;
}

void print(pos p) {
    fout << p.path.size() << '\n';
    for (int i = 0; i < p.path.size(); i++) {
        if (i % 60 == 59) {
            fout << '\n';
        }

        fout << p.path[i];
    }

    if (p.path.size() % 60 != 59) {
        fout << '\n';
    }
}

int main() {
    ifstream fin("msquare.in");
    fout = ofstream("msquare.out");

    for (int i = 0; i < 8; i++) {
        fin >> res.val[i];
    }

    queue<pos> q;
    pos start;
    start.val = {1, 2, 3, 4, 5, 6, 7, 8};
    start.path = "";
    q.push(start);

    set<array<int, 8>> visited;
    while (!q.empty()) {
        pos p = q.front();
        q.pop();
        //cout << p.path << endl;

        if (p.val == res.val) {
            print(p);
            return 0;
        }
        
        pos a, b, c;
        a.val = A(p.val);
        b.val = B(p.val);
        c.val = C(p.val);
        a.path = p.path + "A";
        b.path = p.path + "B";
        c.path = p.path + "C";

        if (!visited.count(a.val)) {
            q.push(a);
            visited.insert(a.val);
        }

        if (!visited.count(b.val)) {
            q.push(b);
            visited.insert(b.val);
        }

        if (!visited.count(c.val)) {
            q.push(c);
            visited.insert(c.val);
        }
    }

    return 0;
}