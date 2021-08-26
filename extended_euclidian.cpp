// boj.kr/14565
#include<cstdio>
#include<algorithm>

using namespace std;
using ll=long long;
using pll=pair<ll,ll>;

pll euc(ll a,ll b){
	if(!b)return {1,0};
	pll ret=euc(b,a%b);
	ret={ret.second,ret.first-(a/b)*ret.second};
	ll t=ret.first/b*b;
	if(ret.first-b*t<0)--t;
	return {ret.first-b*t,ret.second+a*t};
}

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

int main(){
	ll n,a;
	scanf("%lld %lld",&n,&a);
	printf("%lld ",n-a);
	if(gcd(n,a)!=1)printf("-1");
	else printf("%lld",euc(a,n).first);
}