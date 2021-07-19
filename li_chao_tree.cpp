// boj.kr/12795
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#define inf ((ll)(2e18))
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;
using ll=long long;
using ld=long double;

struct Line{
	ll a,b;
	Line():a(0),b(-inf){}
	Line(ll a,ll b):a(a),b(b){}
	ll get(ll x){return a*x+b;}
};

struct Node{
	int l,r;
	ll s,e;
	Line line;
};

struct Li_Chao{
	vector<Node> tree;

	void init(ll s,ll e){
		tree.clear();
		tree.push_back({-1,-1,s,e,Line()});
	}

	void update(int pos,Line v){
		ll s=tree[pos].s,e=tree[pos].e;
		ll m=s+e>>1;

		Line low=tree[pos].line,high=v;
		if(low.get(s)>high.get(s)||(low.get(s)==high.get(s)&&low.get(e)>high.get(e)))swap(low,high);
		if(high.get(e)>=low.get(e)){
			tree[pos].line=high;
			return;
		}
		if(low.get(m)<=high.get(m)){
			tree[pos].line=high;
			if(tree[pos].r==-1){
				tree[pos].r=tree.size();
				tree.push_back({-1,-1,m+1,e,Line()});
			}
			update(tree[pos].r,low);
		}
		else{
			tree[pos].line=low;
			if(tree[pos].l==-1){
				tree[pos].l=tree.size();
				tree.push_back({-1,-1,s,m,{0,-inf}});
			}
			update(tree[pos].l,high);
		}
	}

	ll query(int pos,ll x){
		if(pos==-1)return -inf;
		ll s=tree[pos].s,e=tree[pos].e;
		ll m=s+e>>1;
		if(x<=m)return max(tree[pos].line.get(x),query(tree[pos].l,x));
		else return max(tree[pos].line.get(x),query(tree[pos].r,x));
	}
};

Li_Chao seg;

int main(){
	fastio();
	ll n,q,a,b,x;
	seg.init(-1e12,1e12);
	for(cin>>n;n--;){
		cin>>q;
		if(q-1){
			cin>>x;
			cout<<seg.query(0,x)<<"\n";
		}
		else{
			cin>>a>>b;
			seg.update(0,{a,b});
		}
	}
}