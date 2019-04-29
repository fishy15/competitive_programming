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
