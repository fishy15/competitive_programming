int BIT[MAXBIT];

void update(int x, int v) {
    while (x < MAXBIT) {
        bit[x] += v;
        x += x & -x;
    }
}

int query(int x) {
    int ans = 0;
    while (x) {
        ans += bit[x];
        x -= x & -x;
    }
    return ans;
}


