
#include<bits/stdc++.h>
 
typedef long long LL;  //Attention!!
using namespace std;
 
#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'
 
const int M = 1000000007;
const int N = 1e5;
 
int SA[N];
int pos[N];
int lcp[N];
int tmp[N];
int gap;
int strsize;
 
bool sufcmp(int i,int j)  //is strictly greater j than i
{
if(pos[i]!=pos[j])
	return pos[i] < pos[j];
i += gap;
j += gap;
 
return (i<strsize && j<strsize) ? pos[i] < pos[j] : i > j;  //if there is no difference in position then
}															//the bigger one will be smaller as it will have
															//less $$$$$$ at the end..		
 
void buildSA(string &s)
{
strsize = s.size();
int n = strsize;
int i;
 
for(i=0;i<n;i++)  SA[i] = i ,pos[i] = s[i];
 
for(gap=1;tmp[n-1]<(n-1);gap*=2)  
	{
	sort(SA,SA+n,sufcmp);										//suffix array is sorted wrt pos array valu
 										//from previous iteration
	for(i=1;i<n;i++)	
		tmp[i] = tmp[i-1] + sufcmp(SA[i-1],SA[i]);		//tmp stores positions for each suffixes from 0 to n-1
		
														//in sorted array for string (i to i+gap)					
	for(i=0;i<n;i++)
		pos[SA[i]] = tmp[i];
	
 	}	
}
 
/*
//kasai algorithm
void buildlcp(string &s)
{
int n = s.size();
for(int i=0,k=0;i<n;i++)
	if(pos[i]!=(n-1))
		{
		int j = SA[pos[i]+1];	
		while(i+k<s.size() && j+k<s.size() && s[i+k] == s[j+k])   //lcp stores lcp for i'th suffix and  
			k++;                                                  //the next one in sorted suffix array
 
		lcp[pos[i]] = k;
		if(k) k--;
 
		}
 
}
*/
 
int main()
{
ios_base::sync_with_stdio(0); 
cout.precision(15);
cout.setf(ios::fixed);
 
string s;
 
cin>>s;
 
buildSA(s);
 
for(int i=0;i<s.size();i++)
	cout<<SA[i]<<endl;
 
}
 