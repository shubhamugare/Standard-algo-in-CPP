#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'

const int N = 5005;
const int M = 60005;



 //push relabel with FIFO -- I need gap heurestic!
 // O(n*m) 
// invariant : h[1] = n  , h[n] = 0, 

vector <pair<int,int> > g[N];
LL cap[M];
int he[N];
LL sto[N];
int n;

int main()
{
int i,j,m;

scanf("%d %d",&n,&m);

int a,b,c;

int nid = 0;

for(i=0;i<m;i++)
	{
		scanf("%d %d %d",&a,&b,&c);

		if(a==b) continue;

		g[a].PB(MP(b,nid));
		g[b].PB(MP(a,nid^1));

		// cout<<a<<' '<<b<<endl;

		cap[nid] += c;
		cap[nid^1] += c;

		nid+=2;

		// g[a][b] += c;  //undirected
		// g[b][a] += c;	 
	}


//source is 1 sink is n

he[1] = n;

//for begining make s and t disconnected
LL sum = 0;
queue  <int> q;

for(i=0;i<g[1].size();i++)
	{
	int id = g[1][i].second;
	int to = g[1][i].first;	

	sum += cap[id];	
	cap[id^1] += cap[id];
	
	if(sto[to]==0 && cap[id]>0 && to!=n)
		{
		q.push(to);	
		//cout<<to<<endl;
		}

	sto[to] += cap[id];
	cap[id] = 0; 	
	}


int v;

while(q.size())
	{	
	v = q.front();

	// cout<<v<<' '<<he[v]<<' '<<sto[v]<<' '<<g[v].size()<<endl;

	//push
	for(i=0;i<g[v].size();i++)
		if(cap[g[v][i].second]>0 && he[v]>he[g[v][i].first])
			{
			int id = g[v][i].second;
			int to = g[v][i].first;		
			LL k = min(cap[id],sto[v]);
			sto[v] -= k;
			cap[id] -= k;
			cap[id^1] += k;

			if(sto[to]==0 && to!=1 && to!=n)
				q.push(to);	

			sto[to] += k;

			if(sto[v]==0) break;
			}
		
	//relabel 	
	if(i==g[v].size())
		he[v]++;	
	else 
		q.pop();
	}

printf("%lld\n",sum-sto[1]);
}
