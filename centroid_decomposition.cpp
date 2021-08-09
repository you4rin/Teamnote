// boj.kr/13514
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define inf ((int)(1e9))

using namespace std;

struct Node{
	int sz,del,pcent,depth,color;
	int p[18];
	multiset<int> st;
	vector<int> v;
	vector<int> w;
};

Node arr[100010];

void dfs(int p,int c){
	arr[c].p[0]=p;
	arr[c].depth=(p?arr[p].depth+1:1);
	for(int i=1;i<18;++i)arr[c].p[i]=arr[arr[c].p[i-1]].p[i-1];
	for(auto i:arr[c].v)if(i!=p)dfs(c,i);
}

int init(int p,int c){
	arr[c].sz=1;
	for(auto i:arr[c].v)if(i!=p&&!arr[i].del)arr[c].sz+=init(c,i);
	return arr[c].sz;
}

int centroid(int p,int c,int sz){
	for(auto i:arr[c].v)if(p!=i&&!arr[i].del&&sz/2<arr[i].sz)return centroid(c,i,sz);
	return c;
}

// building centroid tree: decompose(0,1)
// caution: using 1-based index
void decompose(int before,int root){
	int sz=init(0,root);
	int cent=centroid(0,root,sz);
	arr[cent].del=1;
	arr[cent].pcent=before;

	if(before)arr[before].w.push_back(cent);

	for(auto i:arr[cent].v){
		if(!arr[i].del){
			decompose(cent,i);
		}
	}
}

int lca(int a,int b){
	int diff;
	if(arr[a].depth<arr[b].depth)swap(a,b);
	diff=arr[a].depth-arr[b].depth;
	for(int i=0;diff;++i){
		if(diff&1)a=arr[a].p[i];
		diff>>=1;
	}
	if(a==b)return a;
	for(int i=17;i>=0;--i)if(arr[a].p[i]!=arr[b].p[i])a=arr[a].p[i],b=arr[b].p[i];
	return arr[a].p[0];
}

int getdist(int a,int b){
	return arr[a].depth+arr[b].depth-2*arr[lca(a,b)].depth;
}

void update(int x){
	int cur=x;
	arr[x].color=!arr[x].color;
	while(1){
		int dist=getdist(x,cur);
		if(arr[x].color)arr[cur].st.insert(dist);
		else arr[cur].st.erase(arr[cur].st.find(dist));
		if(!(cur=arr[cur].pcent))break;
	}
}

int query(int x){
	int cur=x,ret=inf;
	while(1){
		int dist=getdist(cur,x);
		if(arr[cur].st.size())ret=min(ret,dist+*arr[cur].st.begin());
		if(!(cur=arr[cur].pcent))break;
	}
	if(ret==inf)return -1;
	return ret;
}

int main(){
	fastio();
	int n,s,e,q,a,b;
	cin>>n;
	for(int i=1;i<n;++i){
		cin>>s>>e;
		arr[s].v.push_back(e);
		arr[e].v.push_back(s);
	}
	dfs(0,1);
	decompose(0,1);
	for(cin>>q;q--;){
		cin>>a>>b;
		if(a==1)update(b);
		else cout<<query(b)<<"\n";
	}
}