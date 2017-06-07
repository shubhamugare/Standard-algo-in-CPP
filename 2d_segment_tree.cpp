 
#include<bits/stdc++.h>
 
typedef long long LL;  //Attention!!
using namespace std;
 
#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'
 
const int M = 1000000007;
 
const int N  = 1024;
int tree[N][N] , arr[N][N];
int n,m;
 
 
void build_y (int vx, int lx, int rx, int vy, int ly, int ry) {
	if (ly == ry)
		if (lx == rx)
			tree[vx][vy] = arr[lx][ly];
		else
			tree[vx][vy] = tree[vx*2][vy] + tree[vx*2+1][vy];
	else {
		int my = (ly + ry) / 2;
		build_y (vx, lx, rx, vy*2, ly, my);
		build_y (vx, lx, rx, vy*2+1, my+1, ry);
		tree[vx][vy] = tree[vx][vy*2] + tree[vx][vy*2+1];
	}
}
 
void build_x (int vx, int lx, int rx) {
	if (lx != rx) {
		int mx = (lx + rx) / 2;
		build_x (vx*2, lx, mx);
		build_x (vx*2+1, mx+1, rx);
	}
	build_y (vx, lx, rx, 1, 0, m-1);
}
 
int sum_y (int vx, int vy, int tly, int try_, int ly, int ry) {
	if (ly > ry)
		return 0;
	if (ly == tly && try_ == ry)
		return tree[vx][vy];
	int tmy = (tly + try_) / 2;
	return sum_y (vx, vy*2, tly, tmy, ly, min(ry,tmy))
		+ sum_y (vx, vy*2+1, tmy+1, try_, max(ly,tmy+1), ry);
}
 
 // tlx and tly are for node ..others are queary parameters..
int sum_x (int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
	if (lx > rx)
		return 0;
	if (lx == tlx && trx == rx)
		return sum_y (vx, 1, 0, m-1, ly, ry);
	int tmx = (tlx + trx) / 2;
	return sum_x (vx*2, tlx, tmx, lx, min(rx,tmx), ly, ry)
		+ sum_x (vx*2+1, tmx+1, trx, max(lx,tmx+1), rx, ly, ry);
}
 
void update_y (int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
	if (ly == ry) {
		if (lx == rx)
			tree[vx][vy] = new_val;
		else
			tree[vx][vy] = tree[vx*2][vy] + tree[vx*2+1][vy];
	}
	else {
		int my = (ly + ry) / 2;
		if (y <= my)
			update_y (vx, lx, rx, vy*2, ly, my, x, y, new_val);
		else
			update_y (vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
		tree[vx][vy] = tree[vx][vy*2] + tree[vx][vy*2+1];
	}
}
 
void update_x (int vx, int lx, int rx, int x, int y, int new_val) {
	if (lx != rx) {
		int mx = (lx + rx) / 2;
		if (x <= mx)
			update_x (vx*2, lx, mx, x, y, new_val);
		else
			update_x (vx*2+1, mx+1, rx, x, y, new_val);
	}
	update_y (vx, lx, rx, 1, 0, m-1, x, y, new_val);
}
 
int main()
{
int t;
scanf("%d",&t);
 
int q,ans;
char st[10];
int a,b,c,d;
int i,j;
 
while(t--)
{
scanf("%d",&n);
 
m = n;
 
for(i=0;i<n;i++)
	for(j=0;j<n;j++)
		arr[i][j] = 0;
 
build_x(1,0,n-1);
 
while(q--)
	{
	scanf("%s",st);
	if(st[0] == 'E') break;
 
	if(st[1] == 'E')	
		{
		scanf("%d%d%d",&a,&b,&c);
		//a--,b--;	
		update_x(1,0,n-1,a,b,c);
		//ans = sum_x(1,0,n-1,a,a,b,b);
		//printf("%d\n",ans);
		}
	if(st[1] == 'U')	
		{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		//a--,b--,c--,d--;	
		ans = sum_x(1,0,n-1,a,c,b,d);
		printf("%d\n",ans);
		}
	}
 
}
 
}
 