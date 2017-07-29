/* dinic */
 
const int INF = 2000000000; // greater than max capacity
const int maxn = 5005;
 
struct edge {
	int from, to, cap, flow;
};
 
vector<edge> edges;
vector<int> G[maxn];
 
int q[maxn];
int d[maxn];
 
bool bfs(int s, int t) {
	memset(d, -1, sizeof d);
	int qh = 0, qt = 0;
	q[qt++] = s;
	d[s] = 0;
	while(qh != qt) {
		int cur = q[qh++];
		for(int i = 0; i < (int)G[cur].size(); ++i) {
			edge& e = edges[G[cur][i]];
			if(e.flow != e.cap && d[e.to] == -1) {
				q[qt++] = e.to;
				d[e.to] = d[cur] + 1;
			}
		}
	}
	return d[t] != -1;
}
 
int ptr[maxn];
 
int dfs(int v, int t, int mx) {
	if(!mx)
		return mx;
 
	if(v == t)
		return mx;
 
	for(int& i = ptr[v]; i < (int)G[v].size(); ++i) {
		int id = G[v][i];
		edge& e = edges[id];
		if(d[e.to] == d[v] + 1) {
			if(int pushed = dfs(e.to, t, min(mx, int(e.cap - e.flow)))) {
				e.flow += pushed;
				edges[id ^ 1].flow -= pushed;
				return pushed;
			}
		}
	}
	return 0;
}
 
li dinic(int s, int t) {
	li res = 0;
	while(bfs(s, t)) {
		memset(ptr, 0, sizeof ptr);
 
		while(int pushed = dfs(s, t, INF)) {
			res += pushed;
		}
	}
	return res;
}
 
void add_edge(int from, int to, int cap) {
	edge e1 = {from, to, cap, 0};
	edge e2 = {to, from, 0,0};
	G[from].push_back(edges.size());
	edges.push_back(e1);
	G[to].push_back(edges.size());
	edges.push_back(e2);
}
 
/* end dinic */
	edges.clear();
	for(int i=0;i<n+m+2;i++)
			G[i].clear();
    add_edge(n + 2 + i, x, 1);
    int flow = dinic(source, sink);
    cout << flow << endl;