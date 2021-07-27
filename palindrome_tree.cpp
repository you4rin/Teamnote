// boj.kr/10066
#include<cstdio>
#include<algorithm>

using namespace std;
using ll=long long;

struct Node{
	int len;
	int sl;
	int next[26];
};

char s[300010];
int cnt=2,ls=2;
Node arr[300010];
ll dp[300010];

void construct(char c,int pos){
	int cur=ls;
	while(1){
		if(pos-arr[cur].len-1>=0&&c==s[pos-arr[cur].len-1])break;
		cur=arr[cur].sl;
	}
	if(arr[cur].next[c-'a']){
		ls=arr[cur].next[c-'a'];
		++dp[ls];
		return;
	}
	int next=ls=arr[cur].next[c-'a']=++cnt;
	arr[next].len=arr[cur].len+2;
	++dp[ls];
	if(arr[next].len==1){
		arr[next].sl=2;
		return;
	}
	while(cur>1){
		cur=arr[cur].sl;
		if(pos-arr[cur].len-1>=0&&c==s[pos-arr[cur].len-1]){
			arr[next].sl=arr[cur].next[c-'a'];
			break;
		}
	}
}

int main(){
	ll ans=0;
	arr[1]={-1,1},arr[2]={0,1};
	scanf("%s",s);
	for(int i=0;s[i]!='\0';++i)construct(s[i],i);
	for(int i=cnt;i>2;--i){
		ans=max(ans,dp[i]*arr[i].len);
		dp[arr[i].sl]+=dp[i];
	}
	printf("%lld",ans);
}