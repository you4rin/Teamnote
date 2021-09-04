#include<cstdio>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

struct Node{
	int visit,comp,val; // val is for 2-sat
	vector<int> v;
};

Node arr[100010];
vector<vector<int>> scc;
stack<int> stk;
int cnt,n;

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

void find_scc(int n){for(int i=1;i<=n;++i)if(!arr[i].visit)dfs(i);}

int op(int x){return x>n?x-n:x+n;}

void add_edge(int x,int y){ // if x, then y
	if(x<0)x=-x+n;
	if(y<0)y=-y+n;
	arr[x].v.push_back(y);
	arr[op(y)].v.push_back(op(x));
}

bool solve(){
	find_scc(n<<1);
	for(int i=1;i<=n;++i)if(arr[i].comp==arr[op(i)].comp)return 0;
	for(int i=scc.size()-1;i>=0;--i){
		bool flag=false;
		for(auto j:scc[i]){
			if(arr[j].val){
				flag=true;
				break;
			}
		}
		for(auto j:scc[i]){
			arr[j].val=flag;
			arr[op(j)].val=!flag;
		}
	}
	return 1;
}

int main(){
	int m,s,e;
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;++i){
		scanf("%d %d",&s,&e);
		add_edge(-s,e);
	}
	if(!solve()){
		puts("0");
		return 0;
	}
	puts("1");
	for(int i=1;i<=n;++i)printf("%d ",arr[i].val);
}