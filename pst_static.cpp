// boj.kr/11012
#include<cstdio>
#include<vector>
#include<algorithm>
#define N (1<<17)

using namespace std;
using pii=pair<int,int>;
using ll=long long;

struct Node{
	int l,r,s,e,sum;
};

struct PST{
	vector<Node> tree;

	void init(int pos,int s,int e){
		if(s==e)return;
		int m=s+e>>1;
		tree[pos].l=tree.size();
		tree.push_back({-1,-1,s,m,0});
		tree[pos].r=tree.size();
		tree.push_back({-1,-1,m+1,e,0});
		init(tree[pos].l,s,m);
		init(tree[pos].r,m+1,e);
	}

	void update(int ppos,int cpos,int idx,int s,int e){
		tree[cpos].sum=tree[ppos].sum+1;
		tree[cpos].s=tree[ppos].s;
		tree[cpos].e=tree[ppos].e;
		if(s==e)return;
		int m=s+e>>1;
		if(idx>m){
			tree[cpos].l=tree[ppos].l;
			tree[cpos].r=tree.size();
			tree.push_back({-1,-1,0});
			update(tree[ppos].r,tree[cpos].r,idx,m+1,e);
		}
		else{
			tree[cpos].r=tree[ppos].r;
			tree[cpos].l=tree.size();
			tree.push_back({-1,-1,0});
			update(tree[ppos].l,tree[cpos].l,idx,s,m);
		}
	}

	int query(int pos,int s,int e){
		if(tree[pos].s>e||s>tree[pos].e)return 0;
		if(tree[pos].s>=s&&e>=tree[pos].e)return tree[pos].sum;
		return query(tree[pos].l,s,e)+query(tree[pos].r,s,e);
	}
}pst;

pii point[N];
int root[N];
int t,n,m,b,pos,p,q,r,s;
ll ans;

void pstinit(){
	pst.tree.clear();
	pst.tree.push_back({-1,-1,0,N-1,0});
	pst.init(0,0,N-1);
	for(int i=0;i<N;++i)root[i]=0;
	b=pos=ans=0;
	for(int i=0;i<n;++i)scanf("%d %d",&point[i].first,&point[i].second);
	sort(point,point+n);
}

void pstupdate(int idx){
	root[idx]=pst.tree.size();
	pst.tree.push_back({-1,-1,0,N-1,0});
	pst.update(b,root[idx],point[pos++].second,0,N-1);
	b=root[idx];
}

ll pstquery(int p,int q,int r,int s){
	return pst.query(root[q],r,s)-(p?pst.query(root[p-1],r,s):0);
}

int main(){
	pst.tree.reserve(N+1);
	for(scanf("%d",&t);t--;){
		scanf("%d %d",&n,&m);
		pstinit();
		for(int i=0;i<N;++i){
			root[i]=b;
			if(pos==n||point[pos].first!=i)continue;
			while(point[pos].first==i)pstupdate(i);
		}
		for(int i=0;i<m;++i){
			scanf("%d %d %d %d",&p,&q,&r,&s);
			ans+=pstquery(p,q,r,s);
		}
		printf("%lld\n",ans);
	}
}