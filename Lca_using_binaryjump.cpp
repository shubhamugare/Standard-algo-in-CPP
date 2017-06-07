#include<bits/stdc++.h>
 
typedef long long LL;  //Attention!!
using namespace std;
 
#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'
 
const int M = 1000000007;
 
const int N = 200001;
const int LN = 18;
 
vector <LL> g[N];
LL dp[LN][N],depth[N],color[N];
 
void dfs(LL s)
{
for(int node:g[s])
	if(color[node]==0)
		{	
		color[node] = 1;	
		dp[0][node] = s;
		depth[node] = depth[s] + 1;
		dfs(node);
		}
}
 
LL lca(LL a,LL b)
{
if(depth[a]<depth[b])
		swap(a,b);
 
LL diff  = depth[a] - depth[b];
 
LL i;
for(i=0;i<LN;i++)
	if(diff&(1<<i))	
		a = dp[i][a];
 
if(a!=b)
	{
	for(i=LN-1;i>=0;i--)	
		if(dp[i][a]!=dp[i][b])
			{
			a = dp[i][a];	
			b = dp[i][b];
			}
 
	a = dp[0][a];		
	}
return a;
}
 
 
int main()
{
ios_base::sync_with_stdio(0); cout.precision(15);cout.setf(ios::fixed);
LL n,i,j,m,t;
 
cin>>t;
 
for(int xx=1;xx<=t;xx++)
{
cout<<"Case "<<xx<<":"<<endl;
 
cin>>n;
 
LL a,b;
 
for(i=0;i<n;i++)
	{
	cin>>m;
	a = i;
	for(j=0;j<m;j++)	
		{cin>>b;
		b--;
		g[a].PB(b);
		g[b].PB(a);
		}
	color[i] = 0;
	}
 
color[n-1] = 0;
dp[0][0] = -1;  //parent of root 
color[0] = 1;
dfs(0);
 
for(i=1;i<LN;i++)
	for(j=0;j<n;j++)
		dp[i][j] = dp[i-1][dp[i-1][j]];
 
 
 
LL q;
cin>>q;
 
while(q--)
	{cin>>a>>b;
	a--;b--;
	cout<<lca(a,b)+1<<endl;
	}
 
}
}
 