#include<bits/stdc++.h>

typedef long long LL;  
using namespace std;

#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'

const int M = (int)1e9+7;

struct node
 {
    int key;
    int pr;
    int sz;
    node* l;
    node* r;

    node(int _key)
    {
        key = _key;
        pr = rand();
        l = NULL;
        r = NULL;
        sz = 1;

    }
};


 int size(node* t)
{
    return t?t->sz:0;
}

void upd_sz(node *t)
{
   if(t) 
	t->sz = size(t->l)+ size(t->r) + 1;
}

struct Treap
  { 
    node* root;

    Treap()
    {
        root = NULL;
        srand(time(NULL));
    }

    /* split t and return l and r as the two parts */
    void split(node* t,node* &l,node* &r,int key)     
    {      
        if(t==NULL) 
            {l = NULL;r = NULL;}
		else if(key >= t->key)
            {split(t->r,t->r,r,key); l = t;}
        else
            {split(t->l,l,t->l,key); r = t;}

        upd_sz(t);
    }

     /* merge l and r and make it t */
    void merge(node* &t,node* l,node* r) 
    {   
        if(l==NULL || r==NULL) 
            t=(l ? l : r);
        else if(l->pr > r->pr)
            {merge(l->r,l->r,r); t = l;}
        else
            {merge(r->l,l,r->l); t = r;}    

        upd_sz(t);      
    }

    /*insert node it into tree t and return new tree root through t*/
    void add(node* &t,node* it)
    {

        if(!t){
            t=it;
            }
        else if(t->pr < it->pr)
            {split(t,it->l,it->r,it->key); t = it;
			}
        else
            {
               if(t->key >= it->key) 
                    add(t->l,it);
                else
                    add(t->r,it);
            }
        upd_sz(t);    
    }

    /* erasing a node from tree t with value key and return the root through t*/
    void erase(node* &t,int key)
    {
        if(t==NULL) {
            return;
        }

        if(t->key < key) erase(t->r,key); 
        else if(t->key > key) erase(t->l,key);
        else { node* tmp = t; merge(t,t->l,t->r); free(tmp); }
        upd_sz(t);
    }

    //0 indexed 
    int get_id(node* nd,int key)
    {
    	if(!nd) return -M;
    	if(nd->key < key)
    		{	
    			return size(nd->l)+1+get_id(nd->r,key);
    		}	
    	else if(nd->key > key)
    		return get_id(nd->l,key);
    	else 
    		return size(nd->l);
    }


    void print(node* nd)
    {
    	if(nd == NULL)
    		return;

    	print(nd->l);
    	cout<<nd->key<<' ';
    	print(nd->r);

    }

  };

 int main()
 {
 	Treap* T = new Treap();

 	int n;cin >> n; int k;


 	for(int i=0;i<n;i++)
    {
        cin >> k;
        node* nd = new node(k); 
        T->add(T->root,nd);
        // cout<<T->root->key<<endl;
    T->print(T->root);
    cout<<endl;
    }




    int m;
	cin>>m;
    for(int i=0;i<m;i++)
    {
    	cin >> k;
        T->erase(T->root,k);
    T->print(T->root);
    cout<<endl;
    }    


    int arr[] = {1,2,3,4,5,7,8,11};

   	for(int i=0;i<8;i++)
   		cout<<T->get_id(T->root,arr[i])<<' ';
   	cout<<endl; 

    return 0;

}