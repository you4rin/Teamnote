// boj.kr/3682
#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;

struct Node{
	int visit,scc;
	vector<int> v;
};

struct SCC{
	vector<int> in,out;
};

Node arr[20010];
SCC fin[20010];
vector<vector<int>> scc;
stack<int> stk;
int cnt,r,t,n,m,s,e,a,b;

int dfs(int idx){
	arr[idx].visit=++cnt;
	int ret=arr[idx].visit;
	stk.push(idx);
	for(auto i:arr[idx].v){
		if(!arr[i].visit)ret=min(ret,dfs(i));
		else if(!arr[i].scc)ret=min(ret,arr[i].visit);
	}
	if(ret==arr[idx].visit){
		vector<int> tmp;
		while(1){
			int t=stk.top();
			stk.pop();
			arr[t].scc=r;
			tmp.push_back(t);
			if(t==idx)break;
		}
		++r;
		scc.push_back(tmp);
	}
	return ret;
}

void init(int n){
	scc.clear();
	stk=stack<int>();
	cnt=0,r=1,a=0,b=0;
	for(int i=1;i<=n;++i){
		arr[i].visit=0;
		arr[i].scc=0;
		arr[i].v.clear();
		fin[i].in.clear();
		fin[i].out.clear();
	}
}

void addEdge(int src,int dst){
	arr[src].v.push_back(e);
}

void toposort(){
	for(int i=1;i<=n;++i){
		for(auto j:arr[i].v){
			if(arr[i].scc!=arr[j].scc){
				fin[arr[i].scc].out.push_back(arr[j].scc);
				fin[arr[j].scc].in.push_back(arr[i].scc);
			}
		}
	}
}

int main(){
	for(scanf("%d",&t);t--;){
		scanf("%d %d",&n,&m);
		init(n);
		for(int i=0;i<m;++i){
			scanf("%d %d",&s,&e);
			addEdge(s,e);
		}
		for(int i=1;i<=n;++i)if(!arr[i].visit)dfs(i);
		toposort();
		if(scc.size()==1){
			printf("0\n");
			continue;
		}
		for(int i=1;i<=scc.size();++i){
			if(!fin[i].in.size())++a;
			if(!fin[i].out.size())++b;
		}
		printf("%d\n",max(a,b));
	}
}