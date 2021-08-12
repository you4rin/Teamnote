// boj.kr/13974
#include<iostream>
#include<string>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define inf ((int)(1e9))

using namespace std;

int c[5010];
int dp[5010][5010];
int opt[5010][5010];

void init(int n){
	for(int i=1;i<=n;++i){
		cin>>c[i];
		c[i]+=c[i-1];
		opt[i-1][i]=i;
	}
}

void knuth(int n){
	init(n);
	for(int i=2;i<=n;++i){
		for(int j=0;j+i<=n;++j){
			dp[j][j+i]=inf;
			for(int k=opt[j][j+i-1];k<=opt[j+1][j+i];++k){ 
				// opt[j][j+i-1] <= opt[j][j+i] <= opt[j+1][j+i]
				int tmp=dp[j][k]+dp[k][j+i]+c[i+j]-c[j];
				if(dp[j][j+i]>tmp){
					opt[j][j+i]=k;
					dp[j][j+i]=tmp;
				}
			}
		}
	}
	cout<<dp[0][n]<<"\n";
}

int main(){
	fastio();
	int t,n;
	for(cin>>t;t--;){
		cin>>n;
		knuth(n);
	}
}