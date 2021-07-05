// boj.kr/3176
#include<iostream>
#include<vector>
#include<algorithm>
#define inf ((DataType)(1e9))
#define exp 17
#define VAL_NUM 2
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)

using namespace std;
using ll=long long;
using DataType=int;
using pid=pair<int,DataType>;

struct Node{
	int p[exp];
	DataType val[exp][VAL_NUM];
	int visit,depth;
	vector<pid> v;
};

struct Query{
	DataType val[VAL_NUM];
};

Node arr[100010];

DataType Min(DataType s,DataType e){
	return min(s,e);
}

DataType Max(DataType s,DataType e){
	return max(s,e);
}

DataType (*metric[])(DataType s,DataType e){
	Min, 
		Max, // may be added
};

void lcainit(int p,int idx,DataType val){
	arr[idx].visit=1;
	for(int i=0;i<exp;++i){
		arr[idx].val[i][0]=inf;
		arr[idx].val[i][1]=-inf;
	}
	arr[idx].p[0]=p;
	arr[idx].val[0][0]=arr[idx].val[0][1]=val;
}

void dfs(int p,int idx,DataType val){
	lcainit(p,idx,val);
	for(int i=1;i<exp;++i){
		arr[idx].p[i]=arr[arr[idx].p[i-1]].p[i-1];
		for(int j=0;j<VAL_NUM;++j)
			arr[idx].val[i][j]=metric[j](arr[idx].val[i-1][j],arr[arr[idx].p[i-1]].val[i-1][j]);
	}
	arr[idx].depth=arr[arr[idx].p[0]].depth+1;
	for(auto i:arr[idx].v){
		if(arr[i.first].visit)continue;
		dfs(idx,i.first,i.second);
	}
}

void update(int a,int b,int idx,Query& q){
	for(int i=0;i<VAL_NUM;++i){
		q.val[i]=metric[i](q.val[i],arr[a].val[idx][i]);
		q.val[i]=metric[i](q.val[i],arr[b].val[idx][i]);
	}
}

Query lca(int a,int b,Query q){
	if(a==b)return q;
	for(int i=exp-1;i>=0;--i){
		if(arr[a].p[i]!=arr[b].p[i]){
			update(a,b,i,q);
			a=arr[a].p[i];
			b=arr[b].p[i];
		}
	}
	update(a,b,0,q);
	return q;
}

Query level(int& a,int& b){
	Query ret={inf,-inf};
	for(int i=exp-1;i>=0;--i){
		if(arr[a].depth-(1<<i)>=arr[b].depth){
			for(int j=0;j<VAL_NUM;++j)
				ret.val[j]=metric[j](ret.val[j],arr[a].val[i][j]);
			a=arr[a].p[i];
		}
	}
	return ret;
}

// add 'undirected', 'weighted' edge
void addEdge(int src,int dst,DataType weight){
	arr[src].v.push_back({dst,weight});
	arr[dst].v.push_back({src,weight});
}

int main(){
	int n,k,a,b;
	DataType c;
	fastio();
	cin>>n;
	for(int i=1;i<n;++i){
		cin>>a>>b>>c;
		addEdge(a,b,c);
	}
	dfs(0,1,0);
	for(cin>>k;k--;){
		cin>>a>>b;
		if(arr[b].depth>arr[a].depth)swap(a,b);
		Query ret=level(a,b);
		ret=lca(a,b,ret);
		cout<<ret.val[0]<<' '<<ret.val[1]<<'\n';
	}
}