#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define PB push_back
#define all(v) (v).begin(),(v).end()
#define endl '\n'

const LL M = 1e9+7;

const int N = 22;
LL a[1<<N];

LL powa(LL a,LL b)
{
    a%=M;
    LL res=1%M;

    while(b>0)
    {
        if(b&1)res=res*a%M;
        b>>=1;
        a=a*a%M;
    }
    return res;
}

void fwht(LL *data, int dim) {
  for (int len = 1; 2 * len <= dim; len <<= 1) {
    for (int i = 0; i < dim; i += 2 * len) {
      for (int j = 0; j < len; j++) {
        LL a = data[i + j];
        LL b = data[i + j + len];
        data[i + j] = (a + b) % M;
        data[i + j + len] = (M + a - b) % M;
      }
    }
  }
}

int main() 
{
    ios_base::sync_with_stdio(0); 
    cout.precision(15);
    cout.setf(ios::fixed)  ;

    int n;
    cin >> n;

    string s;
    cin >> s;

    for(int i=0;i<(1<<n);i++)
    {
        a[i] = s[i]-'0';
    }

    fwht(a, 1<<n);

    for(int i=0;i<(1<<n);i++)
          a[i] = (1LL*a[i]*a[i])%M;

    fwht(a, 1<<n);
    
    LL im = powa(1<<n,M-2);    
    for(int i=0;i<(1<<n);i++)        
        a[i] = (a[i]*im)%M;   //to take inverse!!
 
    LL ans = 0;

    int pw[1<<n];
    pw[0] = 1;
    for(int i=1;i<=n;i++) pw[i] = (pw[i-1]+pw[i-1])%M;

    for(int i=0;i<(1<<n);i++)
        ans = (ans+1LL*a[i]*pw[n-__builtin_popcount(i)])%M;
    
    cout << (3*ans)%M << endl;    
}