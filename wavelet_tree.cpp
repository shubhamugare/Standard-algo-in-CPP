#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'

const LL M = (LL)1e9+7;
const int N = (int)1e6+7;
int a[N];

//1 indexed !!!
struct wavelet_tree{
    int lo, hi;
    wavelet_tree *l, *r;
    vector <int> b;
 
    //nos are in range [x,y]
    //array indices are [from, to)
    wavelet_tree(int *from, int *to, int x, int y){
        lo = x, hi = y;
        if(lo == hi or from >= to) return;
        int mid = (lo+hi)/2;
        auto f = [mid](int x){
            return x <= mid;
        };
        b.reserve(to-from+1);
        b.PB(0);
        for(auto it = from; it != to; it++)
            b.PB(b.back() + f(*it));
        //see how lambda function is used here  
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree(from, pivot, lo, mid);
        r = new wavelet_tree(pivot, to, mid+1, hi);
    }
 
    //kth smallest element in [l, r]
    int kth(int l, int r, int k){
        if(l > r) return 0;
        if(lo == hi) return lo;
        int inLeft = b[r] - b[l-1];
        int lb = b[l-1]; //amt of nos in first (l-1) nos that go in left 
        int rb = b[r]; //amt of nos in first (r) nos that go in left
        if(k <= inLeft) return this->l->kth(lb+1, rb , k);
        return this->r->kth(l-lb, r-rb, k-inLeft);
    }
 
    //count of nos in [l, r] Less than or equal to k
    int LTE(int l, int r, int k) {
        if(l > r or k < lo) return 0;
        if(hi <= k) return r - l + 1;
        int lb = b[l-1], rb = b[r];
        return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
    }
 
    //count of nos in [l, r] equal to k
    int count(int l, int r, int k) {
        if(l > r or k < lo or k > hi) return 0;
        if(lo == hi) return r - l + 1;
        int lb = b[l-1], rb = b[r], mid = (lo+hi)/2;
        if(k <= mid) return this->l->count(lb+1, rb, k);
        return this->r->count(l-lb, r-rb, k);
    }
    ~wavelet_tree(){
        delete l;
        delete r;
    }
};

int main()
{
    ios_base::sync_with_stdio(0); 
    cout.precision(15);
    cout.setf(ios::fixed);

    int n;
    cin >> n;

    for(int i=0;i<n;i++)                 
        cin >> a[i];

    //
    wavelet_tree T(a,a+n,1,(int)1e9);

    for(int i=1;i<=n;i++)
        cout<<T.kth(i,i,1)<<' ';
    cout<<endl;

}