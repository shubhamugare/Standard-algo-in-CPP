#include<bits/stdc++.h>
 
typedef long long LL;
 
 
using namespace std;
const int M = 1000000007;
 
const int N=100003;
 
LL trie[26][N],word[N],prefix[N];
LL next;

void add(string &s)
{
int i=0,v=0;

while(i<s.size())
	{
	if(trie[s[i]-'a'][v]==-1)
		v=trie[s[i++]-'a'][v]=next++;
	else
		v=trie[s[i++]-'a'][v];
 
	prefix[v]++;

	}
 
word[v]++;

}  

void get(string &s)
{
int i=0,v=0;

int ma = s.size();

while(i<s.size())
	{
	if(trie[s[i]-'a'][v]!=-1)
		v=trie[s[i]-'a'][v];
	else 
		{
		ma = max(ma,i);
		break;
		}

	ma = max(ma,i+prefix[v]);
	i++;
	}
 
return ma;
}  

 
int main()
{
int i,j;
 
for(i=0;i<N;i++)
	{
	for(j=0;j<26;j++)
		trie[j][i]=-1;
	}

next=1;

int n,m;

cin >> n >> m;

string s;

vector <string> v(n);

for(i=0;i<n;i++)
	{
	cin >> v[i];
	}

int ans = 0;
 
for(i=0;i<m;i++) 
	{
	cin >> s;
	aadd(s);
	}

for(i=0;i<n;i++)
	{
	ans += get(v[i]);	
	} 

cout<<ans<<endl;

} 