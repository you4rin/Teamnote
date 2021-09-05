// boj.kr/13309
#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
#pragma GCC optimize("Ofast") 
#pragma GCC target("avx,avx2,fma") 
#pragma GCC optimize ("unroll-loops")
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define cur seg[pos]
#define left seg[pos*2]
#define right seg[pos*2+1]
#define N (1<<18)
#define VAL_NUM 1

using namespace std;
using ll=long long;
using pii=pair<int,int>;

struct Node{
	int sz,p,depth,chain;
	vector<int> v;
};

struct Seg{
	int s,e;
	int val;
};

Node arr[N];
Seg seg[N<<1];
int cnt;
int num[N]; // vertex idx -> seg idx
int inv[N]; // seg idx -> vertex idx
vector<int> chain[N];

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

void update(int pos,int idx,int val){
	if(cur.s>idx||idx>cur.e)return;
	if(seg[pos].s==seg[pos].e){
		for(int i=0;i<VAL_NUM;++i)cur.val=val;
		return;
	}
	update(pos*2,idx,val);
	update(pos*2+1,idx,val);
	// operations
	cur.val=left.val*right.val;
}

int query(int pos,int s,int e){
	int ret=1,l,r; // init value may be fixed
	if(cur.s>e||s>cur.e||s>e)return ret;
	if(cur.s>=s&&e>=cur.e){
		for(int i=0;i<VAL_NUM;++i)ret=cur.val;
		return ret;
	}
	// operations
	return query(pos*2,s,e)*query(pos*2+1,s,e);
}

void init(){
	// seginit
	for(int pos=N;pos<2*N;++pos)cur.s=cur.e=pos-N+1; // 1-based index
	for(int pos=N-1;pos;--pos)cur.s=left.s,cur.e=right.e;
	for(int pos=1;pos<2*N;++pos)for(int i=0;i<VAL_NUM;++i)cur.val=1; // may be removed
	// hldinit
	arr[1].depth=arr[1].chain=1;
	dfs1(1);dfs2(1);
}

// add 'undirected', 'weighted' edge
void addEdge(int src,int dst){
	arr[src].v.push_back(dst);
	arr[dst].v.push_back(src);
}

int eval(int s,int e){
	int ret=1; // init value may be fixed
	while(arr[s].chain!=arr[e].chain){
		if(arr[arr[s].chain].depth<arr[arr[e].chain].depth)swap(s,e);
		ret*=query(1,num[arr[s].chain],num[s]);
		s=arr[arr[s].chain].p;
	}
	if(arr[s].depth<arr[e].depth)swap(s,e);
	// operations
	return ret*query(1,num[e]+1,num[s]);
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
		int ret=eval(a,b);
		printf(ret?"YES\n":"NO\n");
		if(c&&ret)update(1,num[a],{0});
		else if(c)update(1,num[b],{0});
	}
}