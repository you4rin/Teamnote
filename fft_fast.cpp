// boj.kr/11576
#define _USE_MATH_DEFINES
#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<complex>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()

using namespace std;
using base=complex<double>;
using ll=long long;

void fft(vector<base>& a,bool inv){
	int n=(int)a.size();
	for(int i=1,j=0;i<n;i++){
		int bit=n>>1;
		while(!((j^=bit)&bit))bit>>=1;
		if(i<j)swap(a[i],a[j]);
	}
	for(int i=1;i<n;i<<=1){
		double x=inv?M_PI/i:-M_PI/i;
		base w={cos(x),sin(x)};
		for(int j=0;j<n;j+=i<<1){
			base th={1,0};
			for(int k=0;k<i;k++){
				base tmp=a[i+j+k]*th;
				a[i+j+k]=a[j+k]-tmp;
				a[j+k]+=tmp;
				th*=w;
			}
		}
	}
	if(inv)for(int i=0;i<n;i++)a[i]/=n;
}

void multiply(vector<base>& a,vector<base>& b) {
	int n=(int)max(a.size(),b.size());
	int i=0;
	while((1<<i)<(n<<1))i++;
	n=1<<i;
	a.resize(n);b.resize(n);
	fft(a,0);fft(b,0);
	for(int i=0;i<n;i++)a[i]*=b[i];
	fft(a,1);
}

int main(){
	fastio();
	string p,q;
	vector<base> a,b;
	cin>>p>>q;
	for(auto i:p)a.push_back(i-'0');
	for(auto i:q)b.push_back(i-'0');
	multiply(a,b);
	for(int i=p.size()+q.size()-2;i>=0;--i){
		ll val=round(a[i].real());
		if(val>9){
			if(!i)printf("%lld",val/10);
			else a[i-1]+=base({(double)(val/10),0});
			a[i]=base({(double)(val%10),0});
		}
	}
	for(int i=0;i<p.size()+q.size()-1;++i)printf("%lld",(ll)round(a[i].real()));
}