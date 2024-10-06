#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
constexpr int INF = 1e9;

struct lazy_segtree {
    int n;
    vector<pair<int, int>> st;
    vector<int> lazy;

    lazy_segtree(int N) : n(N), st(4 * N), lazy(4 * N) {
    	build(1, 0, n-1);
    }
    
	void build(int v, int l, int r) {
        if (l == r) {
            st[v] = {0, 1};
        } else {
            int m = (l + r) / 2;
            build(2*v, l, m);
            build(2*v+1, m+1, r);
            st[v] = comb(st[2*v], st[2*v+1]);
        }
    }

    pair<int, int> comb(pair<int, int> a, pair<int, int> b) {
        if (a.first == b.first) {
            return {a.first, a.second + b.second};
        } else {
            return min(a, b);
        }
    }

    void push(int v, int l, int r) {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v].first += lazy[v];
        lazy[v] = 0;
    }

    void upd(int x, int y, int q) { return upd(1, 0, n - 1, x, y, q); }
    void upd(int v, int l, int r, int x, int y, int q) {
        push(v, l, r);
        if (y < l || r < x) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(2 * v, l, m, x, y, q);
            upd(2 * v + 1, m+1, r, x, y, q);
            st[v] = comb(st[2*v], st[2*v+1]);
        }
    }

    pair<int, int> qry(int x, int y) { return qry(1, 0, n - 1, x, y); }
    pair<int, int> qry(int v, int l, int r, int x, int y) {
        push(v, l, r);
        if (y < l || r < x) return {INF, 0};
        if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            auto v1 = qry(2 * v, l, m, x, y);
            auto v2 = qry(2 * v + 1, m+1, r, x, y);
            return comb(v1, v2);
        }
    }
};

ll brute(vector<int>& nums, int k) {
	int n = sz(nums);
	ll ans = 0;
	for(int left = 0; left < n; left++) {
		int bad = 0;
		map<int, int> counts;
		for(int right = left; right < n; right++) {
			int c = nums[right];
			counts[c]++;
			if(counts[c] == k)
				bad++;
			if(counts[c] == k+1)
				bad--;
			if(bad == 0)
				ans++;
		}
	}
	return ans;
}

ll solve(vector<int>& nums, int k) {
	int n = sz(nums);
	vector<vector<int>> colors(1e6+5);
	for(int i = 0; i < n; i++) {
		colors[nums[i]].push_back(i);
	}
	vector<vector<pair<int, int>>> bad(1e6+5);
	lazy_segtree tree(n);
	for(int c = 0; c < sz(colors); c++) {
		if(sz(colors[c]) < k)
			continue;
		colors[c].push_back(n);
		for(int i = k-1; i < sz(colors[c])-1; i++) {
			bad[c].emplace_back(colors[c][i], colors[c][i+1]-1);
		}
		int l = bad[c][0].first;
		int r = bad[c][0].second;
		// cout << "initial bad " << l << " " << r << endl;
		tree.upd(l, r, 1);
	}

	vector<int> index(1e6+5);
	ll ans = 0;

	for(int i = 0; i < n; i++) {
		auto res = tree.qry(i, n-1);
		// cout << "at " << i << " " <<  res.first << " " << res.second << endl;
		if(res.first == 0)
			ans += res.second;
		int c = nums[i];
		if(index[c] < sz(bad[c])) {
			int l = bad[c][index[c]].first;
			int r = bad[c][index[c]].second;
			tree.upd(l, r, -1);
			index[c]++;
		}
		if(index[c] < sz(bad[c])) {
			int l = bad[c][index[c]].first;
			int r = bad[c][index[c]].second;
			tree.upd(l, r, 1);
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;

        int seed = 1;
        while (true) {
            cout << seed << endl;
            srand(seed);


            vector<int> nums(n);

            for(int i = 0; i < n; i++) {
                nums[i] = rand() % n + 1;
            }

            ll b = brute(nums, k);
            ll ans = solve(nums, k);
            if(b != ans) {
                    cout << "BAD, brute: " << b << " sol: " << ans << endl;
                    for(auto i : nums)
                            cout << i << " ";
                    return 0;
            }

            seed++;
        }
}
