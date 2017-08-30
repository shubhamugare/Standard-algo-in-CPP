#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define MP Make_pair
#define PB push_back
#define all(v) (v).begin(),(v).end()
#define endl '\n'

LL M = (LL)1e9+7;
const LL N = 10005;

//polynoMials are taken as a0 + a1x + a2x^2...
LL mem[N * 60];
LL a[N],b[N],ret[N];
LL Mid;

void Mult(LL *A, LL *B, LL *C, LL n) 
{
    if (n <= 64) {
                // cout << "YOa" << C[1] << endl;

        for (LL i=0; i<n; i++)
            for (LL j=0; j<n; j++) (C[i+j] += A[i] * B[j]) %= M;
                // cout << "YOb" << C[1] << endl;
        return;
    }

    LL base = Mid;
    Mid += n * 3;
    fill(mem+base, mem+Mid, 0);

    LL hn = n/2;
    Mult(A, B, mem+base, hn);
    Mult(A+hn, B+hn, mem+base+n, hn);


    LL bb = Mid;
    Mid += n;
    for (LL i=0; i<hn; i++) {
        mem[bb+i] = (A[i] + A[hn+i]);
        if (mem[bb+i] >= M) mem[bb+i] -= M;
    }
    for (LL i=0; i<hn; i++) {
        mem[bb+hn+i] = (B[i] + B[hn+i]);
        if (mem[bb+hn+i] >= M) mem[bb+hn+i] -= M;
    }
    Mult(mem+bb, mem+bb+hn, mem+base+n+n, hn);
    for (LL i=0; i<n; i++) {
        C[i] += mem[base+i];
        C[i+hn] += mem[base+n+n+i] - mem[base+i] - mem[base+n+i];
        C[i+n] += mem[base+n+i];
    }
    for (LL i=0; i<2*n; i++) {
        if (C[i] >= M) C[i] -= M;
        if (C[i] < 0) C[i] += M;
        if (C[i] < 0) C[i] += M;
    }
    Mid -= 4 * n;
}


LL fac[N];

int main()
{   
    ios_base::sync_with_stdio(0); 
    cout.precision(15);
    cout.setf(ios::fixed)  ;
    fac[0] = 1;

    LL t;
    cin >> t;

    for(LL xx=1;xx<=t;xx++)
    {
        //using FFT
        LL n;
        cin >> n >> M;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(ret,0,sizeof(ret));


        fac[0] = 1;
        b[1] = 1;    
        for(LL i=1;i<N;i++) 
            fac[i] = (fac[i-1]*i)%M;
        
        for(LL i=2;i<=n;i++)
        {
            b[i] = fac[i];
            for(LL j=1;j<i;j++)
                b[i] = (b[i] - fac[i-j]*b[j]%M + M)%M;
        }
        
        for(LL i=0;i<=n;i++) a[0] = 0;    
        a[0] = 1;
        LL ans = 0;

        for(LL i=1;i<=n;i++)
        {   
            memset(ret,0,sizeof(ret));
            Mult(a,b,ret,n+2);
            for(LL i=0;i<=n;i++)
                a[i] = (ret[i]%M)%M;
            ans = (ans + i*i*a[n])%M;
        } 

        cout <<"Case #"<<xx<<": "<<ans << endl; 
    }      
}

    


