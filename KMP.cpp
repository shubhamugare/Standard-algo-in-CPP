#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'

/* It is a  nice problem and I will maintain prefix function from KMP from now on */
/* We will construct a tree with edge from i to p[i]  
This tree is useful in very nice problems.
http://codeforces.com/contest/432/problem/D
*/

const int M = (int)1e9+7;
const int N = (int)1e5+7;

int p[N];
int cnt[N];

void prefix_calc(string &s)
{
	int n = s.size();
	int j,i;
	p[0] = -1; // I am not storing length as per conventional KMP instead I am storing 

	for(i=1;i<n;i++)
		{
		j = i-1;	

		while(j!=-1 && s[p[j]+1]!=s[i])
				j = p[j];			
		
		if(j!=-1)
			p[i] =  p[j]+1;	
		else
			p[i] = -1;

		}
}


int main()
{
//ios_base::sync_with_stdio(0); 
cout.precision(15);
cout.setf(ios::fixed);

string s;

cin >> s;

prefix_calc(s);

int i,j,n = s.size();
j = n-1;


//for(i=0;i<n;i++)	cout<<p[i]<<' ';cout<<endl;

for(i=n-1;i>0;i--)
	{
	cnt[i] += 1;
	cnt[p[i]] += cnt[i];	
	}
cnt[0] += 1;	

vector <pair<int,int> > ans;

while(true)
	{
	ans.PB(MP(j+1,cnt[j]));	
	j = p[j];	
	
	if(j==-1) break;
	}

cout<<ans.size()<<endl;

for(i=ans.size()-1;i>=0;i--)
	cout<<ans[i].first<<' '<<ans[i].second<<endl;
}
