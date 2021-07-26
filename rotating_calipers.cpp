// boj.kr/09240
#include<cstdio>
#include<cmath>
#include<vector>
#include<deque>
#include<algorithm>
#define eps 1e-9

using namespace std;
using ll=long long;
using ld=long double;

struct point{
	ld x,y;
	point(){}
	point(ld x,ld y):x(x),y(y){}
	point operator-(const point& other){return {x-other.x,y-other.y};}
	bool operator<(const point& other){
		if(y!=other.y)return y<other.y;
		return x<other.x;
	}
	ld cross(const point& other){return x*other.y-y*other.x;}
	ld norm(){return sqrtl(x*x+y*y);}
};

ld ccw(point a,point b){return a.cross(b);}
ld ccw(point a,point b,point c){return (b-a).cross(c-a);}
point s,ans1,ans2;
bool cmp(point& a,point& b){
	if(abs(ccw(s,a,b))>eps)return ccw(s,a,b)>eps;
	return a<b;
}
// convex hull
vector<int> ch(vector<point>& v){
	vector<int> ret;
	sort(v.begin(),v.end());
	s=v[0];
	sort(v.begin()+1,v.end(),cmp);

	ret.push_back(0);
	ret.push_back(1);

	for(int i=2;i<v.size();++i){
		while(ret.size()>1){
			int idx1=ret.back();
			int idx2=ret[ret.size()-2];
			if(ccw(v[idx2],v[idx1],v[i])>eps)break;
			ret.pop_back();
		}
		ret.push_back(i);
	}
	return ret;
}
// rotating calipers
ld rc(vector<point>& v){
	vector<int> tmp=ch(v);
	vector<point> p;
	for(int i:tmp)p.push_back(v[i]);

	int p1=0,p2=1;
	ld mx=(p[p1]-p[p2]).norm();
	ans1=p[p1];
	ans2=p[p2];

	for(int i=0;i<p.size()*2;++i){
		int np1=(p1+1)%p.size();
		int np2=(p2+1)%p.size();
		ld tmp=ccw(p[np1]-p[p1],p[p2]-p[np2]);

		if(tmp>eps)p1=np1;
		if(tmp<-eps)p2=np2;
		if(abs(tmp)<=eps)p1=np1,p2=np2;

		ld now=(p[p1]-p[p2]).norm();
		if(mx+eps<now){
			mx=now;
			ans1=p[p1];
			ans2=p[p2];
		}
	}
	return mx;
}

int main(){
	int n;
	vector<point> v;
	ld x,y;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%Lf %Lf",&x,&y);
		v.push_back({x,y});
	}
	printf("%.7Lf\n",rc(v));
}