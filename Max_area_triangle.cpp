#include<bits/stdc++.h>
 
typedef long long LL;  //Attention!!
using namespace std;
 
#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'
 
const int M = 1000000007;
 
struct pt
{
LL xx;LL yy;
 
bool operator<(const pt &b)
const {
		return (xx < b.xx);
    	};
 
pt operator + (pt &b)
	{
	pt c;
	c.xx = xx + b.xx;
	c.yy = yy + b.yy;
	return c;
	};
 
pt operator - (pt &b)
	{
	pt c;
	c.xx = xx - b.xx;
	c.yy = yy - b.yy;
	return c;
	};
 
};
 
 
vector <pt> v,ch;
pt pivot;
 
LL ccw(pt a,pt b,pt c)
{
if((c.xx-b.xx)*(b.yy-a.yy)-(c.yy-b.yy)*(b.xx-a.xx)<0)
	return 1;
else if((c.xx-b.xx)*(b.yy-a.yy)-(c.yy-b.yy)*(b.xx-a.xx)>0)
	return -1;
else
	return 0;
}
 
LL Area(pt a,pt b,pt c)  //this actually give area *2
{
return abs((c.xx-b.xx)*(b.yy-a.yy)-(c.yy-b.yy)*(b.xx-a.xx)); 
}
 
bool myfun(const pt &a,const pt &b)
{
return a.yy < b.yy;
}
 
bool myfun2(const pt &a,const pt &b)
{
int k=ccw(a,pivot,b);
 
if(k==-1)   //right turn means b makes bigger angle
	return true;
else if(k==1)
	return false;
else if(k==0)
	return a.xx<b.xx;
}
 
pt top2(stack <pt> &s)
{
	pt p,q;
	p=s.top();
	s.pop();
	q=s.top();
	s.push(p);
	return q;
}
 
void convex_hull()
{
sort(v.begin(),v.end());
sort(v.begin(),v.end(),myfun);
pivot=v[0];
sort(v.begin()+1,v.end(),myfun2);
stack <pt> s;
pt temp;
 
s.push(v[0]);
s.push(v[1]);
 
for(LL i=2;i<v.size();i++)
	{
				
	while(ccw(top2(s),s.top(),v[i])!=1)   //if I pass it as reference it will be difficult
		s.pop();
	
	s.push(v[i]);		
	}
 
while(!s.empty())
	{ch.PB(s.top());
	s.pop();	
	}
}
 
LL p1,p2,ma=0,a1=0,a2=1,a3=2;
 
void tern(LL l,LL h)
{
LL m;
 
while(l+1 < h)
{
m = (l+h)>>1;
 
LL x = Area(ch[p1],ch[p2],ch[m]);
 
LL y = 0;
 
if(m+1<ch.size())
	 y = Area(ch[p1],ch[p2],ch[m+1]);
 
if(x<y)
	l = m;
else
	h = m;
 
}
 
 
if(l>=0 && l<ch.size() && ma < Area(ch[p1],ch[p2],ch[l]))
	{
	ma = Area(ch[p1],ch[p2],ch[l]);	
	a1 = p1; a2 = p2; a3 = l;
	}			
 
if(h>=0 && h<ch.size() && ma < Area(ch[p1],ch[p2],ch[h]))
	{
	ma = Area(ch[p1],ch[p2],ch[h]);
	a1 = p1; a2 = p2 ; a3 = h;	
	}
 
}
 
 
 
int main()
{
ios_base::sync_with_stdio(0); cout.precision(15);cout.setf(ios::fixed);
LL t,n,i,j,m,s;
 
while(t--)
{
cin>>n;
 
if(n==-1) return 0;
 
v.resize(n);
ch.clear();
 
for(i=0;i<n;i++)
	cin>>v[i].xx>>v[i].yy;
 
convex_hull();
 
n = ch.size();
 
//for(i=0;i<n;i++)
//	cout<<ch[i].xx<<' '<<ch[i].yy<<endl;
 
LL maa = 0,a11=0,a22=1,a33=2;
 
 
for(i=0;i<n;i++)
	{
	ma = 0;	
 
	p1 = min(i,(i+1)%n);
	p2 = max(i,(i+1)%n);	
 
	tern(p2,n);
	tern(-1,p1);
 
	p1 = min(a1,a3);
	p2 = max(a1,a3);
 
	tern(p1,p2);
	tern(-1,p1);
	tern(p2,n);
 
	if(ma > maa)
		{
		a11 = a1;	
		a22 = a2;
		a33 = a3;
		maa = ma;
		}
 
	}
 
double pu = 0.5 * maa;
 
cout<<pu<<endl;
 
pt ans1=ch[a1],ans2=ch[a2],ans3=ch[a3];
 
ans1 = ch[a11] + ch[a22] - ch[a33];
ans2 = ch[a11] + ch[a33] - ch[a22];
ans3 = ch[a33] + ch[a22] - ch[a11];
 
}
//cout<<ans1.xx<<' '<<ans1.yy<<endl;
//cout<<ans2.xx<<' '<<ans2.yy<<endl;
//cout<<ans3.xx<<' '<<ans3.yy<<endl;
 
}
 
 