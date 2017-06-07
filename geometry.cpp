#include<bits/stdc++.h>

//taken from cf coder toodifficult!

typedef long long LL;  
using namespace std;

#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'

const int M = (int)1e9+7;

#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())

typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;

ll powmod(ll a,ll b) {ll res=1;a%=M; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%M;a=a*a%M;}return res;}
// head


const double eps=1e-9;
const double pi=acos(-1.0);
const double inf=1e20;
const int maxp=1111;

int dblcMP(double d) {
	if (fabs(d)<eps)return 0;
	return d>eps?1:-1;
}

inline double sqr(double x){return x*x;}

struct point {
	double x,y;
	point(){}
	
	/* constructor for point */
	point(double _x,double _y):
	x(_x),y(_y){};
	
	void input() 
	{
		scanf("%lf%lf",&x,&y);
	}
	
	void output() 
	{
		printf("%.10f %.10f\n",x,y);
	}
	bool operator==(point a)const 
	{
		return dblcMP(a.x-x)==0&&dblcMP(a.y-y)==0;
	}
	bool operator<(point a)const 
	{
		return dblcMP(a.x-x)==0?dblcMP(y-a.y)<0:x<a.x;
	}
	
	double len() { return sqrt(x*x+y*y);}
	
	double len2() { return x*x+y*y;}
	
	double distance(point p) { return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));}
	
	point add(point p) { return point(x+p.x,y+p.y);}
	point sub(point p) { return point(x-p.x,y-p.y);}
	point mul(double b) { return point(x*b,y*b);}
	point div(double b) { return point(x/b,y/b);}
	double dot(point p) { return x*p.x+y*p.y;}
	double det(point p) { return x*p.y-y*p.x;}
	double rad(point a,point b) {
		point p=*this;
		return fabs(atan2(fabs(a.sub(p).det(b.sub(p))),a.sub(p).dot(b.sub(p))));
	}
	point trunc(double r) {
		double l=len();
		if (!dblcMP(l))return *this;
		r/=l;
		return point(x*r,y*r);
	}
	point rotleft() { return point(-y,x);}
	point rotright() { return point(y,-x);}
	point rotate(point p,double angle)//ÈÆµãpÄæÊ±ÕëÐý×ªangle½Ç¶È 
	{
		point v=this->sub(p);
		double c=cos(angle),s=sin(angle);
		return point(p.x+v.x*c-v.y*s,p.y+v.x*s+v.y*c);
	}        
};
struct line {
	point a,b;
	
	line(){}
	
	line(point _a,point _b) { a=_a;b=_b;}

