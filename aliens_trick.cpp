// boj.kr/17439
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#define inf ((ll)(2e18))
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
using ld=long double;

struct Line{
	ll a,b;
	Line():a(0),b(-inf){}
	Line(ll a,ll b):a(a),b(b){}
	ll get(ll x){return a*x+b;}
};

struct Node{
	int l,r,idx;
	ll s,e;
};

int n,k;
int opt[50010];
ll arr[50010],psum[50010],dp[50010];

struct Li_Chao{
	vector<Node> tree;

	ll f(int j,int i){
		return dp[j]+(i-j)*(psum[i]-psum[j]);
	}

	void init(ll s,ll e){
		tree.clear();
		tree.push_back({-1,-1,0,s,e});
	}

	void update(int pos,int idx){
		ll s=tree[pos].s,e=tree[pos].e;
		ll m=s+e>>1;

		int low=tree[pos].idx,high=idx;
		if(f(low,s)>f(high,s)||(f(low,s)==f(high,s)&&f(low,e)>f(high,e)))swap(low,high);
		if(f(high,e)>=f(low,e)){
			tree[pos].idx=low;
			return;
		}
		if(f(low,m)<=f(high,m)){
			tree[pos].idx=low;
			if(tree[pos].r==-1){
				tree[pos].r=tree.size();
				tree.push_back({-1,-1,0,m+1,e});
			}
			update(tree[pos].r,high);
		}
		else{
			tree[pos].idx=high;
			if(tree[pos].l==-1){
				tree[pos].l=tree.size();
				tree.push_back({-1,-1,0,s,m});
			}
			update(tree[pos].l,low);
		}
	}
	int ans;
	void query(int pos,ll x){
		if(pos==-1)return;
		ll s=tree[pos].s,e=tree[pos].e;
		ll m=s+e>>1;
		if(f(tree[pos].idx,x)<f(ans,x))ans=tree[pos].idx;
		if(x<m)return query(tree[pos].l,x);
		else if(x>m)query(tree[pos].r,x);
	}
};

int solve(ll c){
	Li_Chao tree;
	tree.init(0,n);
	for(int i=1;i<=n;++i){
		tree.ans=0;
		tree.query(0,i);
		int j=tree.ans;
		dp[i]=tree.f(j,i)+c;
		opt[i]=opt[j]+1;
		tree.update(0,i);
	}
	return opt[n];
}

ll alien(){
	ll s=0,e=1e15,m;
	int lidx=0,ridx=n+1,lval,rval;
	while(s<=e){
		m=s+e>>1;
		int cnt=solve(m);
		if(cnt==k)return dp[n]-cnt*m;
		if(cnt>k){
			s=m+1;
			if(ridx>cnt)ridx=cnt,rval=dp[n]-cnt*m;
		}
		else{
			e=m-1;
			if(lidx<cnt)lidx=cnt,lval=dp[n]-cnt*m;
		}
	}
	return rval+(lval-rval)/(ridx-lidx)*(ridx-k);
}

int main(){
	scanf("%d %d",&n,&k);
	if(k>n)k=n;
	for(int i=1;i<=n;++i)scanf("%lld",arr+i),psum[i]=psum[i-1]+arr[i];
	printf("%lld",alien());
}