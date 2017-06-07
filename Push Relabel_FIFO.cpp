#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'

const LL M = (LL)1e9+7;

const int N = 5005;

//push relabel with FIFO -- I need gap heurestic!
// O(n^3)

LL g[N][N];
int he[N];
LL sto[N];
int n;

int main()
{
int i,j,m;

scanf("%d %d",&n,&m);

int a,b,c;

for(i=0;i<m;i++)
	{
		scanf("%d %d %d",&a,&b,&c);

		if(a==b) continue;

		g[a][b] += c;  //undirected
		g[b][a] += c;	 
	}


//source is 1 sink is n

he[1] = n;

//for begining make s and t disconnected
LL sum = 0;
queue  <int> q;

for(i=2;i<=n;i++)
	{
	sum += g[1][i];	
	g[i][1] += g[1][i];
	sto[i] = g[1][i];
	g[1][i] = 0; 	

	if(sto[i]>0 && i!=n)
		q.push(i);
	}

int v;

while(q.size())
	{	
	v = q.front();

	//push
	for(i=1;i<=n;i++)
		if(g[v][i]>0 && he[v]>he[i])
			{
			LL k = min(g[v][i],sto[v]);
			sto[v] -= k;
			g[v][i] -= k;
			g[i][v] += k;

			if(sto[i]==0 && i!=1 && i!=n)
				q.push(i);	

			sto[i] += k;

			if(sto[v]==0) break;
			}
		
	//relabel 	
	if(i==n+1)
		he[v]++;	
	else 
		q.pop();
	}

printf("%lld\n",sum-sto[1]);
}
