#include<bits/stdc++.h>
 
typedef long long LL;  //Attention!!
using namespace std;
 
#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'
 
const LL M = 1000000007;
 
const LL N1 = 5001;
 
LL deg[N1];
LL c[N1][N1];
LL f[N1][N1];
LL N, S, F;
LL d[N1];
LL ptr[N1];
LL q[N1];
 
bool bfs()
{
    LL L = 0, R = 0;
    q[R++] = S;
    fillchar(d, -1);
    d[S] = 0;
    while (L < R) {
        LL v = q[L++];
        for(LL i=0;i<N;++i)
            if (d[i] == -1 && f[v][i] < c[v][i])
            {
                q[R++] = i;
                d[i] = d[v] + 1;
            }
    }
    return d[F] != -1;
}
 
LL dfs (LL v, LL flow)
{
    if (!flow)  return 0;
    if (v == F)  return flow;
    for (LL &to = ptr[v]; to < N; ++to)
    {
        if (d[to] != d[v] + 1)  continue;
        LL pushed = dfs (to, min (flow, c[v][to] - f[v][to]));
        if (pushed)
        {
            f[v][to] += pushed;
            f[to][v] -= pushed;
            return pushed;
        }
    }
    return 0;
}
 
LL dinic()
{
    LL flow = 0;
    for (;;) {
        if (!bfs())  break;
        fillchar(ptr, 0);
            while (LL pushed = dfs (S, M))
            flow += pushed;
    }
    return flow;
}
 
 
//f is flow and c is capacity....O(V^2*E) for max matching ff will give O(VE) so this will not be useful... 
 
int main()
{
ios_base::sync_with_stdio(0); cout.precision(15);cout.setf(ios::fixed);
LL i,j,n,m;
 
cin>>n>>m;
 
LL a,b,d;
 
for(i=0;i<n;i++)
    for(j=0;j<m;j++)
           c[i][j] = 0; 
 
for(i=0;i<m;i++)
    {
      cin>>a>>b>>d;  
     a--;b--;
      c[a][b] += d;
      c[b][a] += d; 
    }
//flow parameters
S = 0;   //source vertex
F = n-1;  //sink vertex
N = n;  //total vertices..
 
cout<<dinic()<<endl;
 
}
 
 