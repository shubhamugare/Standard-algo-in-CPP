#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'

const int M = (int)1e9+7;
const int N = 1e4;

const char min_c = 'a';
const LL p1 = 31, M1 = 1000000007;
const LL p2 = 101, M2 = 1000000009;

struct Hash {
    LL p, mod;
    LL h[N], pw[N];
    Hash() {
        p = mod = 1;
    }

    /*constructor used for hashing */
    Hash(string &s, LL P, LL Mod) {
        p = P;
        mod = Mod;
        pw[0] = 1;
        for (int i = 1; i < N; ++i) {
            pw[i] = (pw[i - 1] * p) % mod;
        }
        h[0] = s[0] - min_c + 1;
        for (int i = 1; i < s.length(); i++) {
            h[i] = (p * h[i - 1] + s[i] - min_c + 1) % mod;
        }
    }
    LL get_hash(LL l, LL r) {
        LL x = h[r], y = 0;
        if (l != 0) {
            y = h[l - 1] * pw[r - l + 1];
        }
        return ((x - y) % mod + mod) % mod;
    }
};

 

int main()
{
//ios_base::sync_with_stdio(0); 
cout.precision(15);
cout.setf(ios::fixed);

string a,b,s;
int i,j,n;

cin >> s >> a >> b;


string t;
t = s+a+b;

Hash H[2];
H[0] = Hash(t,p1,M1);
H[1] = Hash(t,p2,M2); 


int l2 = a.size(),l3 = b.size(),l1 = s.size();

int p = H[0].get_hash(l1,l1+l2-1);
int q = H[0].get_hash(l1+l2,l1+l2+l3-1);
int r = H[1].get_hash(l1,l1+l2-1);
int ss = H[1].get_hash(l1+l2,l1+l2+l3-1);

vector <pair<int,int> > v;

// cout<<p<<' '<<q<<endl;
int x,y,z,w;

for(i=0;i+l2<=s.size();i++)
    for(j=i;j+l3<=s.size();j++)
        {
        if(i+l2-1 > j+l3-1) continue;   

        x = H[0].get_hash(i,i+l2-1);
        z = H[1].get_hash(i,i+l2-1);

        // cout<<ans[0]<<endl;
        if(p!=x || z!=r) continue;
        y = H[0].get_hash(j,j+l3-1);
        w = H[1].get_hash(j,j+l3-1);
        

        if(q!=y || w!=ss) continue;
        
        // cout<<i<<' '<<j<<endl;
        v.PB(MP(H[0].get_hash(i,j+l3-1),H[1].get_hash(i,j+l3-1)));
        }

sort(v.begin(),v.end());

int cnt = distance(v.begin(),unique(v.begin(),v.end()));

cout<<cnt<<endl;
}
