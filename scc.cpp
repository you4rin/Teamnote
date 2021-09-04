// boj.kr/2150
#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;

struct Node{
	int visit;
	vector<int> v;
};

vector<vector<int>> scc;
stack<int> stk;
Node arr[10010];
Node inv[10010];

bool comp(vector<int>a,vector<int>b){
	return b.size()?a[0]<b[0]:1;
}

void dfs(int idx){
	arr[idx].visit=1;
	for(auto i:arr[idx].v)if(!arr[i].visit)dfs(i);
	stk.push(idx);
}

void func(int idx,int num){
	inv[idx].visit=1;
	scc[num].push_back(idx);
	for(auto i:inv[idx].v)if(!inv[i].visit)func(i,num);
}

void findscc(int n){
	for(int i=1;i<=n;++i)if(!arr[i].visit)dfs(i);
	while(!stk.empty()){
		scc.push_back(vector<int>());
		func(stk.top(),scc.size()-1);
		while(!stk.empty()&&inv[stk.top()].visit)stk.pop();
	}
}

int main(){
	int n,m,s,e;
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;++i){
		scanf("%d %d",&s,&e);
		arr[s].v.push_back(e);
		inv[e].v.push_back(s);
	}
	findscc(n);
	for(auto& i:scc)sort(i.begin(),i.end());
	sort(scc.begin(),scc.end(),comp);
	printf("%d\n",scc.size());
	for(auto i:scc){
		for(auto j:i)printf("%d ",j);
		printf("-1\n");
	}
}