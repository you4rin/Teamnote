// boj.kr/15892
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#define S 0
#define T 301
#define N 310
#define inf ((int)(1e9))
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)

using namespace std;
using ll=long long;

struct Edge{
	int dst;
	int cap;
	int rev;
};

int level[N],work[N];
vector<Edge> v[N];

bool bfs(){
	for(int i=S;i<=T;++i)level[i]=-1;
	queue<int> q;
	level[S]=0;
	q.push(S);
	while(q.size()){
		int now=q.front();
		q.pop();
		for(auto i:v[now]){
			int next=i.dst;
			if(level[next]==-1&&i.cap>0){
				level[next]=level[now]+1;
				q.push(next);
			}
		}
	}
	return level[T]!=-1;
}

int dfs(int now,int flow){
	if(now==T)return flow;
	for(int& i=work[now];i<v[now].size();++i){
		int next=v[now][i].dst;
		if(level[next]==level[now]+1&&v[now][i].cap>0){
			int ret=dfs(next,min(flow,v[now][i].cap));
			if(ret>0){
				v[now][i].cap-=ret;
				v[next][v[now][i].rev].cap+=ret;
				return ret;
			}
		}
	}
	return 0;
}

// add 'directed' edge
void addEdge(int src,int dst,int cap){
	v[src].push_back({dst,cap,(int)v[dst].size()});
	v[dst].push_back({src,0,(int)v[src].size()-1});
}

void solve(){
	int ans=0;
	while(bfs()){
		for(int i=S;i<=T;++i)work[i]=0;
		while(1){
			int ret=dfs(S,inf);
			if(!ret)break;
			ans+=ret;
		}
	}
	cout<<ans;
}

int main(){
	fastio();
	int n,m,s,e;
	int val;
	cin>>n>>m;
	addEdge(S,1,inf);
	addEdge(n,T,inf);
	for(int i=0;i<m;++i){
		cin>>s>>e>>val;
		addEdge(s,e,val);
		addEdge(e,s,val);
	}
	solve();
}