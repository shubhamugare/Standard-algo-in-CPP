int par[N],rk[N];

void make(int v) 
	{
	par[v] = v;
	rk[v] = 0;
	}
 
int find(int v) 
	{
	if (v == par[v])
		return v;
	return par[v] = find(par[v]);
	}
 
void uni(int a, int b) 
	{
	a = find(a);
	b = find(b);
	if (a != b) 
		{
		if (rk[a] < rk[b])
			swap (a, b);
		par[b] = a;
		if (rk[a] == rk[b])
			++rk[a];
		}
	}
