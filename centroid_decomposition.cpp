#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'

const int M = (int)1e9+7;
const int N = (int)1e5+7;

int cnt;
set <int> g[N];
int ans[N];
int subtree[N];

void dfs(int s,int par)
{	
	cnt++;
	subtree[s] = 1;
	for(int nd: g[s])
	{
		if(nd == par) continue;
		dfs(nd,s);
		subtree[s] += subtree[nd];
	}	
}

int center(int s,int par)
{	
	for(int nd: g[s])
	{
		if(nd==par) continue;
		if(subtree[nd] > cnt)
			return center(nd,s);
	}
	return s;	
}

void decompose(int s,int par)
{	
	cnt = 0;
	dfs(s,par);
	cnt >>= 1;
	//updated the subtree sizes, now find the center
	int ct = center(s,par);
	ans[ct] = (par == -1 ? 0 : ans[par] + 1);

	for(int nd :g[ct])
	{
		if(nd == par) continue;

		g[nd].erase(ct);
		decompose(nd,ct);
	}	
}

int main()
{
	//ios_base::sync_with_stdio(0); 
	cout.precision(15);
	cout.setf(ios::fixed);

	int n;
	cin >> n;

	int a,b;

	for(int i=0;i<n-1;i++)
	{
		cin >> a >> b;
		a--;b--;
		g[a].insert(b);
		g[b].insert(a);
	}

	decompose(0,-1);

	for(int i=0;i<n;i++)
		cout<<(char)('A'+ans[i])<<' ';
	cout<<endl;
}
