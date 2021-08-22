// https://codeforces.com/contest/739/problem/E
#include<cstdio>

using namespace std;
using ld=long double;

int n,a,b,opt[2010][2010];
ld dp[2010][2010],p[2010],u[2010],pu[2010];
ld l=0,r=1,m;

int solve(ld lambda){
	int ret=0,acnt=a;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=a;++j){
			dp[i][j]=dp[i-1][j];
			opt[i][j]=0;
			if(j&&dp[i][j]<dp[i-1][j-1]+p[i])dp[i][j]=dp[i-1][j-1]+p[i],opt[i][j]=1;
			if(dp[i][j]<dp[i-1][j]+u[i]-lambda)dp[i][j]=dp[i-1][j]+u[i]-lambda,opt[i][j]=2;
			if(j&&dp[i][j]<dp[i-1][j-1]+pu[i]-lambda)dp[i][j]=dp[i-1][j-1]+pu[i]-lambda,opt[i][j]=3;
		}
	}
	for(int i=n;i;--i){
		if(opt[i][acnt]>1)++ret;
		if(opt[i][acnt]&1)--acnt;
	}
	return ret;
}

int main(){
	scanf("%d %d %d",&n,&a,&b);
	for(int i=1;i<=n;++i)scanf("%Lf",p+i);
	for(int i=1;i<=n;++i)scanf("%Lf",u+i),pu[i]=p[i]+u[i]-p[i]*u[i];
	for(int i=0;i<50;++i){
		m=(l+r)/2;
		if(solve(m)>b)l=m;
		else r=m;
	}
	solve(r);
	printf("%.10Lf",dp[n][a]+r*b);
}