#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)

using namespace std;
using ll=long long;

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

point src[2],dst[2];

int ccw(point p1,point p2,point p3){
	ll det=(p2.x-p1.x)*(p3.y-p2.y)-(p3.x-p2.x)*(p2.y-p1.y);
	return !det?0:(det>0?1:-1);
}

bool cross(line a,line b){
	int r1,r2;
	if(a.p2<a.p1)swap(a.p1,a.p2);
	if(b.p2<b.p1)swap(b.p1,b.p2);
	if(b<a)swap(a,b);
	r1=ccw(a.p1,a.p2,b.p1),r2=ccw(a.p1,a.p2,b.p2);
	if(r1==r2&&r1)return 0;
	if(r1==r2&&!r1){
		if(a.p1.x!=a.p2.x){
			if(a.p2.x<b.p1.x)return 0;
			return 1;
		}
		else{
			if(a.p2.y<b.p1.y)return 0;
			return 1;
		}
	}
	r1=ccw(b.p1,b.p2,a.p1),r2=ccw(b.p1,b.p2,a.p2);
	if(r1==r2&&r1)return 0;
	return 1;
}

int main(){
	fastio();
	cin>>src[0].x>>src[0].y;
	cin>>dst[0].x>>dst[0].y;
	cin>>src[1].x>>src[1].y;
	cin>>dst[1].x>>dst[1].y;
	cout<<(int)cross({src[0],dst[0]},{src[1],dst[1]});
}