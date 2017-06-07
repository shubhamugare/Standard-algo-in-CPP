#include<bits/stdc++.h>
 
typedef long long int;  //Attention!!
using namespace std;
 
#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'
 
const int M = 1000000007;
const int N = 5001;
 
int color[N];
int par[N];
int tmp[N][N];
int g[N][N];
int n;
 
int ff()
{
int s;
color[n-1] = 1;
 
fillchar(par,0);
int flow = 0;
 
while(color[n-1])
	{
	for(int i=0;i<n;i++) color[i] = 0;
	
	queue <int> q;
	q.push(0);
	color[0] = 1;
 
	while(!q.empty())
			{
			s =	q.front();
			q.pop();
			for(int i=0;i<n;i++)		
				if(tmp[s][i]>0 && color[i]==0)
					{
					color[i] = 1;
					par[i] = s;
					q.push(i);
					}
				
			}
	int xx = n-1;		
	int incr = M;
	
	if(color[n-1]==0) break;
 
	while(xx!=0)
			{
			incr = min(tmp[par[xx]][xx],incr);	
			xx = par[xx];	
			}
	xx = n-1;		
	while(xx!=0)	
			{
			tmp[par[xx]][xx] -= incr;	
			tmp[xx][par[xx]] += incr;
			xx = par[xx];
			}
	
 
	flow += incr;		
	}
return flow;			
}
 
int main()
{
ios_base::sync_with_stdio(0); cout.precision(15);cout.setf(ios::fixed);
int i,j,m;
cin>>n>>m;
int a,b,c;
 
fillchar(g,0);
 
for(i=0;i<m;i++)
	{
	cin>>a>>b>>c;	
	a--;b--;
	g[a][b] += c;  //undirected graph
	g[b][a] += c;
	}
 
for(i=0;i<n;i++)
	for(j=0;j<n;j++)
		tmp[i][j] = g[i][j];
 
cout<<ff()<<endl;
 
}
 