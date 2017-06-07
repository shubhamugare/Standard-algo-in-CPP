//Author :: shas19
 
#include<bits/stdc++.h>
 
typedef long long LL;
using namespace std;
const int M = 1000000007;
const int N = 400001;
 
int tree[4*N],lazy[4*N];
 
vector <int> v;
 
int build(int x,int l,int r)
{
	int m;
	m= (l+r) >> 1;

	lazy[x]=0;

	if(l<r)
	{
		build(2*x,l,m);
		build(2*x+1,m+1,r);

		tree[x]=tree[2*x] + tree[2*x+1];
	}
	else
	tree[x]=v[l];
 }
 
//lazy propagation;
 
void update(int x,int l,int r,int ll,int rr,int d)
{
	int m;

	m= (l+r) >> 1;


	if(lazy[x]!=0)
	{
		tree[x]+=lazy[x]*(r-l+1);

		lazy[2*x]+=lazy[x];
		lazy[2*x+1]+=lazy[x];

		lazy[x]=0;
	}

	if(rr<l || ll>r)
		return ;

	if (ll<=l &&  r<=rr )
	{	
		tree[x]+=d*(r-l+1);
		lazy[2*x]+=d;
		lazy[2*x+1]+=d;
	}
	else
	{
	update(2*x,l,m,ll,rr,d);
	update(2*x+1,m+1,r,ll,rr,d);
	tree[x]=tree[2*x]+tree[2*x+1];
	}
}
 
 
int get(int x,int l,int r,int ll,int rr)
{
	int m;
	m= (l+r) >> 1;
 
	if(lazy[x]!=0)
	{
		tree[x]+=lazy[x]*(r-l+1);
 
		lazy[2*x]+=lazy[x];
		lazy[2*x+1]+=lazy[x];
 
		lazy[x]=0;
 	}
 
 	if(ll<=l && r<=rr)
		return tree[x];
 
	else if(ll>r || rr<l )
		return 0;
 	else
		return get(2*x,l,m,ll,rr) + get(2*x+1,m+1,r,ll,rr);
}
 
 
 
int main()
{
int t,n,i,m,a,b,c,d;
 
cin>>t;
 
while(t--)
 
{
cin>>n>>m;
 
//m querries
 
v.resize(n);
 
for(i=0;i<n;i++)
	v[i]=0;
 
 
 
build(1,0,n-1);
/*
for(i=0;i<n;i++)	
	cout<<tree[i]<<endl;
*/
 
for(i=0;i<m;i++)
{
//1 for get and 2 for update
cin>>a;
 
 
if(a==1)
	{
	  cin>>b>>c;	 //range
	  b--;c--;
	  	                
	  cout<<get(1,0,n-1,b,c)<<endl;
	}
 
if(a==0)
	{
 
	cin>>b>>c>>d;			//add d in all locations between b to c	
	b--;c--;
	update(1,0,n-1,b,c,d);
 
	}
 
}
 
}
 
}
 
 