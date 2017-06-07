    #include<bits/stdc++.h>
     
    typedef int LL;  //Attention!!
    using namespace std;
     
    #define fillchar(a, x) memset(a, x, sizeof(a))
    #define MP make_pair
    #define PB push_back
    #define endl '\n'
     
    const int M = 1000000007;
    const int N = 1e4 + 5;
     
    vector <LL> g[N];
    LL depth[N],sz[N],par[N];
    LL root[N],heavy[N],treepos[N],wt[N],revpos[N];
    LL tree[4*N];
     
    void build(LL x,LL l,LL r)
    {
    LL m;
     
    if(l<r)
    	{m=(l+r) >> 1;
    	build(2*x,l,m);	
    	build(2*x+1,m+1,r);
    	tree[x]=max(tree[2*x],tree[2*x+1]);
    	}
    else
    	{tree[x] =  wt[revpos[l]]; }
    }
     
     
    void update(LL x,LL l,LL r,LL loc,LL data)
    {
    LL m;
     
    if(l<=loc &&  loc<=r  && l<r)  
    	{
    	m=(l+r) >> 1;
    	update(2*x,l,m,loc,data);
    	update(2*x+1,m+1,r,loc,data);
    	tree[x]=max(tree[2*x],tree[2*x+1]);
    	}
    else if(l==r && l==loc)
    	{
    	tree[x]=data;
    	}
    else
    	return ;
    }
     
    LL  get(LL x,LL l,LL r,LL ll,LL rr)
    {
    LL m;
    if (ll<=l &&  r<=rr)  
    	{
    	return tree[x];
    	}
    if( rr<l || ll>r )
         return -1*M;
     
     else
     	{	m=(l+r) >> 1;
     		return max(get(2*x,l,m,ll,rr),get(2*x+1,m+1,r,ll,rr));
     	}
    }
     
     
    void predfs(LL s)
    {
    LL maxsubtree = 0;	
    sz[s] = 1;
    for(LL j=0;j<g[s].size();j++)
    	{
    	LL node = g[s][j];
     
    	if(node!=par[s])	
    		{
    		par[node] = s;	
    		depth[node]	= depth[s] + 1;
    		predfs(node);
    		sz[s] += sz[node];
    		if(sz[node]>maxsubtree)  heavy[s] = node , maxsubtree = sz[node] ; 
    		}	
     
    	}	
    }
     
    void HLD(LL n)
    {
    LL i,j;
    LL curr = 0;
     
    for(i=0;i<n;i++)
    	if(par[i]==-1 || heavy[par[i]]!=i)
    		for(j=i;j!=-1;j = heavy[j])
    			{
    			root[j] = i;	
    			revpos[curr] = j;
    			treepos[j] = curr++;
    			}
     
    build(1,1,n-1);
    }
     
    void process_update(LL u,LL n,LL val)
    {
    update(1,1,n-1,treepos[u],val);
    }
     
     
    LL process_get(LL u,LL v,LL n)
    {
    LL val = 0;
     
    for(;root[u] != root[v];v = par[root[v]])
    	{
    	if(depth[root[u]] > depth[root[v]])  swap(u,v);	
    		val = max(val,get(1,1,n-1,treepos[root[v]],treepos[v]));
    	}
     
    if (depth[u] > depth[v]) swap(u, v);
    	
    val = max(val,get(1,1,n-1,treepos[heavy[u]],treepos[v]));  //will change depending on values are stored in node or edges..
    	//if values are for edges then bottom node represents that edge so above code will not work change u to heavy[u]
    //else treepos[u] is correct
    //will change depending on values are stored in node or edges..
    //make 1,1,n-1 if corresponding to edges as 0 doesnt haave an edge
     
    return val;
    }
     
    struct three {LL a;LL b;LL c;};
     
    int main()
    {
     
    LL n,i,j,m;
    LL t;
     
    cin>>t;
     
    while(t--)
    {
    cin>>n;
     
    //cout<<n<<endl;
     
    vector <three> v;
    LL a,b,c;
     
    for(i=0;i<n;i++)
     	g[i].clear();	
     	
     
    //take graph
    for(i=0;i<(n-1);i++)
    		{
    		scanf("%d%d%d",&a,&b,&c);	
    		a--;b--;
    		g[a].PB(b);
    		g[b].PB(a);
    		three tmp = {a,b,c};
    		v.PB(tmp);
    		}
     
     
    for(i=0;i<n;i++)
    		heavy[i] = -1;
     
    depth[0] = 0;
    par[0] = -1;
     
     
    predfs(0);
     
    for(i=0;i<(n-1);i++)
    	{
    	if(v[i].a==par[v[i].b])  wt[v[i].b] = v[i].c;
    	else wt[v[i].a] = v[i].c;	
    		
    	//cout<<i<<' '<<a<<' '<<b<<' '<<c<<endl;	
    	}
     
    //for(i=0;i<n;i++) cout<<wt[i]<<' '; cout<<endl;
     
     
    HLD(n);
     
    char s[10];
     
    while(true)
    	{
    	scanf("%s",s);
    //	cout<<s<<endl;
    	
    	if(s[0]=='D') break;	
     
    	scanf("%d%d",&a,&b);
     
    	 if(s[0]=='C') {
    		a--;
    		LL qt;
    		
    		if(v[a].a==par[v[a].b]) qt = v[a].b;
    		else qt = v[a].a;  
     
    		//cout<<qt<<' '<<b<<endl;
     
    		process_update(qt,n,b);
    		}
     
    	else if(s[0]=='Q')	
    		{
    		a--;b--;
    		LL ans = process_get(a,b,n);
    		
    		printf("%d\n",ans);
    		}
     
    	}
     
    //cout<<t<<' '<<n<<endl;
     
    }
     
    }
     
     