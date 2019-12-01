// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct query {
    int i;
    int len;
    int pos;
    int ans;   
};

int n, m;
int nums[200001];
vector<query> q;
vector<pair<int, int>> smth;

class BIT {
public:
    vector<int> bit;
    
    int get_max_one(int n) {
        return n & (~n + 1);
    }

    BIT(int sz) {
        bit = vector<int>(sz + 1, 0);
    }

    int get_before(int i) {
        int sum = 0;
        
        while (i > 0) {
            sum += bit[i];
            i -= get_max_one(i);
        }

        return sum;
    }

    void add(int i, int val) {
        while (i < bit.size()) {
            bit[i] += val;
            i += get_max_one(i);
        }
    }
};

int main() {
    //cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        smth.push_back({nums[i], i});
    }

    sort(smth.begin(), smth.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.first == p2.first) {
            return p1.second > p2.second;
        }
        return p1.first < p2.first;
    });

    cin >> m;
    for (int i = 0; i < m; i++) {
        query qq;
        cin >> qq.len >> qq.pos;
        qq.i = i;
        q.push_back(qq);
    }

    sort(q.begin(), q.end(), [](const query &q1, const query &q2) {
        if (q1.len == q2.len) {
            return q1.pos < q2.pos;
        }
        return q1.len > q2.len;
    });

    int possmth = 0;
    int posq = 0;
    BIT bit(n + 1);
    for (int i = n; i > 0; i--) {
        //cout << '\t' << i << '\n';
        int pos = 0;
        int prev = 0;
        while (posq < m && q[posq].len == i) {
            //cout << "\t\t" << posq << '\n';
            int diff = q[posq].pos - prev;
            prev = q[posq].pos;
            while (diff > 0) {
                //cout << prev << ' ' << pos << ' ' << diff  << '\n';
                int tempdiff = bit.get_before(diff + pos) - bit.get_before(pos);
                pos += diff;
                diff = tempdiff;
            }
            q[posq].ans = nums[pos];
            posq++;
        }
        int rem = smth[possmth].second;
        bit.add(rem, 1);
        prev = 0;
        /* for (int i = 1; i <= n; i++) { */
        /*     if (prev == bit.get_before(i)) { */
        /*         cout << nums[i] << ' '; */
        /*     } */
        /*     prev = bit.get_before(i); */
        /* } cout << '\n'; */
        possmth++;
    }

    sort(q.begin(), q.end(), [](const query &q1, const query &q2) {
        return q1.i < q2.i;
    });

    for (int i = 0; i < m; i++) {
        cout << q[i].ans << '\n';
    }

    return 0;
}
