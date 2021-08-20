// boj.kr/4149
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;
using ll=long long;
using i128=__int128;

vector<ll> p={2,3,5,7,11,13,17,19,23,29,31,37};
vector<ll> factor;

ll mul(ll x,ll y,ll mod){
	return ((i128)x*y)%mod;
}

ll add(ll x,ll y,ll mod){
	return ((i128)x+y)%mod;
}

ll func(ll x,ll c,ll mod){
	return add(mul(x,x,mod),c,mod);
}

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

ll power(ll x,ll c,ll mod){
	ll ret=1,cur=x;
	while(c){
		if(c&1)ret=mul(ret,cur,mod);
		cur=mul(cur,cur,mod);
		c>>=1;
	}
	return ret;
}

bool miller(ll x,ll a){
	ll d=x-1,tmp;
	while(~d&1){
		if(power(a,d,x)==x-1)return 1;
		d>>=1;
	}
	tmp=power(a,d,x);
	return tmp==x-1||tmp==1;
}

bool isprime(ll x){
	if(x<2)return 0;
	for(ll i:p){
		if(i==x)return 1;
		if(x>40&&!miller(x,i))return 0;
	}
	return x>40?1:0;
}

void f(ll n){
	if(n<2)return;
	if(~n&1){
		factor.push_back(2);
		f(n>>1);
		return;
	}
	if(isprime(n)){
		factor.push_back(n);
		return;
	}
	ll r,t,c,g=n;
	do{
		if(g==n){
			r=t=rand()%(n-2)+2;
			c=rand()%(n-2)+1;
		}
		t=func(t,c,n);
		r=func(func(r,c,n),c,n);
		g=gcd(abs(r-t),n);
	}while(g==1);
	f(g);f(n/g);
}

void fact(ll n){
	f(n);
	sort(factor.begin(),factor.end());
}

int main(){
	srand(10310401);
	ll n;
	scanf("%lld",&n);
	fact(n);
	for(auto i:factor)printf("%lld\n",i);
}