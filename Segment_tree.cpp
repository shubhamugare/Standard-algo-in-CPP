const int N = 200001;

int tree[4*N];

vector <int> shas;

void build(int x,int l,int r)
{
	int m;
// cout << l << ' ' << r << endl;

	if(l<r)
	{
		m=(l+r) >> 1;
		build(2*x,l,m);	
		build(2*x+1,m+1,r);
		tree[x]=tree[2*x]+tree[2*x+1];
	}
else
	{
	// cout << l << ' ' << shas[l] << endl;	
		tree[x] = shas[l];
	}
}

void update(int x,int l,int r,int loc,int data)
{
	int m;
	if (l<=loc &&  loc<=r  && l<r)  
	{
		m=(l+r) >> 1;

		update(2*x,l,m,loc,data);
		update(2*x+1,m+1,r,loc,data);

		tree[x]=tree[2*x] + tree[2*x+1];
	}
	else if(l==r && l==loc)
	{
		tree[x] = data;
		shas[l] = data;
	}
	
	else
	return ;
}

int  get(int x,int l,int r,int ll,int rr)
{
	int m;
	if (ll<=l &&  r<=rr)  
		return tree[x];
	if( rr<l || ll>r )
	     return 0;
 	else
 	{
 		m=(l+r) >> 1;
 		return get(2*x,l,m,ll,rr) + get(2*x+1,m+1,r,ll,rr);
	}
}
