// may be wrong
// boj.kr/21973
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#pragma GCC optimize("Ofast") 
#pragma GCC target("avx,avx2,fma") 
#pragma GCC optimize ("unroll-loops")
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define inf ((int)(2e9))

using namespace std;
using ll=long long;
using pii=pair<int,int>;

struct Node{
	Node *l,*r,*p;
	int val,sum;
	bool rev;
	Node():Node(0){}
	Node(int val):val(val),sum(val){
		l=r=p=NULL;rev=false;
	}
	Node& operator=(const Node& other){
		l=other.l;r=other.r;p=other.p;
		val=other.val;sum=other.sum;rev=other.rev;
		return *this;
	}
	bool isRoot(){return p==NULL||(this!=p->l&&this!=p->r);}
	bool isLeft(){return this==p->l;}
	void rotate(){
		if(isLeft()){
			if(r)r->p=p;
			p->l=r;r=p;
		}
		else{
			if(l)l->p=p;
			p->r=l;l=p;
		}
		if(!p->isRoot()){
			if(p->isLeft())p->p->l=this;
			else p->p->r=this;
		}
		Node* t=p;p=t->p;t->p=this;
		t->update();update();
	}
	void update(){
		sum=val;
		if(l)sum+=l->sum;
		if(r)sum+=r->sum;
	}
	void update(int val){
		this->val=val;
		update();
	}
	void lazy(){
		if(!rev)return;
		swap(l,r);
		if(l)l->rev=!l->rev;
		if(r)r->rev=!r->rev;
		rev=false;
	}
};

vector<Node> tree;
int n,cnt;
ll ans,cur;

void splay(Node* x){
	for(;!x->isRoot();x->rotate()){
		if(!x->p->isRoot())x->p->p->lazy();
		x->p->lazy();x->lazy();
		if(x->p->isRoot())continue;
		if(x->isLeft()==x->p->isLeft())x->p->rotate();
		else x->rotate();
	}
	x->lazy();
}

void access(Node* x){
	splay(x);
	x->r=NULL;
	for(;x->p;splay(x))splay(x->p),x->p->r=x;
}

void link(Node* p,Node* c){
	access(c);access(p);
	c->l=p;p->p=c;
	c->update();
}

void cut(Node* x){
	access(x);
	if(x->l==NULL)return;
	x->l->p=NULL;
	x->l=NULL;
	x->update();
}

Node* getRoot(Node* x){
	access(x);
	while(x->l)x=x->l,x->lazy();
	access(x);
	return x;
}

Node* getParent(Node* x){
	access(x);
	if(x->l==NULL)return NULL;
	x=x->l;
	x->lazy();
	while(x->r)x=x->r,x->lazy();
	access(x);
	return x;
}

Node* getLCA(Node* x,Node* y){
	access(x);access(y);
	splay(x);
	return x->p?x->p:x;
}

void makeRoot(Node* x){
	access(x);splay(x);
	x->rev=!x->rev;
}

int vertexQuery(Node* x,Node* y){
	Node* l=getLCA(x,y);
	int ret=l->val;
	access(x);splay(l);
	if(l->r)ret+=l->r->sum;
	access(y);splay(l);
	if(l->r)ret+=l->r->sum;
	return ret;
}

void update(Node* x,int val){
	splay(x);x->update(val);
}

int main(){
	fastio();
	int t,q,a,b,tmp;
	string s;
	cin>>n;
	tree=vector<Node>(n+1);
	for(int i=1;i<=n;++i){
		cin>>tmp;
		tree[i]=Node(tmp);
	}
	for(cin>>q;q--;){
		cin>>s>>a>>b;
		if(s=="excursion"){
			if(getRoot(&tree[a])!=getRoot(&tree[b])){
				cout<<"impossible"<<endl;
				continue;
			}
			cout<<vertexQuery(&tree[a],&tree[b])<<endl;
		}
		else if(s=="bridge"){
			if(getRoot(&tree[a])==getRoot(&tree[b])){
				cout<<"no"<<endl;
				continue;
			}
			cout<<"yes"<<endl;
			makeRoot(&tree[b]);
			link(&tree[a],&tree[b]);
		}
		else update(&tree[a],b);
	}
}