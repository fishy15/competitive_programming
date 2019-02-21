#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n, m;
vector<int> nums;
vector<int> size;

int find(int x) {
    if (nums[x] == x) {
        return x;
    }

    nums[x] = find(nums[x]);
    return nums[x];
}

void join(int x, int y) {
    if ((x=find(x)) == (y=find(y))) {
        return;
    }

    if (size[x] > size[y]) {
        nums[y] = x;
        size[x] += size[y];
    } else {
        nums[x] = y;
        size[y] += size[x];
    }
}

int main() {
    ifstream fin("disjoint.in");
    ofstream fout("disjoint.out");

    int n, m; fin >> n >> m;
    nums = vector<int>(n);
    size = vector<int>(n);
    for (int i = 0; i < n; i++) {
        nums[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int op, a, b; fin >> op >> a >> b;
        if (op == 1) {
            join(a - 1, b - 1);
        } else {
            if (find(a - 1) == find(b - 1)) {
                fout << "DA\n";
            } else {
                fout << "NU\n";
            }
        }
    }

    return 0;
}
