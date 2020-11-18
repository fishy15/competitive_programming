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
