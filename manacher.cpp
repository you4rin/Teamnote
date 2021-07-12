#include<iostream>
#include<string>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 4000010

using namespace std;
using ll=long long;

string s,tmp;
int a[N];
int n;

void build_string(){
	n=s.size()*2+1;
	tmp="#";
	for(auto i:s){
		tmp+=i;
		tmp+="#";
	}
	s=tmp;
}

void manacher(){
	int r=-1,p;
	build_string();
	for(int i=0;i<n;++i){
		if(r>=i)a[i]=min(r-i,a[2*p-i]);
		while(i-a[i]>0&&i+a[i]<n-1&&s[i-a[i]-1]==s[i+a[i]+1])++a[i];
		if(i+a[i]>r)r=i+a[i],p=i;
	}
}

int main(){
	fastio();
	cin>>s;
	ll ans=0;
	manacher();
	for(int i=1;i<n;++i)ans+=((i&1)?(a[i]+1)/2:a[i]/2);
	cout<<ans;
}