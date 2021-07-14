// boj.kr/13716
#include<cstdio>
#include<tuple>
#include<random>
#include<vector>
#include<algorithm>
#define mod 1000000007LL
using namespace std;
using ll=long long;

ll arr[500][41];

ll ipow(ll x,ll p){
	ll ret=1,piv=x;
	while(p){
		if(p&1)ret=(ret*piv)%mod;
		piv=(piv*piv)%mod;
		p>>=1;
	}
	return ret;
}

vector<int> berlekamp_massey(vector<int>x){
	vector<int>ls,cur;
	int lf,ld;
	for(int i=0;i<x.size();i++){
		ll t=0;
		for(int j=0;j<cur.size();j++)t=(t+ 1LL*x[i-j-1]*cur[j])%mod;
		if((t-x[i])%mod==0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf=i;
			ld=(t-x[i])%mod;
			continue;
		}
		ll k=-(x[i]-t)*ipow(ld,mod-2)%mod;
		vector<int>c(i-lf-1);
		c.push_back(k);
		for(auto &j:ls)c.push_back(-j*k%mod);
		if(c.size()<cur.size())c.resize(cur.size());
		for(int j=0;j<cur.size();j++)c[j]=(c[j]+cur[j])%mod;
		if(i-lf+(int)ls.size()>=(int)cur.size())tie(ls,lf,ld)=make_tuple(cur,i,(t-x[i])%mod);
		cur=c;
	}
	for(auto &i:cur)i=(i%mod+mod)%mod;
	return cur;
}

int get_nth(vector<int>rec,vector<int>dp,ll n){
	int m=rec.size();
	vector<int>s(m),t(m);
	s[0]=1;
	if(m!=1)t[1]=1;
	else t[0]=rec[0];
	auto mul=[&rec](vector<int>v,vector<int>w){
		int m=v.size();
		vector<int>t(2*m);
		for(int j=0;j<m;j++){
			for(int k=0;k<m;k++){
				t[j+k]+=1LL*v[j]*w[k]%mod;
				if(t[j+k]>=mod)t[j+k]-=mod;
			}
		}
		for(int j=2*m-1;j>=m;j--){
			for(int k=1;k<=m;k++){
				t[j-k]+=1LL*t[j]*rec[k-1]%mod;
				if(t[j-k]>=mod)t[j-k]-=mod;
			}
		}
		t.resize(m);
		return t;
	};
	while(n){
		if(n&1)s=mul(s,t);
		t=mul(t,t);
		n>>=1;
	}
	ll ret=0;
	for(int i=0;i<m;i++)ret+=1LL*s[i]*dp[i]%mod;
	return ret%mod;
}

int guess_nth_term(vector<int>x,ll n){
	if(n<x.size())return x[n];
	vector<int>v = berlekamp_massey(x);
	if(v.empty())return 0;
	return get_nth(v,x,n);
}

struct elem{int x,y,v;};

vector<int> get_min_poly(int n,vector<elem>M){
	vector<int>rnd1,rnd2;
	mt19937 rng(0x14004);
	auto randint=[&rng](int lb,int ub){
		return uniform_int_distribution<int>(lb,ub)(rng);
	};
	for(int i=0;i<n;i++){
		rnd1.push_back(randint(1,mod-1));
		rnd2.push_back(randint(1,mod-1));
	}
	vector<int> gobs;
	for(int i=0;i<2*n+2;i++){
		int tmp=0;
		for(int j=0;j<n;j++){
			tmp+=1LL*rnd2[j]*rnd1[j]%mod;
			if(tmp>=mod)tmp-=mod;
		}
		gobs.push_back(tmp);
		vector<int>nxt(n);
		for(auto &i:M){
			nxt[i.x]+=(1LL*i.v*rnd1[i.y])%mod;
			if(nxt[i.x]>=mod)nxt[i.x]-=mod;
		}
		rnd1=nxt;
	}
	auto sol=berlekamp_massey(gobs);
	reverse(sol.begin(),sol.end());
	return sol;
}

ll det(int n,vector<elem>M){
	vector<int> rnd;
	mt19937 rng(0x14004);
	auto randint=[&rng](int lb,int ub){return uniform_int_distribution<int>(lb,ub)(rng);};
	for(int i=0; i<n; i++)rnd.push_back(randint(1,mod-1));
	for(auto &i:M)i.v=(1LL*i.v*rnd[i.y])%mod;
	auto sol=get_min_poly(n, M)[0];
	if(n%2==0)sol=mod-sol;
	for(auto &i:rnd)sol=1LL*sol*ipow(i,mod-2)%mod;
	return sol;
}

int main(){
	ll n,tot=0;
	int k;
	scanf("%lld %d",&n,&k);
	vector<int> v;
	arr[1][0]=1,arr[2][0]=2;
	for(int i=1;i<=10*k;++i){
		if(i>2)arr[i][0]=(arr[i-1][0]+arr[i-2][0])%mod;
		for(int j=1;j<=k;++j)arr[i][j]=(arr[i][j-1]*i)%mod;
		tot+=arr[i][k];
		tot%=mod;
		v.push_back(tot);
	}
	printf("%d",guess_nth_term(v,n-1));
}