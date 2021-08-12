// boj.kr/12766
#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define inf ((int)(2e9))
#define linf ((ll)(9e18))

using namespace std;
using ll=long long;
using pii=pair<int,int>;

struct Node{
	int dist;
	vector<pii> v,rv;
};

int n,b,s,r;
Node arr[5010];
int d[5010];
ll tot[5010];
ll dp[5010][5010];
int p[5010][5010];

void init(){
	int c,d,w;
	cin>>n>>b>>s>>r;
	for(int i=0;i<r;++i){
		cin>>c>>d>>w;
		arr[c].v.push_back({d,w});
		arr[d].rv.push_back({c,w});
	}
}

void dijkstra(bool r){
	for(int i=1;i<=n;++i)arr[i].dist=inf;
	arr[b+1].dist=0;
	priority_queue<pii,vector<pii>,greater<pii>> pq;
	pq.push({0,b+1});
	while(pq.size()){
		pii tmp=pq.top();
		int dist=tmp.first,idx=tmp.second;
		pq.pop();
		if(dist>arr[idx].dist)continue;
		d[idx]+=dist;
		for(auto it=r?arr[idx].rv.begin():arr[idx].v.begin();it!=(r?arr[idx].rv.end():arr[idx].v.end());++it){
			int nxt=it->first,val=it->second;
			if(arr[nxt].dist>arr[idx].dist+val){
				arr[nxt].dist=arr[idx].dist+val;
				pq.push({arr[nxt].dist,nxt});
			}
		}
	}
}

void dnc(int t,int s,int e,int l,int r){
	if(s>e)return;
	int m=s+e>>1;
	dp[t][m]=linf;
	p[t][m]=-1;
	int lo=l,hi=min(r,m-1);
	for(int i=lo;i<=hi;++i){
		ll tmp=dp[t-1][i]+(tot[m]-tot[i])*(m-i-1);
		if(dp[t][m]>tmp)dp[t][m]=tmp,p[t][m]=i;
	}
	dnc(t,s,m-1,l,p[t][m]);
	dnc(t,m+1,e,p[t][m],r);
}

int main(){
	fastio();
	init();
	dijkstra(0);
	dijkstra(1);
	sort(d+1,d+b+1);
	for(int i=1;i<=b;++i)tot[i]=tot[i-1]+d[i];
	for(int i=1;i<=b;++i)dp[1][i]=tot[i]*(i-1),p[1][i]=1;
	for(int i=2;i<=s;++i)dnc(i,i,b,0,b);
	cout<<dp[s][b];
}