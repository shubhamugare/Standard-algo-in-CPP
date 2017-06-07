#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n' 
 
const int M = 1000000007;
 
struct point{
LL xx;LL yy;LL zz;
 
bool const operator < (const point &b)
const {
return xx < b.xx;
}
};
 
bool myfun(const point& a,const point& b)
{
return a.yy < b.yy;
}
 
const int N = 2000001;
LL tree[N],L[N],R[N];
LL next;
vector <point> v;
 
 
void build(LL ID,LL l,LL r)
{
tree[ID] = 0;
LL m = (l+r)>>1;
 
if(l<r)
{
L[ID] = next++;
build(L[ID],l,m);
R[ID] = next++;
build(R[ID],m+1,r);
}
else
	{L[ID] = -1;R[ID] = -1;}
}
 
void update(LL ID,LL id,LL l,LL r,LL loc)  //new ID and old id
{
LL m = (l+r)>>1;
 
if(l==r)
	{
	tree[ID] = 1;
	return;	
	}
 
L[ID] = L[id];
R[ID] = R[id];
 
if(l<=loc && loc<=m)
	{L[ID] = next++;
	update(L[ID],L[id],l,m,loc);
	}
if((m+1)<=loc && loc<=r)
	{R[ID] = next++;
	update(R[ID],R[id],m+1,r,loc);	
	}
tree[ID] = tree[L[ID]] + tree[R[ID]];
 
}
 
LL get(LL id,LL ID,LL k,LL l,LL r)
{
if(l==r) return v[l].xx;
 
LL mid = (l+r)>>1;
 
//cout<<tree[L[ID]] - tree[L[id]]<<' '<<k<<' '<<l<<' '<<r<<endl;
 
if(tree[L[ID]]-tree[L[id]] >= k) 
		return get(L[id],L[ID],k,l,mid);
else	
		return get(R[id],R[ID],k-(tree[L[ID]]-tree[L[id]]),mid+1,r);
}
 
 
int main()
{
LL n,i,j,m;
ios_base::sync_with_stdio(0); cout.precision(15);cout.setf(ios::fixed);
 
cin>>n>>m;
 
v.resize(n);
 
for(i=0;i<n;i++)
	{cin>>v[i].xx;
	v[i].yy = i;	
	}	
 
sort(v.begin(),v.end());
 
for(i=0;i<n;i++)
	v[i].zz = i;
 
sort(v.begin(),v.end(),myfun);
 
next = 2;
 
build(1,0,n-1);
 
vector <LL> ind(n+1);
ind[0] = 1;
 
for(i=1;i<=n;i++)
	{
	ind[i] = next++;	
	update(ind[i],ind[i-1],0,n-1,v[i-1].zz);
		//ID and then location
	}//we set original v[i]'s position in sorted as 1
 
LL a,b,c;
 
sort(v.begin(),v.end());
 
for(i=0;i<m;i++)
	{
	cin>>a>>b>>c;
	a--;
	cout<<get(ind[a],ind[b],c,0,n-1)<<endl;	
	}
 
}
 