	bool operator==(line v) { return (a==v.a)&&(b==v.b);}
	//ÇãÐ±½Çangle 
	line(point p,double angle) {
		a=p;
		if (dblcMP(angle-pi/2)==0) b=a.add(point(0,1));
		else b=a.add(point(1,tan(angle)));
	}       
	//ax+by+c=0
	line(double _a,double _b,double _c) {
		if (dblcMP(_a)==0) a=point(0,-_c/_b),b=point(1,-_c/_b);
		else if (dblcMP(_b)==0) a=point(-_c/_a,0),b=point(-_c/_a,1);
		else a=point(0,-_c/_b),b=point(1,(-_c-_a)/_b);
	}
	void input() { a.input();b.input();}
	void adjust() { if (b<a)swap(a,b);}
	double length() { return a.distance(b);}
	//Ö±ÏßÇãÐ±½Ç 0<=angle<180
	double angle() {
		double k=atan2(b.y-a.y,b.x-a.x);
		if (dblcMP(k)<0)k+=pi;
		if (dblcMP(k-pi)==0)k-=pi;
		return k;
	}
	//µãºÍÏß¶Î¹ØÏµ
	//1 ÔÚÄæÊ±Õë
	//2 ÔÚË³Ê±Õë
	//3 Æ½ÐÐ
	int relation(point p) {
		int c=dblcMP(p.sub(a).det(b.sub(a)));
		if (c<0)return 1;
		if (c>0)return 2;
		return 3;
	}
	bool pointonseg(point p) {
		return dblcMP(p.sub(a).det(b.sub(a)))==0&&dblcMP(p.sub(a).dot(p.sub(b)))<=0;
	}
	bool parallel(line v) {
		return dblcMP(b.sub(a).det(v.b.sub(v.a)))==0;
	}
	//2 ¹æ·¶Ïà½»
	//1 ·Ç¹æ·¶Ïà½»
	//0 ²»Ïà½» 
	int segcrossseg(line v)
	{
		int d1=dblcMP(b.sub(a).det(v.a.sub(a)));
		int d2=dblcMP(b.sub(a).det(v.b.sub(a)));
		int d3=dblcMP(v.b.sub(v.a).det(a.sub(v.a)));
		int d4=dblcMP(v.b.sub(v.a).det(b.sub(v.a)));
		if ((d1^d2)==-2&&(d3^d4)==-2)return 2;
		return (d1==0&&dblcMP(v.a.sub(a).dot(v.a.sub(b)))<=0||
				d2==0&&dblcMP(v.b.sub(a).dot(v.b.sub(b)))<=0||
				d3==0&&dblcMP(a.sub(v.a).dot(a.sub(v.b)))<=0||
				d4==0&&dblcMP(b.sub(v.a).dot(b.sub(v.b)))<=0);        
	}        
	int linecrossseg(line v)//*this seg v line
	{
		int d1=dblcMP(b.sub(a).det(v.a.sub(a)));
		int d2=dblcMP(b.sub(a).det(v.b.sub(a)));
		if ((d1^d2)==-2)return 2;
		return (d1==0||d2==0);
	}
	//0 Æ½ÐÐ
	//1 ÖØºÏ
	//2 Ïà½» 
	int linecrossline(line v)
	{
		if ((*this).parallel(v))
		{
			return v.relation(a)==3;
		}
		return 2;
	}
	point crosspoint(line v)
	{
		double a1=v.b.sub(v.a).det(a.sub(v.a));
		double a2=v.b.sub(v.a).det(b.sub(v.a));
		return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
	}
	double dispointtoline(point p)
	{
		return fabs(p.sub(a).det(b.sub(a)))/length();
	}
	double dispointtoseg(point p)
	{
		if (dblcMP(p.sub(b).dot(a.sub(b)))<0||dblcMP(p.sub(a).dot(b.sub(a)))<0)
		{
			return min(p.distance(a),p.distance(b));
		}
		return dispointtoline(p);
	}
	point lineprog(point p)
	{
		return a.add(b.sub(a).mul(b.sub(a).dot(p.sub(a))/b.sub(a).len2()));
	}
	point symmetrypoint(point p)
	{
		point q=lineprog(p);
		return point(2*q.x-p.x,2*q.y-p.y);
	}   
};
struct circle 
{
	point p;
	double r;
	circle(){}
	circle(point _p,double _r):
	p(_p),r(_r){};
	circle(double x,double y,double _r):
	p(point(x,y)),r(_r){};
	circle(point a,point b,point c)//Èý½ÇÐÎµÄÍâ½ÓÔ² 
	{
		p=line(a.add(b).div(2),a.add(b).div(2).add(b.sub(a).rotleft())).crosspoint(line(c.add(b).div(2),c.add(b).div(2).add(b.sub(c).rotleft())));
		r=p.distance(a);
	}
	circle(point a,point b,point c,bool t)//Èý½ÇÐÎµÄÄÚÇÐÔ² 
	{
		line u,v;
		double m=atan2(b.y-a.y,b.x-a.x),n=atan2(c.y-a.y,c.x-a.x);
		u.a=a;
		u.b=u.a.add(point(cos((n+m)/2),sin((n+m)/2)));
		v.a=b;
		m=atan2(a.y-b.y,a.x-b.x),n=atan2(c.y-b.y,c.x-b.x);
		v.b=v.a.add(point(cos((n+m)/2),sin((n+m)/2)));
		p=u.crosspoint(v);
		r=line(a,b).dispointtoseg(p);
	}
	void input()
	{
		p.input();
		scanf("%lf",&r);
	}
	void output()
	{
		printf("%.2lf %.2lf %.2lf\n",p.x,p.y,r);
	}
	bool operator==(circle v)
	{
		return ((p==v.p)&&dblcMP(r-v.r)==0);
	}
	bool operator<(circle v)const
	{
		return ((p<v.p)||(p==v.p)&&dblcMP(r-v.r)<0);
	}
	double area()
	{
		return pi*sqr(r);
	}
	double circumference()
	{
		return 2*pi*r;
	}
	//0 Ô²Íâ
	//1 Ô²ÉÏ
	//2 Ô²ÄÚ 
	int relation(point b)
	{
		double dst=b.distance(p);
		if (dblcMP(dst-r)<0)return 2;
		if (dblcMP(dst-r)==0)return 1;
		return 0;
	}
	int relationseg(line v)
	{
		double dst=v.dispointtoseg(p);
		if (dblcMP(dst-r)<0)return 2;
		if (dblcMP(dst-r)==0)return 1;
		return 0;
	}
	int relationline(line v)
	{
		double dst=v.dispointtoline(p);
		if (dblcMP(dst-r)<0)return 2;
		if (dblcMP(dst-r)==0)return 1;
		return 0;
	}
	//¹ýa bÁ½µã °ë¾¶rµÄÁ½¸öÔ² 
	int getcircle(point a,point b,double r,circle&c1,circle&c2)
	{
		circle x(a,r),y(b,r);
		int t=x.pointcrosscircle(y,c1.p,c2.p);
		if (!t)return 0;
		c1.r=c2.r=r;
		return t;
	}
	//ÓëÖ±ÏßuÏàÇÐ ¹ýµãq °ë¾¶r1µÄÔ² 
	int getcircle(line u,point q,double r1,circle &c1,circle &c2)
	{
		double dis=u.dispointtoline(q);
		if (dblcMP(dis-r1*2)>0)return 0;
		if (dblcMP(dis)==0)
		{
			c1.p=q.add(u.b.sub(u.a).rotleft().trunc(r1));
			c2.p=q.add(u.b.sub(u.a).rotright().trunc(r1));
			c1.r=c2.r=r1;
			return 2;
		}
		line u1=line(u.a.add(u.b.sub(u.a).rotleft().trunc(r1)),u.b.add(u.b.sub(u.a).rotleft().trunc(r1)));
		line u2=line(u.a.add(u.b.sub(u.a).rotright().trunc(r1)),u.b.add(u.b.sub(u.a).rotright().trunc(r1)));
		circle cc=circle(q,r1);
		point p1,p2;
		if (!cc.pointcrossline(u1,p1,p2))cc.pointcrossline(u2,p1,p2);
		c1=circle(p1,r1);
		if (p1==p2)
		{
			c2=c1;return 1;
		}
		c2=circle(p2,r1);
		return 2;
	}
	//Í¬Ê±ÓëÖ±Ïßu,vÏàÇÐ °ë¾¶r1µÄÔ² 
	int getcircle(line u,line v,double r1,circle &c1,circle &c2,circle &c3,circle &c4)
	{
		if (u.parallel(v))return 0;
		line u1=line(u.a.add(u.b.sub(u.a).rotleft().trunc(r1)),u.b.add(u.b.sub(u.a).rotleft().trunc(r1)));
		line u2=line(u.a.add(u.b.sub(u.a).rotright().trunc(r1)),u.b.add(u.b.sub(u.a).rotright().trunc(r1)));
		line v1=line(v.a.add(v.b.sub(v.a).rotleft().trunc(r1)),v.b.add(v.b.sub(v.a).rotleft().trunc(r1)));
		line v2=line(v.a.add(v.b.sub(v.a).rotright().trunc(r1)),v.b.add(v.b.sub(v.a).rotright().trunc(r1)));
		c1.r=c2.r=c3.r=c4.r=r1;
		c1.p=u1.crosspoint(v1);
		c2.p=u1.crosspoint(v2);
		c3.p=u2.crosspoint(v1);
		c4.p=u2.crosspoint(v2);
		return 4;
	}
	//Í¬Ê±Óë²»Ïà½»Ô²cx,cyÏàÇÐ °ë¾¶Îªr1µÄÔ²
	int getcircle(circle cx,circle cy,double r1,circle&c1,circle&c2)
	{
		circle x(cx.p,r1+cx.r),y(cy.p,r1+cy.r);
		int t=x.pointcrosscircle(y,c1.p,c2.p);
		if (!t)return 0;
		c1.r=c2.r=r1;
		return t;
	}
	int pointcrossline(line v,point &p1,point &p2)//ÇóÓëÏß¶Î½»ÒªÏÈÅÐ¶Ïrelationseg  
	{
		if (!(*this).relationline(v))return 0;
		point a=v.lineprog(p);
		double d=v.dispointtoline(p);
		d=sqrt(r*r-d*d);
		if (dblcMP(d)==0)
		{
			p1=a;
			p2=a;
			return 1;
		}
		p1=a.sub(v.b.sub(v.a).trunc(d));
		p2=a.add(v.b.sub(v.a).trunc(d));
		return 2;
	}
	//5 ÏàÀë
	//4 ÍâÇÐ
	//3 Ïà½»
	//2 ÄÚÇÐ
	//1 ÄÚº¬ 
	int relationcircle(circle v)
	{
		double d=p.distance(v.p);
		if (dblcMP(d-r-v.r)>0)return 5;
		if (dblcMP(d-r-v.r)==0)return 4;
		double l=fabs(r-v.r);
		if (dblcMP(d-r-v.r)<0&&dblcMP(d-l)>0)return 3;
		if (dblcMP(d-l)==0)return 2;
		if (dblcMP(d-l)<0)return 1;
	}
	int pointcrosscircle(circle v,point &p1,point &p2)
	{
		int rel=relationcircle(v);
		if (rel==1||rel==5)return 0;
		double d=p.distance(v.p);
		double l=(d+(sqr(r)-sqr(v.r))/d)/2;
		double h=sqrt(sqr(r)-sqr(l));
		p1=p.add(v.p.sub(p).trunc(l).add(v.p.sub(p).rotleft().trunc(h)));
		p2=p.add(v.p.sub(p).trunc(l).add(v.p.sub(p).rotright().trunc(h)));
		if (rel==2||rel==4)
		{
			return 1;
		}
		return 2;
	}
	//¹ýÒ»µã×öÔ²µÄÇÐÏß (ÏÈÅÐ¶ÏµãºÍÔ²¹ØÏµ) 
	int tangentline(point q,line &u,line &v)
	{
		int x=relation(q);
		if (x==2)return 0;
		if (x==1)
		{
			u=line(q,q.add(q.sub(p).rotleft()));
			v=u;
			return 1;
		}
		double d=p.distance(q);
		double l=sqr(r)/d;
		double h=sqrt(sqr(r)-sqr(l));
		u=line(q,p.add(q.sub(p).trunc(l).add(q.sub(p).rotleft().trunc(h))));
		v=line(q,p.add(q.sub(p).trunc(l).add(q.sub(p).rotright().trunc(h))));
		return 2;
	}
	//5 ÏàÀë
	//4 ÍâÇÐ
	//3 Ïà½»
	//2 ÄÚÇÐ
	//1 ÄÚº¬ 
	int tangentline(circle v,line &u1,line &u2,line &v1,line &v2)
	{
		int w=relationcircle(v);
		if (w==2) {
			
		}
	}
	double areacircle(circle v)
	{
		int rel=relationcircle(v); 
		if (rel>=4)return 0.0;
		if (rel<=2)return min(area(),v.area());
		double d=p.distance(v.p);
		double hf=(r+v.r+d)/2.0;
		double ss=2*sqrt(hf*(hf-r)*(hf-v.r)*(hf-d));
		double a1=acos((r*r+d*d-v.r*v.r)/(2.0*r*d));
		a1=a1*r*r;
		double a2=acos((v.r*v.r+d*d-r*r)/(2.0*v.r*d));
		a2=a2*v.r*v.r;
		return a1+a2-ss;
	}
	double areatriangle(point a,point b)
	{
		if (dblcMP(p.sub(a).det(p.sub(b))==0))return 0.0;
		point q[5];
		int len=0;
		q[len++]=a;
		line l(a,b);
		point p1,p2;
		if (pointcrossline(l,q[1],q[2])==2)
		{
			if (dblcMP(a.sub(q[1]).dot(b.sub(q[1])))<0)q[len++]=q[1];
			if (dblcMP(a.sub(q[2]).dot(b.sub(q[2])))<0)q[len++]=q[2];
		}
		q[len++]=b;
		if (len==4&&(dblcMP(q[0].sub(q[1]).dot(q[2].sub(q[1])))>0))swap(q[1],q[2]);
		double res=0;
		int i;
		for (i=0;i<len-1;i++)
		{
			if (relation(q[i])==0||relation(q[i+1])==0)
			{
				double arg=p.rad(q[i],q[i+1]);
				res+=r*r*arg/2.0;
			}
			else 
			{
				res+=fabs(q[i].sub(p).det(q[i+1].sub(p))/2.0);
			}
		}
		return res;
	}
};
struct polygon 
{
	int n;
	point p[maxp];
	line l[maxp];
	void input()
	{
		n=4;
		for (int i=0;i<n;i++)
		{
			p[i].input();
		}
	}
	void output() {
		puts("pp");
		printf("%d\n",n);
		for (int i=0;i<n;i++) p[i].output();
	}
	void add(point q)
	{
		p[n++]=q;
	}
	void getline()
	{
		for (int i=0;i<n;i++)
		{
			l[i]=line(p[i],p[(i+1)%n]);
		}
	}
	struct cMP
	{
		point p;
		cMP(const point &p0){p=p0;}
		bool operator()(const point &aa,const point &bb)
		{
			point a=aa,b=bb;
			int d=dblcMP(a.sub(p).det(b.sub(p)));
			if (d==0)
			{
				return dblcMP(a.distance(p)-b.distance(p))<0;
			}
			return d>0;
		}
	};
	void norm()
	{
		point mi=p[0];
		for (int i=1;i<n;i++)mi=min(mi,p[i]);
		sort(p,p+n,cMP(mi));
	}
	void getconvex(polygon &convex)
	{
		int i,j,k;
		sort(p,p+n);
		convex.n=n;
		for (i=0;i<min(n,2);i++)
		{
			convex.p[i]=p[i];
		}
		if (n<=2)return;
		int &top=convex.n;
		top=1;
		for (i=2;i<n;i++)
		{
			while (top&&convex.p[top].sub(p[i]).det(convex.p[top-1].sub(p[i]))<=0)
				top--;
			convex.p[++top]=p[i];
		}
		int teMP=top;
		convex.p[++top]=p[n-2];
		for (i=n-3;i>=0;i--)
		{
			while (top!=teMP&&convex.p[top].sub(p[i]).det(convex.p[top-1].sub(p[i]))<=0)
				top--;
			convex.p[++top]=p[i];
		}
	}
	bool isconvex()
	{
		bool s[3];
		memset(s,0,sizeof(s));
		int i,j,k;
		for (i=0;i<n;i++)
		{
			j=(i+1)%n;
			k=(j+1)%n;
			s[dblcMP(p[j].sub(p[i]).det(p[k].sub(p[i])))+1]=1;
			if (s[0]&&s[2])return 0;
		}
		return 1;
	}
	//3 µãÉÏ
	//2 ±ßÉÏ
	//1 ÄÚ²¿
	//0 Íâ²¿ 
	int relationpoint(point q)
	{
		int i,j;
		for (i=0;i<n;i++)
		{
			if (p[i]==q)return 3;
		}
		getline();
		for (i=0;i<n;i++)
		{
			if (l[i].pointonseg(q))return 2;
		}
		int cnt=0;
		for (i=0;i<n;i++)
		{
			j=(i+1)%n;
			int k=dblcMP(q.sub(p[j]).det(p[i].sub(p[j])));
			int u=dblcMP(p[i].y-q.y);
			int v=dblcMP(p[j].y-q.y);
			if (k>0&&u<0&&v>=0)cnt++;
			if (k<0&&v<0&&u>=0)cnt--;
		}
		return cnt!=0;
	}
	//1 ÔÚ¶à±ßÐÎÄÚ³¤¶ÈÎªÕý 
	//2 Ïà½»»òÓë±ßÆ½ÐÐ
	//0 ÎÞÈÎºÎ½»µã 
	int relationline(line u)
	{
		int i,j,k=0;
		getline();
		for (i=0;i<n;i++)
		{
			if (l[i].segcrossseg(u)==2)return 1;
			if (l[i].segcrossseg(u)==1)k=1;
		}
		if (!k)return 0;
		vector<point>vp; 
		for (i=0;i<n;i++)
		{
			if (l[i].segcrossseg(u))
			{
				if (l[i].parallel(u))
				{
					vp.PB(u.a);
					vp.PB(u.b);
					vp.PB(l[i].a);
					vp.PB(l[i].b);
					continue;
				}
				vp.PB(l[i].crosspoint(u));
			}
		}
		sort(vp.begin(),vp.end());
		int sz=vp.size();
		for (i=0;i<sz-1;i++)
		{
			point mid=vp[i].add(vp[i+1]).div(2);
			if (relationpoint(mid)==1)return 1;
		}
		return 2;
	}
	//Ö±ÏßuÇÐ¸îÍ¹¶à±ßÐÎ×ó²à 
	//×¢ÒâÖ±Ïß·½Ïò 
	void convexcut(line u,polygon &po)
	{
		int i,j,k;
		int &top=po.n;
		top=0;
		for (i=0;i<n;i++)
		{
			int d1=dblcMP(p[i].sub(u.a).det(u.b.sub(u.a)));
			int d2=dblcMP(p[(i+1)%n].sub(u.a).det(u.b.sub(u.a)));
			if (d1>=0)po.p[top++]=p[i];
			if (d1*d2<0)po.p[top++]=u.crosspoint(line(p[i],p[(i+1)%n]));
		}
	}
	double getcircumference()
	{
		double sum=0;
		int i;
		for (i=0;i<n;i++)
		{
			sum+=p[i].distance(p[(i+1)%n]);
		}
		return sum;
	}
	double getarea()
	{
		double sum=0;
		int i;
		for (i=0;i<n;i++)
		{
			sum+=p[i].det(p[(i+1)%n]);
		}
		return fabs(sum)/2;
	}
	bool getdir()//1´ú±íÄæÊ±Õë 0´ú±íË³Ê±Õë 
	{
		double sum=0;
		int i;
		for (i=0;i<n;i++)
		{
			sum+=p[i].det(p[(i+1)%n]);
		}
		if (dblcMP(sum)>0)return 1;
		return 0;
	}
	point getbarycentre()
	{
		point ret(0,0);
		double area=0;
		int i;
		for (i=1;i<n-1;i++)
		{
			double tMP=p[i].sub(p[0]).det(p[i+1].sub(p[0]));
			if (dblcMP(tMP)==0)continue;
			area+=tMP;
			ret.x+=(p[0].x+p[i].x+p[i+1].x)/3*tMP;
			ret.y+=(p[0].y+p[i].y+p[i+1].y)/3*tMP;
		}
		if (dblcMP(area))ret=ret.div(area);
		return ret;
	}
	double areaintersection(polygon po)
	{
	}
	double areaunion(polygon po)
	{
		return getarea()+po.getarea()-areaintersection(po);
	}
	double areacircle(circle c)
	{
		int i,j,k,l,m;
		double ans=0;
		for (i=0;i<n;i++)
		{
			int j=(i+1)%n;
			if (dblcMP(p[j].sub(c.p).det(p[i].sub(c.p)))>=0)
			{
				ans+=c.areatriangle(p[i],p[j]);
			}
			else 
			{
				ans-=c.areatriangle(p[i],p[j]);
			}
		}
		return fabs(ans);
	}
	//¶à±ßÐÎºÍÔ²¹ØÏµ
	//0 Ò»²¿·ÖÔÚÔ²Íâ
	//1 ÓëÔ²Ä³Ìõ±ßÏàÇÐ
	//2 ÍêÈ«ÔÚÔ²ÄÚ 
	int relationcircle(circle c)
	{
		getline();
		int i,x=2;
		if (relationpoint(c.p)!=1)return 0;
		for (i=0;i<n;i++)
		{
			if (c.relationseg(l[i])==2)return 0;
			if (c.relationseg(l[i])==1)x=1;
		}
		return x;
	}
	void find(int st,point tri[],circle &c)
	{
		if (!st)
		{
			c=circle(point(0,0),-2);
		}
		if (st==1)
		{
			c=circle(tri[0],0);
		}
		if (st==2)
		{
			c=circle(tri[0].add(tri[1]).div(2),tri[0].distance(tri[1])/2.0);
		}
		if (st==3)
		{
			c=circle(tri[0],tri[1],tri[2]);
		}
	}
	void solve(int cur,int st,point tri[],circle &c)
	{
		find(st,tri,c);
		if (st==3)return;
		int i;
		for (i=0;i<cur;i++)
		{
			if (dblcMP(p[i].distance(c.p)-c.r)>0)
			{
				tri[st]=p[i];
				solve(i,st+1,tri,c);
			}
		}
	}
	circle mincircle()//µã¼¯×îÐ¡Ô²¸²¸Ç
	{
		random_shuffle(p,p+n);
		point tri[4];
		circle c;
		solve(n,0,tri,c);
		return c;
	}
	int circlecover(double r)//µ¥Î»Ô²¸²¸Ç 
	{
		int ans=0,i,j;
		vector<pair<double,int> >v;
		for (i=0;i<n;i++)
		{
			v.clear();
			for (j=0;j<n;j++)if (i!=j)
			{
				point q=p[i].sub(p[j]);
				double d=q.len();
				if (dblcMP(d-2*r)<=0)
				{
					double arg=atan2(q.y,q.x);
					if (dblcMP(arg)<0)arg+=2*pi;
					double t=acos(d/(2*r));
					v.push_back(make_pair(arg-t+2*pi,-1));
					v.push_back(make_pair(arg+t+2*pi,1));
				}
			}
			sort(v.begin(),v.end());
			int cur=0;
			for (j=0;j<v.size();j++)
			{
				if (v[j].second==-1)++cur;
				else --cur;
				ans=max(ans,cur);
			}
		}
		return ans+1;
	}           
	int pointinpolygon(point q)//µãÔÚÍ¹¶à±ßÐÎÄÚ²¿µÄÅÐ¶¨ 
	{
		if (getdir())reverse(p,p+n);
		if (dblcMP(q.sub(p[0]).det(p[n-1].sub(p[0])))==0)
		{
			if (line(p[n-1],p[0]).pointonseg(q))return n-1;
			return -1;
		}
		int low=1,high=n-2,mid;
		while (low<=high)
		{
			mid=(low+high)>>1;
			if (dblcMP(q.sub(p[0]).det(p[mid].sub(p[0])))>=0&&dblcMP(q.sub(p[0]).det(p[mid+1].sub(p[0])))<0)
			{
				polygon c;
				c.p[0]=p[mid];
				c.p[1]=p[mid+1];
				c.p[2]=p[0];
				c.n=3;
				if (c.relationpoint(q))return mid;
				return -1;
			}
			if (dblcMP(q.sub(p[0]).det(p[mid].sub(p[0])))>0)
			{
				low=mid+1;
			}
			else 
			{
				high=mid-1;
			}
		}
		return -1;
	}   
};
struct polygons
{
	vector<polygon>p;
	polygons()
	{
		p.clear();
	}
	void clear()
	{
		p.clear();
	}
	void push(polygon q)
	{
		if (dblcMP(q.getarea()))p.PB(q);
	}
	vector<pair<double,int> >e;
	void ins(point s,point t,point X,int i)
	{
		double r=fabs(t.x-s.x)>eps?(X.x-s.x)/(t.x-s.x):(X.y-s.y)/(t.y-s.y);
		r=min(r,1.0);r=max(r,0.0);
		e.PB(MP(r,i));
	}
	double polyareaunion()
	{
		double ans=0.0;
		int c0,c1,c2,i,j,k,w;
		for (i=0;i<p.size();i++)
		{
			if (p[i].getdir()==0)reverse(p[i].p,p[i].p+p[i].n);
		}
		for (i=0;i<p.size();i++)
		{
			for (k=0;k<p[i].n;k++)
			{
				point &s=p[i].p[k],&t=p[i].p[(k+1)%p[i].n];
				if (!dblcMP(s.det(t)))continue;
				e.clear();
				e.PB(MP(0.0,1));
				e.PB(MP(1.0,-1));
				for (j=0;j<p.size();j++)if (i!=j)
				{
					for (w=0;w<p[j].n;w++)
					{
						point a=p[j].p[w],b=p[j].p[(w+1)%p[j].n],c=p[j].p[(w-1+p[j].n)%p[j].n];
						c0=dblcMP(t.sub(s).det(c.sub(s)));
						c1=dblcMP(t.sub(s).det(a.sub(s)));
						c2=dblcMP(t.sub(s).det(b.sub(s)));
						if (c1*c2<0)ins(s,t,line(s,t).crosspoint(line(a,b)),-c2);
						else if (!c1&&c0*c2<0)ins(s,t,a,-c2);
						else if (!c1&&!c2)
						{
							int c3=dblcMP(t.sub(s).det(p[j].p[(w+2)%p[j].n].sub(s)));
							int dp=dblcMP(t.sub(s).dot(b.sub(a)));
							if (dp&&c0)ins(s,t,a,dp>0?c0*((j>i)^(c0<0)):-(c0<0));
							if (dp&&c3)ins(s,t,b,dp>0?-c3*((j>i)^(c3<0)):c3<0);
						}
					}
				}
				sort(e.begin(),e.end());
				int ct=0;
				double tot=0.0,last;
				for (j=0;j<e.size();j++)
				{
					if (ct==2)tot+=e[j].first-last;
					ct+=e[j].second;
					last=e[j].first;
				}
				ans+=s.det(t)*tot;
			}
		}
		return fabs(ans)*0.5;
	}
};
const int maxn=500;
struct circles 
{
	circle c[maxn];
	double ans[maxn];//ans[i]±íÊ¾±»¸²¸ÇÁËi´ÎµÄÃæ»ý 
	double pre[maxn];
	int n;
	circles(){}
	void add(circle cc)
	{
		c[n++]=cc;
	}
	bool inner(circle x,circle y)
	{
		if (x.relationcircle(y)!=1)return 0;
		return dblcMP(x.r-y.r)<=0?1:0;
	}
	void init_or()//Ô²µÄÃæ»ý²¢È¥µôÄÚº¬µÄÔ² 
	{
		int i,j,k=0;
		bool mark[maxn]={0};
		for (i=0;i<n;i++)
		{
			for (j=0;j<n;j++)if (i!=j&&!mark[j])
			{
				if ((c[i]==c[j])||inner(c[i],c[j]))break;
			}
			if (j<n)mark[i]=1;
		}
		for (i=0;i<n;i++)if (!mark[i])c[k++]=c[i];
		n=k;
	}
	void init_and()//Ô²µÄÃæ»ý½»È¥µôÄÚº¬µÄÔ² 
	{
		int i,j,k=0;
		bool mark[maxn]={0};
		for (i=0;i<n;i++)
		{
			for (j=0;j<n;j++)if (i!=j&&!mark[j])
			{
				if ((c[i]==c[j])||inner(c[j],c[i]))break;
			}
			if (j<n)mark[i]=1;
		}
		for (i=0;i<n;i++)if (!mark[i])c[k++]=c[i];
		n=k;
	}
	double areaarc(double th,double r)
	{
		return 0.5*sqr(r)*(th-sin(th));
	}
	void getarea()
	{
		int i,j,k;
		memset(ans,0,sizeof(ans));
		vector<pair<double,int> >v;
		for (i=0;i<n;i++)
		{
			v.clear();
			v.push_back(make_pair(-pi,1));
			v.push_back(make_pair(pi,-1));
			for (j=0;j<n;j++)if (i!=j)
			{
				point q=c[j].p.sub(c[i].p);
				double ab=q.len(),ac=c[i].r,bc=c[j].r;
				if (dblcMP(ab+ac-bc)<=0)
				{
					v.push_back(make_pair(-pi,1));
					v.push_back(make_pair(pi,-1));
					continue;
				}
				if (dblcMP(ab+bc-ac)<=0)continue;
				if (dblcMP(ab-ac-bc)>0) continue;
				double th=atan2(q.y,q.x),fai=acos((ac*ac+ab*ab-bc*bc)/(2.0*ac*ab));
				double a0=th-fai;
				if (dblcMP(a0+pi)<0)a0+=2*pi;
				double a1=th+fai;
				if (dblcMP(a1-pi)>0)a1-=2*pi;
				if (dblcMP(a0-a1)>0)
				{
					v.push_back(make_pair(a0,1));
					v.push_back(make_pair(pi,-1));
					v.push_back(make_pair(-pi,1));
					v.push_back(make_pair(a1,-1));
				}
				else 
				{
					v.push_back(make_pair(a0,1));
					v.push_back(make_pair(a1,-1));
				}
			}
			sort(v.begin(),v.end());
			int cur=0;
			for (j=0;j<v.size();j++)
			{
				if (cur&&dblcMP(v[j].first-pre[cur]))
				{
					ans[cur]+=areaarc(v[j].first-pre[cur],c[i].r);
					ans[cur]+=0.5*point(c[i].p.x+c[i].r*cos(pre[cur]),c[i].p.y+c[i].r*sin(pre[cur])).det(point(c[i].p.x+c[i].r*cos(v[j].first),c[i].p.y+c[i].r*sin(v[j].first)));   
				}
				cur+=v[j].second;
				pre[cur]=v[j].first;
			}
		}
		for (i=1;i<=n;i++)
		{
			ans[i]-=ans[i+1];
		}
	}
};
struct halfplane:public line
{
	double angle;
	halfplane(){}
	//±íÊ¾ÏòÁ¿ a->bÄæÊ±Õë(×ó²à)µÄ°ëÆ½Ãæ
	halfplane(point _a,point _b)
	{
		a=_a;
		b=_b;
	}
	halfplane(line v)
	{
		a=v.a;
		b=v.b;
	}
	void calcangle()
	{
		angle=atan2(b.y-a.y,b.x-a.x);
	}
	bool operator<(const halfplane &b)const 
	{
		return angle<b.angle;
	}
};

