// boj.kr/2150
#include<cstdio>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

struct Node{
	int visit,comp;
	vector<int> v;
};

Node arr[100010];
vector<vector<int>> scc;
stack<int> stk;
int cnt;

bool comp(vector<int>a,vector<int>b){
	return b.size()?a[0]<b[0]:1;
}

int dfs(int idx){
	arr[idx].visit=++cnt;
	int ret=arr[idx].visit;
	stk.push(idx);
	for(auto i:arr[idx].v){
		if(!arr[i].visit)ret=min(ret,dfs(i));
		else if(!arr[i].comp)ret=min(ret,arr[i].visit);
	}
	if(arr[idx].visit==ret){
		vector<int> tmp;
		while(1){
			int t=stk.top();
			stk.pop();
			arr[t].comp=scc.size()+1;
			tmp.push_back(t);
			if(t==idx)break;
		}
		scc.push_back(tmp);
	}
	return ret;
}

void find_scc(int n){
	for(int i=1;i<=n;++i)if(!arr[i].visit)dfs(i);
}

int main(){
	int n,m,s,e;
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;++i){
		scanf("%d %d",&s,&e);
		arr[s].v.push_back(e);
	}
	find_scc(n);
	for(auto& i:scc)sort(i.begin(),i.end());
	sort(scc.begin(),scc.end(),comp);
	printf("%d\n",scc.size());
	for(auto i:scc){
		for(auto j:i)printf("%d ",j);
		printf("-1\n");
	}
}