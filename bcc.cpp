// apoint: boj.kr/11266
// aedge: boj.kr/11400
#include<cstdio>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;
using pii=pair<int,int>;

struct Node{
	int num,m,group;
	vector<int> v;
};

Node arr[100010];
int dfs_cnt,n,m;
vector<vector<pii>> bcc;
int ans[100010];
vector<int> ap;
vector<pii> ae;
stack<pii> stk;

void dfs(int p,int idx){
	arr[idx].num=arr[idx].m=++dfs_cnt;
	for(auto i:arr[idx].v){
		if(i==p)continue;
		if(arr[idx].num>arr[i].num)stk.push({idx,i});
		if(arr[i].num){
			arr[idx].m=min(arr[idx].m,arr[i].num);
			continue;
		}
		dfs(idx,i);
		arr[idx].m=min(arr[idx].m,arr[i].m);
		if(arr[i].m>=arr[idx].num){
			vector<pii> v;
			while(1){
				pii e=stk.top();stk.pop();
				v.push_back(e);
				if(e==pii{idx,i})break;
			}
			bcc.push_back(v);
		}
	}
}

void init(){
	int s,e;
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;++i){
		scanf("%d %d",&s,&e);
		arr[s].v.push_back(e);
		arr[e].v.push_back(s);
	}
	for(int i=1;i<=n;++i)if(!arr[i].num)dfs(0,i);
}

void apoint(){
	for(int i=0;i<bcc.size();++i){
		for(auto j:bcc[i]){
			for(auto k:{j.first,j.second}){
				if(ans[k])continue;
				if(arr[k].group&&arr[k].group!=i+1){
					ans[k]=1;
					ap.push_back(k);
				}
				arr[k].group=i+1;
			}
		}
	}
	sort(ap.begin(),ap.end());
	printf("%d\n",ap.size());
	for(auto i:ap)printf("%d ",i);
}

void aedge(){
	for(auto i:bcc)if(i.size()==1)ae.push_back({min(i[0].first,i[0].second),max(i[0].first,i[0].second)});
	sort(ae.begin(),ae.end());
	printf("%d\n",ae.size());
	for(auto i:ae)printf("%d %d\n",i.first,i.second);
}

int main(){
	init();
	//apoint();
	aedge();
}