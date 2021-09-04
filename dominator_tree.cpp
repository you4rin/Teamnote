// code based on https://github.com/koosaga/DeobureoMinkyuParty
// boj.kr/20174
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAXN 100010

using namespace std;

vector<int> E[MAXN], RE[MAXN], rdom[MAXN];

int result[MAXN];
int S[MAXN], RS[MAXN], cs;
int par[MAXN], val[MAXN], sdom[MAXN], rp[MAXN], dom[MAXN];

void clear(int n) {
	cs = 0;
	for(int i=0;i<=n;i++) {
		par[i] = val[i] = sdom[i] = rp[i] = dom[i] = S[i] = RS[i] = 0;
		E[i].clear(); RE[i].clear(); rdom[i].clear();
	}
}
void add_edge(int x, int y) { E[x].push_back(y); }
void Union(int x, int y) { par[x] = y; }
int Find(int x, int c = 0) {
	if(par[x] == x) return c ? -1 : x;
	int p = Find(par[x], 1);
	if(p == -1) return c ? par[x] : val[x];
	if(sdom[val[x]] > sdom[val[par[x]]]) val[x] = val[par[x]];
	par[x] = p;
	return c ? p : val[x];
}
void dfs(int x) {
	RS[ S[x] = ++cs ] = x;
	par[cs] = sdom[cs] = val[cs] = cs;
	for(int e : E[x]) {
		if(S[e] == 0) dfs(e), rp[S[e]] = S[x];
		RE[S[e]].push_back(S[x]);
	}
}
int solve(int s, int *up) { // Calculate idoms
	dfs(s);
	for(int i=cs;i;i--) {
		for(int e : RE[i]) sdom[i] = min(sdom[i], sdom[Find(e)]);
		if(i > 1) rdom[sdom[i]].push_back(i);
		for(int e : rdom[i]) {
			int p = Find(e);
			if(sdom[p] == i) dom[e] = i;
			else dom[e] = p;
		}
		if(i > 1) Union(i, rp[i]);
	}
	for(int i=2;i<=cs;i++) if(sdom[i] != dom[i]) dom[i] = dom[dom[i]];
	for(int i=2;i<=cs;i++) up[RS[i]] = RS[dom[i]];
	return cs;
}

int main(){
	int n,m,k,s,e,ans=0;
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=m;++i)add_edge(1,i+1);
	for(int i=0;i<k;++i){
		scanf("%d %d",&s,&e);
		add_edge(s+1,e+1);
	}
	solve(1,result);
	for(int i=2;i<=n+1;++i)if(result[i]==1)++ans;
	printf("%d",ans);
}