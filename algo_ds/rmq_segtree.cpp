int arr[MAXN + 1];
int tree[4 * MAXN + 4];

void build(int node, int left, int right) {
    if (left == right) {
        tree[node] = arr[left];
    } else {
        int mid = (left + right) / 2;
        
        build(2 * node, left, mid);
        build(2 * node + 1, mid + 1, right);
        
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
}

void update(int node, int left, int right, int index, int value) {
    if (left == right) {
        arr[index] = value;
        tree[node] = value;
    } else {
        int mid = (left + right) / 2;
        if (index <= mid) {
            update(2 * node, left, mid, index, value);
        } else {
            update(2 * node + 1, mid + 1, right, index, value);
        }
        
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
}

int query(int node, int left, int right, int l, int r) {
    if (r < left || l > right) {
        return MAXN + 1;
    }
    
    if (l <= left && r >= right) {
        return tree[node];
    }
    
    int mid = (left + right) / 2;
    int res1 = query(2 * node, left, mid, l, r);
    int res2 = query(2 * node + 1, mid + 1, right, l, r);
    
    return min(res1, res2);
}
