// boj.kr/17387
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#define fastio() ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)

using namespace std;
using ll=long long;

struct point{
	ll x,y;
};

struct line{
	point p1,p2;
};

point src[2],dst[2];

int ccw(point p1,point p2,point p3){
	ll x1,y1,x2,y2,det;
	x1=p2.x-p1.x;
	y1=p2.y-p1.y;
	x2=p3.x-p2.x;
	y2=p3.y-p2.y;
	det=x1*y2-x2*y1;
	if(det>0)return 1;
	if(!det) return 0;
	return -1;
}

bool cross(line a,line b){
	int r1,r2;
	if(a.p1.x>a.p2.x)swap(a.p1,a.p2);
	else if(a.p1.x==a.p2.x&&a.p1.y>a.p2.y)swap(a.p1,a.p2);
	if(b.p1.x>b.p2.x)swap(b.p1,b.p2);
	else if(b.p1.x==b.p2.x&&b.p1.y>b.p2.y)swap(b.p1,b.p2);
	if(a.p1.x>b.p1.x)swap(a,b);
	else if(a.p1.x==b.p1.x&&a.p1.y>b.p1.y)swap(a,b);
	r1=ccw(a.p1,a.p2,b.p1),r2=ccw(a.p1,a.p2,b.p2);
	if(r1==r2&&r1)return 0;
	if(r1==r2&&!r1){
		int t1,t2,t3,t4;
		if(a.p1.x!=a.p2.x){
			t1=a.p1.x<b.p1.x,t2=a.p1.x<b.p2.x;
			t3=a.p2.x<b.p1.x,t4=a.p2.x<b.p2.x;
			if(t1==t2&&t2==t3&&t3==t4)return 0;
			return 1;
		}
		else{
			t1=a.p1.y<b.p1.y,t2=a.p1.y<b.p2.y;
			t3=a.p2.y<b.p1.y,t4=a.p2.y<b.p2.y;
			if(t1==t2&&t2==t3&&t3==t4)return 0;
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