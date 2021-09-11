// boj.kr/17387
// boj.kr/20149
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define inf 1e9
#define eps 1e-14

using namespace std;
using ll=long long;
using ld=long double;
using pld=pair<ld,ld>;

struct point{
	ll x,y;
	bool operator==(point& other){return x==other.x&&y==other.y;}
	bool operator<(point& other){
		if(x==other.x)return y<other.y;
		return x<other.x;
	}
};

struct line{
	point p1,p2;
	bool operator<(line& other){
		if(p1==other.p1)return p2<other.p2;
		return p1<other.p1;
	}
};

struct func{
	ld a,b;
};

point src[2],dst[2];
pld intersect;

int ccw(point p1,point p2,point p3){
	ll det=(p2.x-p1.x)*(p3.y-p2.y)-(p3.x-p2.x)*(p2.y-p1.y);
	return !det?0:(det>0?1:-1);
}

void find_point(func a,func b){
	ld x=(a.b-b.b)/(b.a-a.a),y=a.a*x+a.b;
	intersect={x,y};
}

bool cross(line a,line b){
	// annotation: finding point of intersection
	int r1,r2;
	if(a.p2<a.p1)swap(a.p1,a.p2);
	if(b.p2<b.p1)swap(b.p1,b.p2);
	if(b<a)swap(a,b);
	r1=ccw(a.p1,a.p2,b.p1),r2=ccw(a.p1,a.p2,b.p2);
	if(r1==r2&&r1)return 0;
	if(r1==r2){
		if(a.p1.x!=a.p2.x){
			if(a.p2.x<b.p1.x)return 0;
			if(a.p2.x==b.p1.x)intersect={a.p2.x,a.p2.y};
			else intersect={inf,inf};
		}
		else{
			if(a.p2.y<b.p1.y)return 0;
			if(a.p2.y==b.p1.y)intersect={a.p2.x,a.p2.y};
			else intersect={inf,inf};
		}
		return 1;
	}
	r1=ccw(b.p1,b.p2,a.p1),r2=ccw(b.p1,b.p2,a.p2);
	if(r1==r2&&r1)return 0;
	func c,d;
	if(b.p1.x==b.p2.x)swap(a,b);
	c.a=(ld)(a.p2.y-a.p1.y)/(a.p2.x-a.p1.x),c.b=c.a*-a.p1.x+a.p1.y;
	d.a=(ld)(b.p2.y-b.p1.y)/(b.p2.x-b.p1.x),d.b=d.a*-b.p1.x+b.p1.y;
	if(a.p1.x==a.p2.x)intersect={a.p1.x,d.a*a.p1.x+d.b};
	else find_point(c,d);
	return 1;
}

int main(){
	scanf("%lld %lld %lld %lld",&src[0].x,&src[0].y,&src[1].x,&src[1].y);
	scanf("%lld %lld %lld %lld",&dst[0].x,&dst[0].y,&dst[1].x,&dst[1].y);
	if(!cross({src[0],src[1]},{dst[0],dst[1]})){
		printf("0");
		return 0;
	}
	printf("1\n");
	if(intersect.first==inf)return 0;
	printf("%.11Lf %.11Lf",intersect.first+eps,intersect.second+eps);
}