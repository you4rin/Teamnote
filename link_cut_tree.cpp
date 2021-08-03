// boj.kr/10723
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;
using ll=long long;
using pii=pair<int,int>;

struct Node{
	Node *l,*r,*p;
	int val,idx;
	pii m;
	bool rev;
	Node():Node(0,0){}
	Node(int val,int idx):val(val),idx(idx){
		l=r=p=NULL;rev=false;
		m={val,idx};
	}
	Node& operator=(const Node& other){
		l=other.l;r=other.r;p=other.p;
		val=other.val;idx=other.idx;
		m=other.m;rev=other.rev;
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
		m={val,idx};
		if(l)m=max(m,l->m);
		if(r)m=max(m,r->m);
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
vector<vector<pii>> adj;
vector<pii> edge;
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

pii pathQuery(Node* x,Node* y){
	Node* l=getLCA(x,y);
	pii ret={l->val,l->idx};
	access(x);splay(l);
	if(l->r)ret=max(ret,l->r->m);
	access(y);splay(l);
	if(l->r)ret=max(ret,l->r->m);
	return ret;
}

void query(Node* x,Node* y,int val){
	pii tmp=pathQuery(x,y);
	int m=tmp.first,idx=tmp.second;
	if(m<=val||!idx)return;
	int a=edge[idx].first,b=edge[idx].second;
	cur+=(ll)val-m;++cnt;
	if(getParent(&tree[n+idx])==&tree[a])cut(&tree[n+idx]);
	else cut(&tree[a]);
	if(getParent(&tree[n+idx])==&tree[b])cut(&tree[n+idx]);
	else cut(&tree[b]);
	tree[n+cnt]=Node(val,cnt);
	makeRoot(x);
	link(&tree[n+cnt],x);
	link(y,&tree[n+cnt]);
	edge[cnt]={y-&tree[0],x-&tree[0]};
}

void dfs(int p,int idx){
	for(auto i:adj[idx]){
		if(i.first==p)continue;
		dfs(idx,i.first);
		++cnt;
		tree[n+cnt]=Node(i.second,cnt);
		link(&tree[n+cnt],&tree[i.first]);
		link(&tree[idx],&tree[n+cnt]);
		edge[cnt]={idx,i.first};
	}
}

int main(){
	int t,q,s,e,v;
	for(scanf("%d",&t);t--;){
		scanf("%d %d",&n,&q);
		ans=cur=cnt=0;
		tree=vector<Node>(2*n+q);
		adj=vector<vector<pii>>(n+1);
		edge=vector<pii>(n+q);
		for(int i=2;i<=n;++i){
			scanf("%d %d",&s,&v);
			++s;
			adj[s].push_back({i,v});
			adj[i].push_back({s,v});
			cur+=v;
		}
		dfs(-1,1);
		while(q--){
			scanf("%d %d %d",&s,&e,&v);
			++s;++e;
			query(&tree[s],&tree[e],v);
			ans^=cur;
		}
		printf("%lld\n",ans);
	}
}