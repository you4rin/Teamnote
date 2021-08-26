#include<cstdio>
#include<queue>
#include<algorithm>

using namespace std;
using ll=long long;
using pll=pair<ll,ll>;

priority_queue<ll> pq;

pll euc(ll a,ll b){
	if(!b)return {1,0};
	pll ret=euc(b,a%b);
	ret={ret.second,ret.first-a/b*ret.second};
	ll t=ret.first/b;
	if(ret.first-b*t<0)--t;
	return{ret.first-b*t,ret.second+a*t};
}

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

ll lcm(ll a,ll b){
	return a*b/gcd(a,b);
}

pll crt(ll p1,ll p2,ll a1,ll a2){
	pll ret={lcm(p1,p2),0};
	ll g=gcd(p1,p2);
	if(a1%g^a2%g)return {-1,-1};
	ret.second=euc(p1,p2).first*(a2-a1)/g*p1+a1;
	ret.second=(ret.second%ret.first+ret.first)%ret.first;
	return ret;
}

int main(){
	ll a,b,c,d,e,f,g;
	ll p1,p2,p3,a1,a2,a3,pm,am;
	scanf("%lld %lld %lld %lld %lld %lld %lld",&a,&b,&c,&d,&e,&f,&g);
	for(int i=1;i<=50;++i){
		if(2*i>=a||2*i>=b)break;
		pq.push(i*(a-2*i)*(b-2*i));
	}
	p1=pq.top();
	pq.pop();
	p2=pq.top();
	pq.pop();
	p3=pq.top();
	pq.pop();
	a1=c,a2=d,a3=e;
	pll ret=crt(p1,p2,a1,a2);
	ret=crt(ret.first,p3,ret.second,a3);
	printf("%lld",(g-ret.second)/ret.first*ret.first+ret.second);
}