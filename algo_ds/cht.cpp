struct line {
    mutable ll m, b, l;
    line(ll m, ll b) : m(m), b(b), l(0) {}
    bool operator<(const line& other) const { return m < other.m; }
    bool operator<(const ll x) const { return l < x; }
};
template<bool GET_MAX>
struct cht : multiset<line, less<>> {
    // double: inf = 1/.0, div(a, b) = a / b
    static const ll inf = INFLL;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a & b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->l = inf; return false; }
        if (x->m == y->m) x->l = x->b > y->b ? inf : -inf;
        else x->l = div(y->b - x->b, x->m - y->m);
        return x->l >= y->l;
    }
    void add(line l) {
        if (!GET_MAX) l.m = -l.m, l.b = -l.b; 
        auto z = insert(l), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->l >= y->l) isect(x, erase(y));
    }
    ll qry(ll x) {
        auto l = *lower_bound(x);
        return (l.m * x + l.b) * (GET_MAX ? 1 : -1);
    }
};
