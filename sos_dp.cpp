// boj.kr/2803
#include<cstdio>

using namespace std;
using ll=long long;

const ll mod=1000000007;

ll arr[1100000];
ll dp[1100000];

int main(){
	int n,m,k,tmp,bit;
	ll ans=0;
	scanf("%d %d",&n,&m);
	for(int i=0;i<(1<<m);++i)arr[i]=1;
	for(int i=0;i<n;++i){
		scanf("%d",&k);
		bit=0;
		for(int j=0;j<k;++j){
			scanf("%d",&tmp);
			bit|=(1<<(tmp-1));
		}
		arr[bit]*=2;
		arr[bit]%=mod;
	}
	for(int i=0;i<(1<<m);++i)dp[i]=arr[i];
	for(int i=0;i<m;++i){
		for(int j=0;j<(1<<m);++j){
			if(j&(1<<i)){
				dp[j]*=dp[j^(1<<i)];
				dp[j]%=mod;
			}
		}
	}
	for(int i=0;i<(1<<m);++i){
		ans+=(m-__builtin_popcount(i)&1?-1:1)*dp[i];
		ans+=mod;
		ans%=mod;
	}
	printf("%lld",ans);
}