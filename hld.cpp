// boj.kr/13309
#include<iostream>
#include<vector>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define cur seg[pos]
#define left seg[pos*2]
#define right seg[pos*2+1]
#define N (1<<18)
#define INIT_VAL 1 // may be fixed
#define VAL_NUM 1

using namespace std;
using ll=long long;
using pii=pair<int,int>;
using DataType=int;

struct Node{
	int sz,p,depth,chain;
	vector<int> v;
};

struct Edge{
	int s,e;
	DataType val[VAL_NUM];
};

struct Seg{
	int s,e;
	DataType val[VAL_NUM];
};

struct Query{
	DataType val[VAL_NUM];
};

Node arr[N];
Seg seg[N<<1];
int cnt;
int num[N]; // vertex idx -> seg idx
int inv[N]; // seg idx -> vertex idx
vector<int> chain[N];
Edge edge[N];

DataType mul(DataType s,DataType e){
	return s*e;
}

DataType (*metric[])(DataType s,DataType e){
	mul, // may be added
};

int dfs1(int idx){
	arr[idx].sz=1;
	for(auto i:arr[idx].v){
		if(!arr[i].sz){
			arr[i].p=idx;
			arr[i].depth=arr[idx].depth+1;
			arr[idx].sz+=dfs1(i);
		}
	}
	return arr[idx].sz;
}

void dfs2(int idx){
	int heavy=-1;
	num[idx]=++cnt;
	inv[num[idx]]=idx;
	for(auto i:arr[idx].v)
		if(i!=arr[idx].p&&(heavy==-1||arr[i].sz>arr[heavy].sz))
			heavy=i;
	if(heavy!=-1){
		arr[heavy].chain=arr[idx].chain;
		dfs2(heavy);
	}
	for(auto i:arr[idx].v){
		if(i!=arr[idx].p&&i!=heavy){
			arr[i].chain=i;
			dfs2(i);
		}
	}
}

void update(int pos,int idx,Query val){
	if(cur.s>idx||idx>cur.e)return;
	if(seg[pos].s==seg[pos].e){
		for(int i=0;i<VAL_NUM;++i)seg[pos].val[i]=val.val[i];
		return;
	}
	update(pos*2,idx,val);
	update(pos*2+1,idx,val);
	for(int i=0;i<VAL_NUM;++i)cur.val[i]=metric[i](left.val[i],right.val[i]);
}

Query query(int pos,int s,int e){
	Query ret={INIT_VAL},l,r;
	if(cur.s>e||s>cur.e||s>e)return ret;
	if(cur.s>=s&&e>=cur.e){
		for(int i=0;i<VAL_NUM;++i)ret.val[i]=cur.val[i];
		return ret;
	}
	l=query(pos*2,s,e),r=query(pos*2+1,s,e);
	for(int i=0;i<VAL_NUM;++i)ret.val[i]=metric[i](l.val[i],r.val[i]);
	return ret;
}

void init(){
	// seginit
	for(int pos=N;pos<2*N;++pos)cur.s=cur.e=pos-N+1; // 1-based index
	for(int pos=N-1;pos;--pos)cur.s=left.s,cur.e=right.e;
	for(int pos=1;pos<2*N;++pos)for(int i=0;i<VAL_NUM;++i)cur.val[i]=INIT_VAL;
	// hldinit
	arr[1].depth=arr[1].chain=1;
	dfs1(1);dfs2(1);
}

// add 'undirected' edge
void addEdge(int src,int dst){
	arr[src].v.push_back(dst);
	arr[dst].v.push_back(src);
}

Query eval(int s,int e){
	Query ret={INIT_VAL},p; // init value may be fixed
	while(arr[s].chain!=arr[e].chain){
		if(arr[arr[s].chain].depth<arr[arr[e].chain].depth)swap(s,e);
		p=query(1,num[arr[s].chain],num[s]);
		for(int i=0;i<VAL_NUM;++i)ret.val[i]=metric[i](ret.val[i],p.val[i]);
		s=arr[arr[s].chain].p;
	}
	if(arr[s].depth<arr[e].depth)swap(s,e);
	p=query(1,num[e]+1,num[s]);
	for(int i=0;i<VAL_NUM;++i)ret.val[i]=metric[i](ret.val[i],p.val[i]);
	return ret;
}

int main(){
	int n,q,p,a,b,c;
	fastio();
	cin>>n>>q;
	for(int i=2;i<=n;++i){
		cin>>p;
		addEdge(p,i);
	}
	init();
	// may add preprocessing code of segtree here
	for(;q--;){
		cin>>a>>b>>c;
		Query ret=eval(a,b);
		printf(ret.val[0]?"YES\n":"NO\n");
		if(c&&ret.val[0])update(1,num[a],{0});
		else if(c)update(1,num[b],{0});
	}
}