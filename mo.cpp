// boj.kr/13547
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

struct Q{
	int l,r,idx;
};

Q query[100010];
int cnt[1000010];
int arr[100010];
int ans[100010];
int rt,cur;

bool cmp(Q&x,Q&y){
	if(x.r/rt!=y.r/rt)return x.r/rt<y.r/rt;
	return x.l<y.l;
}

void f(int idx,bool add){
	if(add){if(!(cnt[arr[idx]]++))++cur;}
	else{if(!(--cnt[arr[idx]]))--cur;}
}

int main(){
	int n,q,l,r;
	scanf("%d",&n);
	rt=(int)sqrt(n);
	for(int i=1;i<=n;++i)scanf("%d",arr+i);
	scanf("%d",&q);
	for(int i=0;i<q;++i){
		scanf("%d %d",&query[i].l,&query[i].r);
		query[i].idx=i;
	}
	sort(query,query+q,cmp);
	l=1;r=0;
	for(int i=0;i<q;++i){
		while(query[i].l<l)f(--l,1);
		while(query[i].r>r)f(++r,1);
		while(query[i].l>l)f(l++,0);
		while(query[i].r<r)f(r--,0);
		ans[query[i].idx]=cur;
	}
	for(int i=0;i<q;++i)printf("%d\n",ans[i]);
}