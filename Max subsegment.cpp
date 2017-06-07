#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'

const int M = (int)1e9+7;
const int N = 200001;


struct pt{
	int msum;
	int esum;
	int ssum;
	int elen;
	int slen;
	int mlen;
	int sz;
	int sum;
};

pt nool = {-M,-M,-M,0,0,0,0,0};

pt operator+(pt a,pt b)
{
pt c;

if(a.sz==0) return b;
else if(b.sz==0) return a;

c.sz = a.sz + b.sz;
c.sum = a.sum + b.sum;
//calculating msum
if(a.msum>b.msum || (a.msum==b.msum && a.mlen>b.mlen))
	{c.msum = a.msum;c.mlen = a.mlen;}
else 
	{c.msum = b.msum;c.mlen = b.mlen;}

if(a.esum+b.ssum > c.msum || (a.esum+b.ssum==c.msum && a.elen+b.slen>c.mlen))
	{c.msum =a.esum+b.ssum;c.mlen = a.elen+b.slen;}

// cout<<a.sz<<' '<<b.sz<<endl;
// cout<<a.msum<<' '<<b.msum<<' '<<c.msum<<endl;

//calculating ssum
c.ssum = a.ssum;c.slen = a.slen;
if(a.sum+b.ssum>c.ssum || (a.sum+b.ssum==c.ssum && a.sz+b.slen>c.slen))
	{c.slen=a.sz+b.slen; c.ssum = a.sum+b.ssum;}


//calculating esum
c.esum = b.esum;c.elen = b.elen;
if(b.sum+a.esum>c.esum || (b.sum+a.esum==c.esum && b.sz+a.elen>c.elen))
	{c.esum=b.sum+a.esum;c.elen=b.sz+a.elen;}

return c;

}

pt tree[4*N];

vector <int> v;

void build(int x,int l,int r)
{
int m;

if(l<r)
	{
	m=(l+r) >> 1;
	build(2*x,l,m);	
	build(2*x+1,m+1,r);
	tree[x]=tree[2*x]+tree[2*x+1];

			// cout<<"shas"<<' '<<l<<' '<<r<<' '<<tree[x].sz<<endl; 

	}
else
	{
	// cout << l << ' ' << shas[l] << endl;	
	tree[x].msum = tree[x].ssum = tree[x].esum = tree[x].sum = v[l];
	tree[x].slen = tree[x].elen = tree[x].mlen = 1;
	tree[x].sz=1;
	}
}



pt  get(int x,int l,int r,int ll,int rr)
{
	int m;
 if (ll<=l &&  r<=rr)  
	{
		// cout<<"fuck"<<' '<<l<<' '<<r<<' '<<tree[x].esum<<endl; 
		return tree[x];
	}
if( rr<l || ll>r )
	 {		
	 // cout<<2<<' '<<nool.sz<<endl; 
    return nool;
	}
 else
 	{
 	m=(l+r) >> 1;
 	return get(2*x,l,m,ll,rr) + get(2*x+1,m+1,r,ll,rr);
	}
}


int main()
{
int n,q;

scanf("%d",&n);

v.resize(n);

int i;

for(i=0;i<n;i++)
	scanf("%d",&v[i]);

build(1,0,n-1);


scanf("%d",&q);

int a,b;
pt ans;

for(i=0;i<q;i++)
	{
	scanf("%d%d",&a,&b);
	a--;b--;	
	ans = get(1,0,n-1,a,b);

	printf("%d %d\n",ans.msum,ans.mlen);

	}

}
