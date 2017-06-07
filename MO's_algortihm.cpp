#include<bits/stdc++.h>
 
typedef long long LL;  //Attention!!
using namespace std;
 
#define fiintchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'
const int M = 1000000007;
 
 
struct qu
{
    int ll,rr,ans,id;
};
 
int n,sn;
int blok(int id)
{
return id/sn;       
}

bool myfun(const qu &a,const qu &b)
{
 return (blok(a.ll)<blok(b.ll) || (blok(a.ll)==blok(b.ll) && a.rr<b.rr));       
}

bool qid(const qu &a,const qu &b)
{
return a.id<b.id;   
}
 
int N =1e6 + 5;
     
int main()
{
    //ios_base::sync_with_stdio(0); 
    cout.precision(15);
    cout.setf(ios::fixed);
    
    int i,j,m;
     
    cin>>n;
    sn = sqrt(n);
     
    vector <int> v(n),cnt(N);
     
    for(i=0;i<n;i++)
        cin>>v[i];  
     
    cin>>m;
    vector <qu> q(m);
        
    for(i=0;i<m;i++)
        {
        q[i].id = i;    
        cin>>q[i].ll>>q[i].rr;
        q[i].ll--;
        q[i].rr--;
        }
     
    sort(q.begin(),q.end(),myfun);
     
    int cur_ans=0,cur_block=0;
    i = 0; j = 0;
     
    for(int xx=0;xx<m;xx++)
        {
        
        //cout<<"DEBUG"<<endl;  
        //cout<<i<<' '<<j<<endl;    
     
        while(i<q[xx].ll)  
            {
            cnt[v[i]]--;
            if(cnt[v[i]]==0)  cur_ans--;    
            i++;
            }
     
        while(i>q[xx].ll)  
            {
            i--;    
            cnt[v[i]]++;
            if(cnt[v[i]]==1) cur_ans++; 
            }
     
        
        while(j<q[xx].rr+1) 
            {
            cnt[v[j]]++;    
            if(cnt[v[j]]==1) cur_ans++;
            j++;
            }
     
        while(j>q[xx].rr+1) 
            {
            j--;    
            cnt[v[j]]--;    
            if(cnt[v[j]]==0)    cur_ans--;
            }   
     
        //cout<<i<<' '<<j<<' '<<cur_ans<<' '<<cur_block<<endl;  
        
     
        q[xx].ans = cur_ans;    
     
        }
     
    sort(q.begin(),q.end(),qid);
     
    for(i=0;i<m;i++)
        cout<<q[i].ans<<endl;
     
}
     
     