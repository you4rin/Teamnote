// boj.kr/18438
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)

using namespace std;

void len(string::iterator al,string::iterator ar,string::iterator bl,
		 string::iterator br,vector<int>& v){
	vector<int> cur(br-bl+1,0);
	vector<int> prv(cur);
	for(auto it=al;it!=ar;++it){
		swap(prv,cur);
		for(int i=0;i<br-bl;++i)cur[i+1]=(*it==*(bl+i)?prv[i]+1:max(cur[i],prv[i+1]));
	}
	v=cur;
}

void rlen(string::reverse_iterator al,string::reverse_iterator ar,
		  string::reverse_iterator bl,string::reverse_iterator br,vector<int>& v){
	vector<int> cur(br-bl+1,0);
	vector<int> prv(cur);
	for(auto it=al;it!=ar;++it){
		swap(prv,cur);
		for(int i=0;i<br-bl;++i)cur[i+1]=(*it==*(bl+i)?prv[i]+1:max(cur[i],prv[i+1]));
	}
	v=cur;
}

void solve(string::iterator a,string::iterator al,string::iterator ar,
		   string::iterator bl,string::iterator br,vector<int>& v){
	int dist=ar-al,lm=-1;
	string::iterator am;
	vector<int> v1,v2;
	if(!dist)return;
	if(dist==1){
		v[al-a]=find(bl,br,*al)!=br;
		return;
	}
	am=al+dist/2;
	string::reverse_iterator ral(ar),ram(am),rbl(br),rbr(bl);
	len(al,am,bl,br,v1);
	rlen(ral,ram,rbl,rbr,v2);
	auto rit=v2.rbegin();
	auto b=bl,bm=bl;
	for(auto it=v1.begin();it!=v1.end();++it,++rit){
		if(*it+*rit>lm){
			lm=*it+*rit;
			bm=b;
		}
		if(b!=br)++b;
	}
	solve(a,al,am,bl,bm,v);
	solve(a,am,ar,bm,br,v);
}

void hirschberg(string& a,string& b,string& ans){
	vector<int> v(a.size(),0);
	solve(a.begin(),a.begin(),a.end(),b.begin(),b.end(),v);
	ans="";
	for(int i=0;i<v.size();++i)if(v[i])ans+=a[i];
}

int main(){
	fastio();
	string a,b,ans;
	cin>>a>>b;
	hirschberg(a,b,ans);
	cout<<ans.size()<<"\n";
	cout<<ans;
}