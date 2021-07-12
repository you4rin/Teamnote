// boj.kr/1067
#define _USE_MATH_DEFINES
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<complex>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define N 1000000LL

using namespace std;
using ld=long double;
using ll=long long;
using DataType=int;
using base=complex<ld>;

void fft(vector<base>& a,bool inv){
	int n=(int)a.size();
	for(int i=1,j=0;i<n;i++){
		int bit=n>>1;
		while(!((j^=bit)&bit))bit>>=1;
		if(i<j)swap(a[i],a[j]);
	}
	vector<base>root(n/2);
	long double ang=2*acos(-1)/n*(inv?-1:1);
	for(int i=0;i<n/2;i++)root[i]=base(cos(ang*i),sin(ang*i));
	for(int idx=2;idx<=n;idx<<=1){ 
		int step=n/idx;
		for(int i=0;i<n;i+=idx){ 
			for(int j=0;j<idx/2;j++){ 
				base u=a[i+j],v=a[i+j+idx/2]*root[step*j]; 
				a[i+j]=u+v; 
				a[i+j+idx/2]=u-v; 
			} 
		} 
	} 
	if(inv){ 
		for(auto& i:a)i /= n; 
	}
}

void multiply(vector<DataType>& a,vector<DataType>& b,vector<DataType>& res){
	vector<base> al,as,bl,bs;
	int n=(int)max(a.size(),b.size()),cut=sqrt(N);
	int i=0;
	while((1<<i)<(n<<1))i++;
	n=1<<i;
	al.resize(n);as.resize(n);bl.resize(n);bs.resize(n);
	for(int i=0;i<a.size();++i){
		al[i]=a[i]/cut;
		as[i]=a[i]%cut;
	}
	for(int i=0;i<b.size();++i){
		bl[i]=b[i]/cut;
		bs[i]=b[i]%cut;
	}
	fft(al,0);fft(bl,0);
	fft(as,0);fft(bs,0);
	vector<base> c(all(al)),d(all(as));
	for(int i=0;i<n;i++){
		c[i]*=bl[i];
		al[i]*=bs[i];
		as[i]*=bs[i];
		d[i]*=bl[i];
	}
	fft(as,1);fft(d,1);
	fft(al,1);fft(c,1);
	res.resize(n);
	for(int i=0;i<n;++i){
		DataType ss=(DataType)round(as[i].real());
		DataType sb=(DataType)round(d[i].real());
		DataType bs=(DataType)round(al[i].real());
		DataType bb=(DataType)round(c[i].real());
		res[i]=ss;
		res[i]+=(sb+bs)*cut;
		res[i]+=bb*cut*cut;
	}
}

int main(){
	fastio();
	int n,tmp;
	DataType ans=0;
	vector<DataType> a,b,res;
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>tmp;
		a.push_back(tmp);
	}
	for(int i=0;i<n;++i){
		cin>>tmp;
		b.push_back(tmp);
	}
	b=vector<DataType>(b.rbegin(),b.rend());
	for(int i=0;i<n;++i)a.push_back(a[i]);
	multiply(a,b,res);
	for(int i=n;i<2*n;++i)ans=max(ans,res[i]);
	cout<<ans<<"\n";
}