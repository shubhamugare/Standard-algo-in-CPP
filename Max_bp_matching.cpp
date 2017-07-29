#include <bits/stdc++.h>
 
using namespace std;
 
const int LEFT = 5000, RIGHT = 5000;
 
vector<int> G[LEFT];
int match[LEFT], par[RIGHT];
bool used[LEFT];
 
bool mdfs(int v) 
{
	if (used[v]) return false;

	used[v] = true;
	
	for (int i=0;i<G[v].size();i++)
	{
		u = G[v][i];

		if (par[u] == -1 || mdfs(par[u])) 
		{
			match[v] = u;
			par[u] = v;
			return true;
		}
	}	
	return false;
}
 
int max_match(int left, int right)
 {
	memset(match, -1, sizeof(int) * left);
	memset(par, -1, sizeof(int) * right);
	bool run = true;
	int size = 0;
	
	while (run) 
	{
		memset(used, 0, sizeof(bool) * left);
		run = false;
		
		for (int i = 0; i < left; i++)
			if (match[i] == -1 && mdfs(i)) 
			{
				size++;
				run = true;
			}
	}
	return size;
}