// boj.kr/16229
#include<iostream>
#include<string>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define N 100010

using namespace std;

string s;
int a[N];
int n,k,ans;

void z(){
	int r=-1,p;
	for(int i=1;i<n;++i){
		a[i]=(r>=i?min(a[i-p],r-i):-1);
		while(i+a[i]+1<n&&s[i+a[i]+1]==s[a[i]+1])++a[i];
		if(i+a[i]>r)r=i+a[i],p=i;
	}
}

int main(){
	fastio();
	cin>>n>>k;
	if(k>=n){
		cout<<n<<"\n";
		return 0;
	}
	cin>>s;
	z();
	for(int i=n-1;i;--i){
		for(int j=i;j<=n+k;j+=i){
			if(j>=n){ans=max(ans,i);break;}
			if(a[j]+1<i&&j+a[j]+1!=n)break;
		}
	}
	cout<<ans;
}