const int N=610;
struct halfplanes 
{
	int n;
	halfplane hp[N];
	point p[N];
	int que[N];
	int st,ed;
	void init() {
		n=0;
		memset(hp,0,sizeof(hp));
		memset(p,0,sizeof(p));
		memset(que,0,sizeof(que));
	}
	void push(halfplane tMP) {
		hp[n++]=tMP;
	}
	void unique()
	{
		int m=1,i;
		for (i=1;i<n;i++)
		{
			if (dblcMP(hp[i].angle-hp[i-1].angle))hp[m++]=hp[i];
			else if (dblcMP(hp[m-1].b.sub(hp[m-1].a).det(hp[i].a.sub(hp[m-1].a))>0))hp[m-1]=hp[i];
		}
		n=m;
	}
	bool halfplaneinsert()
	{
		int i;
		for (i=0;i<n;i++)hp[i].calcangle();
		sort(hp,hp+n);
		unique();
		que[st=0]=0;
		que[ed=1]=1;
		p[1]=hp[0].crosspoint(hp[1]);
		for (i=2;i<n;i++)
		{
			while (st<ed&&dblcMP((hp[i].b.sub(hp[i].a).det(p[ed].sub(hp[i].a))))<0)ed--;
			while (st<ed&&dblcMP((hp[i].b.sub(hp[i].a).det(p[st+1].sub(hp[i].a))))<0)st++;
			que[++ed]=i;
			if (hp[i].parallel(hp[que[ed-1]]))return false;
			p[ed]=hp[i].crosspoint(hp[que[ed-1]]);
		}
		while (st<ed&&dblcMP(hp[que[st]].b.sub(hp[que[st]].a).det(p[ed].sub(hp[que[st]].a)))<0)ed--;
		while (st<ed&&dblcMP(hp[que[ed]].b.sub(hp[que[ed]].a).det(p[st+1].sub(hp[que[ed]].a)))<0)st++;
		if (st+1>=ed)return false;
		return true;
	}
	void getconvex(polygon &con)
	{
		p[st]=hp[que[st]].crosspoint(hp[que[ed]]);
		con.n=ed-st+1;
		int j=st,i=0;
		for (;j<=ed;i++,j++)
		{
			con.p[i]=p[j];
		}
	}
}T;