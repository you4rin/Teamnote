// boj.kr/11408
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#define S 0
#define T 801
#define N 810
#define WORK 400
#define x first
#define y second
#define inf ((int)(1e9))
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)

using namespace std;
using ll=long long;
using pii=pair<int,int>;

struct Edge{
	int dst;
	int cap,cost;
	int rev;
};

int dist[N];
bool inq[N];
pii prv[N];
vector<Edge> v[N];

bool bfs(){
	queue<int> q;
	for(int i=S;i<=T;++i)inq[i]=0,prv[i].x=prv[i].y=-1,dist[i]=inf;
	dist[0]=0,inq[0]=1;
	q.push(S);
	while(q.size()){
		int now=q.front();
		q.pop();
		inq[now]=0;
		for(int i=0;i<v[now].size();++i){
			int next=v[now][i].dst;
			if(v[now][i].cap>0&&dist[next]>dist[now]+v[now][i].cost){
				dist[next]=dist[now]+v[now][i].cost;
				prv[next]={now,i};
				if(!inq[next]){
					q.push(next);
					inq[next]=1;
				}
			}
		}
	}
	return prv[T].x!=-1;
}

int dfs(int now,int& flow){
	int ret=0;
	for(int i=T;i!=S;i=prv[i].x)flow=min(flow,v[prv[i].x][prv[i].y].cap);
	for(int i=T;i!=S;i=prv[i].x){
		ret+=flow*v[prv[i].x][prv[i].y].cost;
		v[prv[i].x][prv[i].y].cap-=flow;
		v[v[prv[i].x][prv[i].y].dst][v[prv[i].x][prv[i].y].rev].cap+=flow;
	}
	return ret;
}

// add 'directed' edge
void addEdge(int src,int dst,int cap,int cost){
	v[src].push_back({dst,cap,cost,(int)v[dst].size()});
	v[dst].push_back({src,0,-cost,(int)v[src].size()-1});
}

void solve(){
	int ans=0,tot=0;
	while(bfs()){
		while(1){
			int flow=inf;
			int ret=dfs(S,flow);
			if(!flow)break;
			tot+=flow,ans+=ret;
		}
	}
	cout<<tot<<"\n"<<ans;
}

int main(){
	fastio();
	int n,m,e,w;
	int val;
	cin>>n>>m;
	for(int i=1;i<=n;++i)addEdge(S,i,1,0);
	for(int i=1;i<=m;++i)addEdge(WORK+i,T,1,0);
	for(int i=1;i<=n;++i){
		cin>>val;
		for(int j=0;j<val;++j){
			cin>>e>>w;
			addEdge(i,WORK+e,1,w);
		}
	}
	solve();
}