#include<bits/stdc++.h>
 
typedef long long LL;  //Attention!!
using namespace std;
 
#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'
 
//int MODS[] = {999999937,999999929};
 
int MODS[] = {(int)1e6+3,(int)1e6+1723};
int RK[] = {31,37};
const int sz = 2;
 
//int MODS[] = {999999937};
//int RK[] = {31};
//const int sz = 1;
 
LL powa(LL a,LL b,LL M)
{
if(b==0) return 1;
if(b%2 == 1) return (powa(a,b-1,M)*a)%M;
 
LL c = powa(a,b/2,M);
return (c*c)%M;
}
 
void prehash(string &s,vector <vector <LL> > &hashv)
{
int n = s.size();
hashv.resize(sz);
 
for(int j=0;j<sz;j++) hashv[j].resize(n);
 
vector <LL> curp(sz);

for(int j=0;j<sz;j++) curp[j] = 1;

 
for(int i=0;i<n;i++)
	for(int j=0;j<sz;j++)		
		{
		hashv[j][i] = ( (i>0 ? hashv[j][i-1] : 0) + curp[j]*s[i] )%MODS[j]; 	
		curp[j] = (curp[j]*RK[j])%MODS[j];  	
		}
 
}
 
 
//for substring
void get_hash(int a,int b,vector <vector <LL> > &hashv,vector <LL> &ans)
{
ans.resize(sz);	
for(int j=0;j<sz;j++)
	{
	ans[j] = ((hashv[j][b]-(a>0 ? hashv[j][a-1] : 0 ) )*powa(RK[j],MODS[j]-a,MODS[j]))%MODS[j];	
	if(ans[j]<0) ans[j] += MODS[j];  //never forget this for modulo subtraction..
	}
}
 
/*
void quick_hash(string &s,vector <LL> &ans)
{
int n = s.size();	
ans.resize(sz);
vector <LL> curp(sz,1);
 
for(int i=0;i<n;i++)
	for(int j=0;j<sz;j++)		
		{
		ans[j] = (ans[j] + curp[j]*s[i])%MODS[j]; 	
		curp[j] = (curp[j]*RK[j])%MODS[j]; 	
		}
}
*/
 
vector <vector <LL> > hashv,hashrv;
vector <LL> ans1,ans2;
 
bool ispalindrome(int a,int b,int n )
{
get_hash(a,b,hashv,ans1);
get_hash(n-b-1,n-a-1,hashrv,ans2);
 
for(int j=0;j<ans1.size();j++)
	{
	 if(ans1[j]!=ans2[j])
		return false;
	}	
return true;	
}
 
int main()
{
ios_base::sync_with_stdio(0); 
cout.precision(15);
cout.setf(ios::fixed);
 
//clock_t start,end;
//start = clock();
 
int n,k,i,j;
string s,t;
 
cin>>n;
cin>>s;
 
n = s.size();
 
t = s;
 
reverse(t.begin(),t.end());
 
 
 
prehash(s,hashv);
prehash(t,hashrv);
 
int si = 0;
 
//for odd 
vector <int> perm;
for(i=0;i<n;i++) perm.PB(i);
random_shuffle(perm.begin(),perm.end());
 
for(i=0;i<n;i++)
	{
	LL l=0,h=min(perm[i],n-1-perm[i]),mid;
	if(h==0 || s[perm[i]-1]!=s[perm[i]+1]) continue;
 
	while(l<h)
		{mid = (l+h+1)/2;
		if(2*h + 1 <= si) break;  //optimizations	
		if(ispalindrome(perm[i]-mid,perm[i]+mid,n ))	
			l = mid;
		else
			h = mid - 1;
		 
		}	
	if(2*l + 1 > si)  {si = 2*l + 1;}
	}
 
//for even
for(i=0;i<(n-1);i++)
	{if(s[i]!=s[i+1]) continue;
	
	LL l=0,h=min(i,n-2-i),mid;
	
	while(l<h)
		{mid = (l+h+1)/2;
		if(2*h + 2 <= si) break;  //optimizations	
		if(ispalindrome(i-mid,i+1+mid,n))	
			l = mid;
		else
			h = mid - 1;
		}	
	if(2*l + 2 > si)  {si = 2*l + 2;}
	}
 
cout<<si<<endl;
 
//end = clock();
//cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
 
}
 
 