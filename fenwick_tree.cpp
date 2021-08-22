#include<cstdio>
#define N (1<<20)

using namespace std;
using ll=long long;

ll tree[N+1],arr[N];

void update(int idx,ll diff){
	while(idx<=N){
		tree[idx]+=diff;
		idx+=(idx&-idx);
	}
}

ll query(int idx){
	ll ans=0;
	while(idx>0){
		ans+=tree[idx];
		idx&=idx-1;
	}
	return ans;
}

ll query(int l,int r){
	if(r>N)r=N;
	return query(r)-query(l-1);
}

int main(){
	int n,m,k,a;
	ll b,c;
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;++i)scanf("%lld",arr+i),update(i,arr[i]);
	for(int i=0;i<m+k;++i){
		scanf("%d %lld %lld",&a,&b,&c);
		if(a==1){
			update(b,c-arr[b]);
			arr[b]=c;
		}
		else printf("%lld\n",query(b,c));
	}
}