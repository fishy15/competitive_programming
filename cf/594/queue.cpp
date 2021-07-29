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

struct person {
    int pos;
    ll ready;
    ll done;
};

class comp1 {
public:
    bool operator()(const person &p1, const person &p2) {
        if (p1.ready == p2.ready) {
            return p1.pos > p2.pos;
        }

        return p1.ready > p2.ready;
    }
};

class comp2 {
public:
    bool operator()(const person &p1, const person &p2) {
        return p1.pos > p2.pos;
    }
};

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

    int n, p; cin >> n >> p;
    vector<person> ppl;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        person p; 
        p.pos = i + 1;
        p.ready = x;
        ppl.push_back(p);
    }

    ll t = 0;
    priority_queue<person, vector<person>, comp1> getup;
    priority_queue<person, vector<person>, comp2> wait;
    priority_queue<person, vector<person>, comp2> realq;
    BIT up(n);

    for (int i = 0; i < n; i++) {
        getup.push(ppl[i]);
    }

    while (!getup.empty() || !realq.empty() || !wait.empty()) {
        if (realq.empty()) {
            t = getup.top().ready;
        }

        vector<int> gotup;
        while (!getup.empty()) {
            person cur = getup.top();
            if (cur.ready > t) break;
            getup.pop();

            if (up.get_before(cur.pos) == 0) {
                realq.push(cur);
                gotup.push_back(cur.pos);
            } else {
                wait.push(cur);
            }
        }

        for (int &i : gotup) {
            up.add(i, 1);
        }

        t += p;
        person done = realq.top();
        realq.pop();
        done.done = t;
        ppl[done.pos - 1].done = t;
        up.add(done.pos, -1);

        while (!wait.empty()) {
            person cur = wait.top();
            if (up.get_before(cur.pos) == 0) {
                realq.push(cur);
                up.add(cur.pos, 1);
                wait.pop();
            } else {
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ppl[i].done << ' ';
    } cout << '\n';

    return 0;
}
