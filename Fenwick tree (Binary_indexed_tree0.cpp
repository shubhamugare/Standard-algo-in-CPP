
//to find sum

struct FenwickTree 
{
    vector<int> bit; // binary indexed tree
    int n;

    void init(int n) 
    {
        this->n = n;
        bit.assign(n, 0);
    }
    
    int sum(int r) 
    {
        int ret = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            ret += bit[r];
        return ret;
    }
    
    void add(int idx, int delta) 
    {
        for (; idx < n; idx = idx | (idx+1))
            bit[idx] += delta;
    }
    
    int sum(int l, int r) 
    {
        return sum(r) - sum(l-1);
    }
    
    void init(vector<int> a)
     {
        init(a.size());
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }
};

//to find minimum from 0 to r

struct FenwickTreeMin {
    vector<int> bit;
    int n;
    const int INF = (int)1e9;
    void init (int n) {
        this->n = n;
        bit.assign (n, INF);
    }
    int getmin (int r) {
        int ret = INF;
        for (; r >= 0; r = (r & (r+1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }
    void update (int idx, int val) {
        for (; idx < n; idx = idx | (idx+1))
            bit[idx] = min(bit[idx], val);
    }
    void init (vector<int> a) {
        init (a.size());
        for (size_t i = 0; i < a.size(); i++)
            update(i, a[i]);
    }
};

//finding sum in 2D
struct FenwickTree2D {
    vector <vector <int> > bit;
    int n, m;
    // init(...) { ... }
    int sum (int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i+1)) - 1)
            for (int j = y; j >= 0; j = (j & (j+1)) - 1)
                ret += bit[i][j];
        return ret;
    }
    void add(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i+1))
            for (int j = y; j < m; j = j | (j+1))
                bit[i][j] += delta;
    }
};