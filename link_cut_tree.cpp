// boj.kr/18861
#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
#define inf ((int)(2e9))

using namespace std;
using ll=long long;
using pii=pair<int,int>;

struct Node{
	Node *l,*r,*p;
	int val,idx;
	pii m;
	bool rev;
	Node():Node(inf,0){}
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
		if(l)m=min(m,l->m);
		if(r)m=min(m,r->m);
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
//vector<vector<pii>> adj;
vector<pii> edge;
set<pii> s;
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

pii pathQuery(Node* x,Node* y){
	Node* l=getLCA(x,y);
	pii ret={l->val,l->idx};
	access(x);splay(l);
	if(l->r)ret=min(ret,l->r->m);
	access(y);splay(l);
	if(l->r)ret=min(ret,l->r->m);
	return ret;
}

/*
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
*/

/*
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
*/

int main(){
	int t,q,a,b,c,d;
	scanf("%d %d",&n,&q);
	tree=vector<Node>(n+q+1);
	//adj=vector<vector<pii>>(n+1);
	edge=vector<pii>(n+q);
	while(q--){
		scanf("%d",&a);
		if(a==1){
			scanf("%d %d %d",&b,&c,&d);
			if(getRoot(&tree[b])==getRoot(&tree[c])){
				pii ret=pathQuery(&tree[b],&tree[c]);
				if(ret.first>=d)continue;
				int e=edge[ret.second].first,f=edge[ret.second].second;
				if(getParent(&tree[n+ret.second])==&tree[e])cut(&tree[n+ret.second]);
				else cut(&tree[e]);
				if(getParent(&tree[n+ret.second])==&tree[f])cut(&tree[n+ret.second]);
				else cut(&tree[f]);
				s.erase(ret);
			}
			++cnt;
			tree[n+cnt]=Node(d,cnt);
			makeRoot(&tree[b]);
			link(&tree[n+cnt],&tree[b]);
			link(&tree[c],&tree[n+cnt]);
			edge[cnt]={c,b};
			s.insert({d,cnt});
		}
		else if(a==2){
			scanf("%d",&b);
			while(s.size()&&s.begin()->first<b){
				pii ret=*s.begin();
				s.erase(s.begin());
				int e=edge[ret.second].first,f=edge[ret.second].second;
				if(getParent(&tree[n+ret.second])==&tree[e])cut(&tree[n+ret.second]);
				else cut(&tree[e]);
				if(getParent(&tree[n+ret.second])==&tree[f])cut(&tree[n+ret.second]);
				else cut(&tree[f]);
			}
		}
		else{
			scanf("%d %d",&b,&c);
			if(getRoot(&tree[b])!=getRoot(&tree[c]))printf("0\n");
			else printf("%d\n",pathQuery(&tree[b],&tree[c]).first);
		}
	}
}