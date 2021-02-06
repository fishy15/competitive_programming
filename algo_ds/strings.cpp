// Manacher's Algorithm
// d1 stores # of palindromes centered at i
// d2 stores # of palindromes centered at [i - 1, i]
pair<vector<int>, vector<int>> manachers(string s) {
    int n = (int)(s.size());
    vector<int> d1(n);
    vector<int> d2(n);

    int l = 0;
    int r = -1;
    for (int i = 0; i < n; i++) {
        int k = 1;
        if (i <= r) k = min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    l = 0;
    r = -1;
    for (int i = 0; i < n; i++) {
        int k = 0;
        if (i <= r) k = min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n  && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }

    return {d1, d2};
}

// Polynomial Hashing
// Does double hashing with randomization
// precalculates N powers
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll modpow(ll n, ll e, ll mod) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * n % mod;
        n = n * n % mod;
        e >>= 1;
    }
    return res;
}

int randval() {
    return uniform_int_distribution<int>(2, 1000000005)(rng);
}
 
template<int N>
struct string_hash {
    struct hash {
        int n;
        array<int, 2> h;
        static inline array<array<int, N>, 2> base, inv;
        static constexpr int p[2] = {1000000007, 1000000009};
        hash() { 
            n = 0;
            if (!base[0][0]) calc_base();
            h = {0, 0};
        }
        hash(char c) : hash() {
            *this += c;
        }
        hash(const hash &h2) : hash() {
            n = h2.n;
            h = h2.h;
        }
        void calc_base() {
            for (int i = 0; i < 2; i++) {
                base[i][0] = 1;
                base[i][1] = randval();
                inv[i][0] = 1;
                inv[i][1] = modpow(base[i][1], p[i] - 2, p[i]);
            }
            for (int j = 2; j < N; j++) {
                for (int i = 0; i < 2; i++) {
                    base[i][j] = (ll) base[i][j - 1] * base[i][1] % p[i];
                    inv[i][j] = (ll) inv[i][j - 1] * inv[i][1] % p[i];
                }
            }
        }
        bool operator==(const hash &h2) const {
            return n == h2.n && h == h2.h;
        }
        bool operator<(const hash &h2) const {
            if (n == h2.n) return h < h2.h;
            return n < h2.n;
        }
        hash &operator+=(const char c) {
            for (int i = 0; i < 2; i++) {
                h[i] += (ll) base[i][n] * c % p[i];
                if (h[i] >= p[i]) h[i] -= p[i];
            }
            n++;
            return *this;
        }
        hash &operator-=(const hash &h2) {
            for (int i = 0; i < 2; i++) {
                h[i] -= h2.h[i];
                if (h[i] < 0) h[i] += p[i];
                h[i] = (ll) h[i] * inv[i][h2.n] % p[i];
            }
            n -= h2.n;
            return *this;
        }
    };
    vector<hash> h;
    string_hash() : string_hash("") {}
    string_hash(const string &s) {
        h.resize(s.size());
        hash cur;
        for (int i = 0; i < (int)(s.size()); i++) {
            cur += s[i];
            h[i] = cur;
        }
    }
    hash substr(int n, int sz) const {
        hash res = h[n + sz - 1];
        if (n) res -= h[n - 1];
        return res;
    }
    hash val() const {
        return h.back();
    }
    static hash calc(const string &s) {
        hash cur;
        for (char c : s) {
            cur += c;
        }
        return cur;
    }
};
 
using shash = string_hash<MAXN>;

// Aho-Corasick Algorithm
// insert strings with insert(), then build() after all done
// trie[x].link stores suffix link (max proper suffix), trie[x].exit_link stores max suffix that is a leaf
// SZ is size of alphabet, also can change conv function (or change to pass in a function)
template<int SZ>
struct aho_corasick {
    struct node {
        array<int, SZ> next;
        int depth, link, exit_link, cnt, leafcnt;
        node() : depth(0), link(-1), exit_link(-1), cnt(0), leafcnt(0) { next.fill(0); }
    };
    vector<node> trie;
    aho_corasick() : trie(1) {}
    aho_corasick(const vector<string> &v) : aho_corasick() {
        for (auto s : v) insert(s);
        build();
    }
    void clear() { trie = vector<node>(1); }
    int conv(int c) { return c - 'a'; }
    int insert(const string &s) {
        int v = 0;
        trie[0].cnt++;
        for (auto ch : s) {
            int c = conv(ch);
            if (!trie[v].next[c]) {
                trie[v].next[c] = trie.size();
                trie.emplace_back();
                trie.back().depth = trie[v].depth + 1;
            }
            v = trie[v].next[c];
            trie[v].cnt++;
        }
        trie[v].leafcnt++;
        return v;
    }
    int get_next(int v, int c) {
        return trie[v].next[conv(c)];
    }
    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int c = 0; c < SZ; c++) {
                if (trie[v].next[c]) {
                    int e = trie[v].next[c];
                    int link = trie[e].link = trie[v].link == -1 ? 0 : trie[trie[v].link].next[c]; 
                    trie[e].exit_link = trie[link].leafcnt ? link : trie[link].exit_link;
                    q.push(e);
                }
            }
            if (v) {
                for (int c = 0; c < SZ; c++) {
                    if (!trie[v].next[c]) {
                        trie[v].next[c] = trie[trie[v].link].next[c];
                    }
                }
            }
        }
    }
};
