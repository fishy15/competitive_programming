#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int lower_bound(int);
int upper_bound(int);

int N, Q; 
vector<int> nums;

int main() {
    ifstream fin("haybales.in");
    ofstream fout("haybales.out");

    fin >> N >> Q;
    
    for (int i = 0; i < N; i++) {
        int x; fin >> x;
        nums.push_back(x);
    }

    sort(nums.begin(), nums.end());

    for (int i = 0; i < Q; i++) {
        int l, r; fin >> l >> r;
        //cout << lower_bound(l) << ' ' << upper_bound(r) << '\n';
        fout << upper_bound(r) - lower_bound(l) << '\n';
    }

    return 0;
}

int lower_bound(int x) {
    //cout << "in lower\n";
    int min = 0;
    int max = N;

    while (min < max) {
        //cout << "loop\n";
        int mid = (min + max) / 2;
        if (nums[mid] >= x) {
            max = mid;
        } else if (nums[mid] < x) {
            min = mid + 1;
        } else {
            break;
        }
    }

    return min;
}

int upper_bound(int x) {
    int min = 0;
    int max = N;

    while (min < max) {
        //cout << "loop 2\n";
        int mid = (min + max) / 2;
        if (nums[mid] > x) {
            max = mid;
        } else if (nums[mid] <= x) {
            min = mid + 1;
        }
    }

    return min;
}
