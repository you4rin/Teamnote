#include<iostream>
#include<string>
#include<vector>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)

using namespace std;

string s,t;
int n,m;
int p[1000010];
vector<int> result;

void init(){
	getline(cin,s);
	getline(cin,t);
	n=s.size(),m=t.size();
	for(int i=1,j=0;i<m;++i){
		while(j>0&&t[i]!=t[j])j=p[j-1];
		if(t[i]==t[j])p[i]=++j;
	}
}

void solve(){
	for(int i=0,j=0;i<n;++i){
		while(j>0&&s[i]!=t[j])j=p[j-1];
		if(s[i]==t[j]){
			if(j==m-1){
				result.push_back(i-m+2);
				j=p[j];
			}
			else ++j;
		}
	}
}

int main(){
	fastio();
	init();
	solve();
	cout<<result.size()<<"\n";
	for(auto i:result)cout<<i<<" ";
}