// boj.kr/13263
#include<iostream>
#include<string>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define inf 1e60
#define N 100010

using namespace std;
using ll=long long;
using ld=long double;

struct line{
	ll a,b;
	ld s = -inf;
};

ll a[N],b[N],dp[N],psum[N];
line f[N];

ld cross(const line& a,const line& b){
	return ((ld)(a.b-b.b))/(b.a-a.a);
}

void cht(int n){
	// precompute psum & dp here if you want
	// for(int i=1;i<=n;++i)dp[i]+=0;
	int top=0,pos=0;
	for(int i=1;i<n;++i){ // check range
		line g;
		g.a=b[i-1],g.b=dp[i-1];
		while(top>0){
			g.s=cross(g,f[top-1]);
			if(f[top-1].s<g.s)break;
			--top;
		}
		f[top++]=g;
		ll x=a[i];
		while(pos+1<top&&x>f[pos+1].s)++pos;
		dp[i]=f[pos].a*x+f[pos].b; // may be revised
	}
}

int main(){
	fastio();
	int n;
	cin>>n;
	for(int i=0;i<n;++i)cin>>a[i];
	for(int i=0;i<n;++i)cin>>b[i];
	cht(n);
	cout<<dp[n-1];
}