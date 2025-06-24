#include <algorithm>
#include <vector>
#include "gap.h"

using namespace std;
using ll = long long;

constexpr ll MAX = 1'000'000'000'000'000'000;

ll solve1(int N) {
    vector<ll> front, back;
    ll mn = 0;
    ll mx = MAX;

    while (mn < mx && ssize(front) + ssize(back) < N) {
        MinMax(mn, mx, &mn, &mx);
        if (mn == -1) {
            break;
        } else if (mn == mx) {
            front.push_back(mn);
            break;
        } else {
            front.push_back(mn);
            back.push_back(mx);
        }
        mn++;
        mx--;
    }

    reverse(begin(back), end(back));
    front.insert(end(front), begin(back), end(back));

    ll ans = 0;
    for (int i = 0; i < N-1; i++) {
        ans = max(ans, front[i+1] - front[i]);
    }

    return ans;
}

ll solve2(int N) {
    ll mn, mx;
    MinMax(0, MAX, &mn, &mx);

    auto gap_size = (mx - mn + N - 1) / N;
    ll cur = mn + 1;
    ll last = mn;
    ll ans = 0;
    while (cur <= mx) {
        ll cur_mn, cur_mx;
        MinMax(cur, cur + gap_size - 1, &cur_mn, &cur_mx);
        if (cur_mn != -1) {
            ans = max(ans, cur_mn - last);
        }
        if (cur_mx != -1) {
            last = cur_mx;
        }
        cur += gap_size;
    }

    return ans;
}

ll findGap(int T, int N) {
    if (T == 1) {
        return solve1(N);
    } else {
        return solve2(N);
    }
}
