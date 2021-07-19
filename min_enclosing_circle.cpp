// boj.kr/2626
#include<cstdio>
#include<cmath>
#include<random>
#include<vector>
#include<algorithm>
#define x first
#define y second
#define eps 1e-14
#define ax p[a].x
#define ay p[a].y
#define bx p[b].x
#define by p[b].y
#define cx p[c].x
#define cy p[c].y

using namespace std;
using ld=long double;

pair<ld,ld> p[1010];

ld dist(pair<ld,ld> a,pair<ld,ld> b){
	return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}

pair<pair<ld,ld>,ld> c,tmp;
int n;

pair<pair<ld,ld>,ld> find3(int a,int b,int c){
	if((by-ay<eps&&ay-by<eps&&by-cy<eps&&cy-by<eps)
	   ||(eps>(bx-ax)/(by-ay)-(cx-bx)/(cy-by)&&(bx-ax)/(by-ay)-(cx-bx)/(cy-by)>-eps)){
		if(abs(ax-cx)+abs(ay-cy)>abs(ax-bx)+abs(ay-by)+eps){
			return {{(p[a].x+p[c].x)/2,(p[a].y+p[c].y)/2},dist(p[a],p[c])/2};
		}
		else return {{(p[a].x+p[b].x)/2,(p[a].y+p[b].y)/2},dist(p[a],p[b])/2};
	}
	ld xx=(ax*ax*(by-cy)+bx*bx*(cy-ay)+cx*cx*(ay-by)-(ay-by)*(by-cy)*(cy-ay))/
		(2*(ax*(by-cy)+bx*(cy-ay)+cx*(ay-by)));
	ld yy=(ay*ay*(bx-cx)+by*by*(cx-ax)+cy*cy*(ax-bx)-(ax-bx)*(bx-cx)*(cx-ax))/
		(2*(ay*(bx-cx)+by*(cx-ax)+cy*(ax-bx)));
	return {{xx,yy},dist({xx,yy},p[a])};
}

pair<pair<ld,ld>,ld> find2(int idx1,int idx2){
	tmp={{(p[idx1].x+p[idx2].x)/2,(p[idx1].y+p[idx2].y)/2},dist(p[idx1],p[idx2])/2};
	for(int i=0;i<idx1;++i){
		if(tmp.y+eps>=dist(p[i],tmp.x))continue;
		tmp=find3(i,idx1,idx2);
	}
	return tmp;
}

pair<pair<ld,ld>,ld> find1(int idx){
	tmp={{(p[0].x+p[idx].x)/2,(p[0].y+p[idx].y)/2},dist(p[0],p[idx])/2};
	for(int i=1;i<idx;++i){
		if(tmp.y+eps>=dist(p[i],tmp.x))continue;
		tmp=find2(i,idx);
	}
	return tmp;
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%Lf %Lf",&p[i].x,&p[i].y);
		for(int j=0;j<i;++j){
			if(eps>(p[i].x-p[j].x)&&-eps<(p[i].x-p[j].x)&&eps>(p[i].y-p[j].y)&&-eps<(p[i].y-p[j].y)){
				--i;--n;
			}
		}
	}
	random_device rd;
	mt19937 gen(rd());
	shuffle(p,p+n,gen);
	if(n==1){
		printf("%.3Lf %.3Lf\n%.3Lf\n",p[0].x+eps,p[0].y+eps,(ld)0);
		return 0;
	}
	c={{(p[0].x+p[1].x)/2,(p[0].y+p[1].y)/2},dist(p[0],p[1])/2};
	if(c.y<eps&&c.y>-eps)c.y=abs(c.y);
	if(n==2){
		printf("%.3Lf %.3Lf\n%.3Lf\n",c.x.x+eps,c.x.y+eps,c.y);
		return 0;
	}
	for(int i=2;i<n;++i){
		if(c.y+eps>=dist(p[i],c.x))continue;
		c=find1(i);
	}
	if(c.y<eps&&c.y>-eps)c.y=abs(c.y);
	printf("%.3Lf %.3Lf\n%.3Lf\n",c.x.x+eps,c.x.y+eps,c.y);
}