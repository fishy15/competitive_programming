#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct num num;
struct num {
    int val;
    int pos;
};

int main() {
    ifstream fin("sort.in");
    ofstream fout("sort.out");

    int n; fin >> n;
    vector<num> nums;

    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        //cout << "HI\n";
        num m;
        m.val = x;
        m.pos = i;
        nums.push_back(m);
    }

    sort(nums.begin(), nums.end(), [](const num &a, const num &b) {
        if (a.val == b.val) {
            return a.pos < b.pos;
        }

        return a.val < b.val;
    });

    int max = 0;
    for (int i = 0; i < n; i++) {
        //cout << nums[i].pos << endl;
        int x = nums[i].pos - i;
        max = x > max ? x : max;
    }

    fout << max + 1 << '\n';
    return 0;
}
