#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;

struct Expr {
    virtual void simple_print(int left, int row) = 0;    
    virtual array<int, 3> print(int left, int row) = 0;    
};

vector<string> grid;
void setg(int x, int y, char c) {
    if (x < 0) return;
    while (sz(grid) <= x) {
        grid.push_back("");
    }
    while (sz(grid[x]) <= y) {
        grid[x] += " ";
    }
    grid[x][y] = c;
}

struct Var : public Expr {
    char v;
    Var(char _v) : v(_v) {}
    virtual void simple_print(int left, int row) {
        cout << string(left, ' ') << v << endl;
        assert(row != -1);
    }
    // {left, mid, right}
    virtual array<int, 3> print(int left, int row) {
        setg(row - 1, left, '|');
        setg(row, left, v);
        return {left, left, left};
    }
};

struct Op : public Expr {
    char op;
    Expr *l, *r;
    Op(char _op, Expr *_l, Expr *_r) : op(_op), l(_l), r(_r) {}
    virtual void simple_print(int left, int row) {
        cout << string(left, ' ') << "OP " << op << endl;
        l->print(left + 2, row);
        r->print(left + 2, row);
    }
    virtual array<int, 3> print(int left, int row) {
        auto [ll_, lm, lr] = l->print(left, row + 2);
        auto [rl, rm, rr] = r->print(lr + 6, row + 2);
        setg(row, lm, '.');
        setg(row, rm, '.');
        for (int i = lm + 1; i < rm; i++) {
            setg(row, i, '-');
        }
        setg(row, lr + 2, '[');
        setg(row-1, lr + 3, '|');
        setg(row, lr + 3, op);
        setg(row, lr + 4, ']');
        return {ll_, lr + 3, rr};
    }
};

using It = string::iterator;

pair<Expr *, It> read_expr(It start, It end);
pair<Expr *, It> read_term(It start, It end);
pair<Expr *, It> read_factor(It start, It end);
pair<Expr *, It> read_item(It start, It end);
pair<Expr *, It> read_var(It start, It end);

pair<Expr *, It> read_expr(It start, It end) {
    vector<Expr *> term_stack;
    vector<char> ops;
    while (true) {
        auto [elem, new_start] = read_term(start, end);
        start = new_start;
        term_stack.push_back(elem);

        if (start == end || (*start != '+' && *start != '-')) {
            break;
        }
        assert(*start == '+' || *start == '-');
        ops.push_back(*start);
        start++;
    }

    Expr *cur = term_stack[0];
    rep(i, 1, sz(term_stack)) {
        cur = new Op(ops[i - 1], cur, term_stack[i]);
    }
    return {cur, start};
}

pair<Expr *, It> read_term(It start, It end) {
    vector<Expr *> term_stack;
    vector<char> ops;
    while (true) {
        auto [elem, new_start] = read_factor(start, end);
        start = new_start;
        term_stack.push_back(elem);

        if (start == end || (*start != '*' && *start != '/')) {
            break;
        }
        assert(*start == '*' || *start == '/');
        ops.push_back(*start);
        start++;
    }

    Expr *cur = term_stack[0];
    rep(i, 1, sz(term_stack)) {
        cur = new Op(ops[i - 1], cur, term_stack[i]);
    }
    return {cur, start};
}

pair<Expr *, It> read_factor(It start, It end) {
    vector<Expr *> power_stack;
    while (true) {
        auto [elem, new_start] = read_item(start, end);
        power_stack.push_back(elem);
        start = new_start;

        if (start == end || *start != '^') {
            break;
        }
        assert(*start == '^');
        start++;
    }

    Expr *cur = power_stack.back();
    for (int i = sz(power_stack) - 2; i >= 0; i--) {
        cur = new Op('^', power_stack[i], cur);
    }
    return {cur, start};
}

pair<Expr *, It> read_item(It start, It end) {
    if (*start == '(') {
        start++;
        auto [inside, new_start] = read_expr(start, end);
        assert(*new_start == ')');
        return {inside, new_start + 1};
    } else {
        return read_var(start, end);
    }
}

pair<Expr *, It> read_var(It start, It end) {
    char c = *start;
    assert(start != end);
    return {new Var(c), start + 1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);

    string s;
    cin >> s;

    auto [parse, _] = read_expr(all(s));
    parse->print(0, 0);

    for (auto &row : grid) {
        cout << row << '\n';
    }

    return 0;
}

