#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define MP make_pair
#define PB push_back
#define all(v) (v).begin(),(v).end()
#define endl '\n'

const LL M = (LL)1e9 + 7;

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

const LL MS = (LL)1e6+7;
LL invmemo[MS];
LL inv(LL a)
{   
    if(a<MS && invmemo[a]!=0) return invmemo[a];
    if(a<MS)
        return invmemo[a] = powa(a,M-2);
    else
        return powa(a,M-2);
}

//interpolate using Lagrange's form 
//input values are for poLLs i=0 to i=m-1
LL Lagrange(vector <LL> &in,LL n)
{
    LL m = in.size();
    LL num = 1;
    LL iden = 1;

    for(int i=1;i<m;i++)
        num = (num*(n-i))%M;

    for(int i=1;i<m;i++)
        iden = (iden*inv(i))%M;

    LL ans = 0;
    int sign = (m%2? 1 : -1);

    for(int i=0;i<m;i++)
    {   
        ans = ((ans + sign*((in[i]*num)%M)*iden)%M + M)%M; 
        num = (num*(n-i))%M;
        num = (num*inv(n-i-1))%M;
        iden = (iden*inv(i+1))%M;
        iden = (iden*(m-i-1))%M;
        sign *= -1;
    }    

    return ans;
}

int main()
{   
    ios_base::sync_with_stdio(0); 
    cout.precision(15);
    cout.setf(ios::fixed)  ;

    LL n,k;
    cin >> n >> k;

    //polynomial of degree k+1
    //requires k+2 points
    vector <LL> in(k+2);

    in[0] = 0;
    for(int i=1;i<=k+1;i++)
    {   

        in[i] = (in[i-1]+powa(i,k))%M;
    }
    
    if(n>k+1)    
        cout << Lagrange (in,n) << endl; 
    else
        cout << in[n] << endl;
}