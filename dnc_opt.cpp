// boj.kr/13262
#include<iostream>
#include<string>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)

using namespace std;
using ll=long long;

int n,k,opt[5010][5010];
ll arr[5010],cost[5010][5010],dp[5010][5010];

void init(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>arr[i];
	// cost initialization
	for(int i=1;i<=n;++i){
		for(int j=i;j<=n;++j){
			cost[i][j]=cost[i][j-1]|arr[j];
		}
	}
	for(int i=1;i<=n;++i){
		dp[1][i]=cost[1][i];
		opt[1][i]=1;
	}
}

void dnc(int t,int s,int e,int l,int r){
	if(s>e)return;
	int m=s+e>>1;
	opt[t][m]=dp[t][m]=-1;
	for(int i=l;i<=min(r,m);++i){
		ll tmp=dp[t-1][i-1]+cost[i][m];
		if(dp[t][m]<tmp){
			dp[t][m]=tmp;
			opt[t][m]=i;
		}
	}
	dnc(t,s,m-1,l,opt[t][m]);
	dnc(t,m+1,e,opt[t][m],r);
}

int main(){
	fastio();
	init();
	for(int i=2;i<=k;++i)dnc(i,i,n,i,n);
	cout<<dp[k][n];
}